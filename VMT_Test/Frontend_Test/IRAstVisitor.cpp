#pragma once
#include "IRAstVisitor.h"
#include "Env.h"


namespace TS {
    class AST_IR_Codegen;

    class CollectIRValue : public AST::ICollectInfoBack {
    public:
        CollectIRValue()
            : m_value(nullptr)
        {}

        IR::Value* getValue() const {
            return m_value;
        }
        void setValue(IR::Value* v) {
            m_value = v;
        }
    private:
        IR::Value* m_value;
    };
    // translate ast to ir,we need so much help component
    AST_IR_Codegen::AST_IR_Codegen() {
        m_context = std::make_shared<IR::IRContext>();
        m_env = std::make_shared<SymTable>();
        
        m_env->put( "bool", m_context->getTypeManger().getBoolType());
        m_env->put( "i32",  m_context->getTypeManger().getTypeFromName("i32"));
        m_env->put( "ui32", m_context->getTypeManger().getTypeFromName("ui32"));
        m_env->put( "i64",  m_context->getTypeManger().getTypeFromName("i64"));
        m_env->put( "ui64", m_context->getTypeManger().getTypeFromName("ui64"));
        m_env->put( "f32",  m_context->getTypeManger().getTypeFromName("f32"));
        m_env->put( "f64",  m_context->getTypeManger().getTypeFromName("f64"));

        m_currentEnv = m_env;
        m_localValueIndex = 0;

    }
    
    void AST_IR_Codegen::visitFunction(AST::AstFunction* astFunction, AST::ICollectInfoBack* collect) {
        EnvRAII lock(this);
        auto astType = astFunction->getFunctionType();
        std::string ss(astType->getType().toStringView());
        auto ttype = _Find(ss);
        if (nullptr == ttype) {
            Diagnose::errorMsg("cann't find the type");
        }
        auto funNameTok = astFunction->getFunctionName();
        IR::Function* ir_function = IR::IRBuilder(m_context).emitFunction(funNameTok.toString().data(), nullptr);


        auto paramList = astFunction->getFunctionParamList();
        for (size_t i = 0; i < paramList->size(); ++i) {
            auto param = paramList->at(i);
            auto typeTok = param.getType();
            std::string ss(typeTok.toStringView());
            auto envType = _GetCurrentEnv()->find( ss );
            auto name = param.getId();
            if (nullptr == envType) {
                Diagnose::errorMsg("cann't find the type");
                return;
            }
            else {
                auto symtype = envType->getSymType();
                if (symtype == SymType::kClass) {
                
                }
                else if (symtype == SymType::kType) {
                    auto type = _GetCurrentEnv()->get<IR::Type>(ss);
                    IR::Value* value = IR::IRBuilder(m_context).emitAlloc(type, std::string(name.toStringView()).c_str());
                    _GetCurrentEnv()->put(std::string(name.toStringView()), value);
                    ir_function->addArgs(value);
                }
                else {
                    Diagnose::errorMsg("cann't find the type");
                    return;
                }
            }
        }
        auto block = astFunction->getFunctionBlock();
        block->gen(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), collect);

        {
            auto function = m_context->getCurrentFunction();
            IR::TextIRWriteVisitor writer;
            writer.writeFunction(function);
            std::cout << writer.getTextStr() << std::endl;
        }
    }
    
    void AST_IR_Codegen::visitForStmt(AST::AstForStmt* forstmt, AST::ICollectInfoBack* collect) {
        std::string for_start = _GenLabel();
        std::string for_end   = _GenLabel();
        IR::IRBuilder(m_context).emitLabel(for_start);
        auto initExpr = forstmt->getLoopExpr( );
        if (initExpr) {
            CollectIRValue collectValue;
            initExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue);
        }

        std::string for_bool = _GenLabel();
        std::string for_body_begin = _GenLabel();
        IR::IRBuilder(m_context).emitLabel( for_bool);
        auto bool_expr = forstmt->getLoopExpr();
        CollectIRValue collectConditionValue;
        bool_expr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectConditionValue);
        IR::IRBuilder(m_context).emitBr( collectConditionValue.getValue(),for_body_begin, for_end );
        IR::IRBuilder(m_context).emitLabel(for_body_begin);
        auto stmt = forstmt->getStmt();
        CollectIRValue collectForBodyValue;
        stmt->gen(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectForBodyValue );
        std::string for_tail = _GenLabel();
        IR::IRBuilder(m_context).emitLabel(for_tail);
        auto tailExpr = forstmt->getTailExpr();
        if (tailExpr) {
            CollectIRValue collectTailValue;
            tailExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectTailValue);
        }
        IR::IRBuilder(m_context).emitJmp(for_bool);
        IR::IRBuilder(m_context).emitLabel(for_end);
    }
    
    void AST_IR_Codegen::visitWhileStmt(AST::AstWhileStmt* whileStmt, AST::ICollectInfoBack* collect) {
        std::string while_start = _GenLabel( );
        std::string while_end   = _GenLabel( );
        auto boolExpr = whileStmt->getLoopExpr();
    }

    void AST_IR_Codegen::visitDoWhileStmt(AST::AstDoWhileStmt*, AST::ICollectInfoBack* collect) {

    }

    void AST_IR_Codegen::visitIfStmt(AST::AstIfStmt* ifstmt, AST::ICollectInfoBack* collect) {
        auto bool_expr = ifstmt->getBoolExpr();
        auto else_stmt = ifstmt->getElseStmt();
        auto if_stmt = ifstmt->getIfStmt();
        CollectIRValue bool_value;

        bool_expr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &bool_value);
        
        std::string if_start = _GenLabel( );
        std::string if_end = _GenLabel( );


        std::string else_start;
        if (else_stmt) {
            else_start = _GenLabel();
            IR::IRBuilder(m_context).emitBr(bool_value.getValue(), if_start, else_start);
        }
        else {
            IR::IRBuilder(m_context).emitBr(bool_value.getValue(), if_start, if_end );
        }
        IR::IRBuilder(m_context).emitLabel(if_start);

        CollectIRValue if_stmt_collect_back;
        if_stmt->gen(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &if_stmt_collect_back);
        if (else_stmt) {
            IR::IRBuilder(m_context).emitJmp( if_end);
            IR::IRBuilder(m_context).emitLabel(else_start);
            CollectIRValue collectBack;
            else_stmt->gen(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectBack);
            IR::IRBuilder(m_context).emitJmp(if_end);
        }
        IR::IRBuilder(m_context).emitLabel(if_end);
    }

    void AST_IR_Codegen::visitElseStmt(AST::AstElseStmt* elseStmt, AST::ICollectInfoBack* collect) {
        CollectIRValue collectBack;
        elseStmt->getStmt()->gen(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectBack);
        if (nullptr != collect) {
            static_cast<CollectIRValue*>( collect)->setValue( collectBack.getValue());
        }
    }

    void AST_IR_Codegen::visitStmts(AST::AstStmts*, AST::ICollectInfoBack* collect) {
    
    }

    void AST_IR_Codegen::visitReturnStmt(AST::AstReturnStmt*, AST::ICollectInfoBack* collect) {
    
    }

    void AST_IR_Codegen::visitBreakStmt(AST::AstBreakStmt*, AST::ICollectInfoBack* collect) {
        
    }

    void AST_IR_Codegen::visitContinueStmt(AST::AstContinueStmt*, AST::ICollectInfoBack* collect) {
        
    }

    void AST_IR_Codegen::visitExprStmt(AST::AstExprStmt* astExprStmt, AST::ICollectInfoBack* collect) {
        auto expr = astExprStmt->getExpr();
        CollectIRValue collectValue;
        expr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue);
    }
    void AST_IR_Codegen::visitType(AST::AstType*, AST::ICollectInfoBack* collect) {
    
    }

    void AST_IR_Codegen::visitParamList(AST::AstParamList*, AST::ICollectInfoBack* collect) {
    
    }

    void AST_IR_Codegen::visitBlock(AST::AstBlock* astBlock, AST::ICollectInfoBack* collect) {
        EnvRAII s(this);
        for (auto iter = astBlock->begin(); iter != astBlock->end(); ++iter) {
            (*iter)->gen(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), collect);
        }
    }


    std::shared_ptr<AST::AstObjectExpr> AST_IR_Codegen::reduceBinaryOpExpr(AST::AstBinaryOpExpr* astBinaryOpExpr, AST::ICollectInfoBack* collect) {
        auto leftExpr  = astBinaryOpExpr->getLeft();
        auto rightExpr = astBinaryOpExpr->getRight();

        CollectIRValue collectValue1;
        CollectIRValue collectValue2;
        auto rleftExpr  = leftExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue1);
        auto rrightExpr = rightExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue2);
        auto tok = astBinaryOpExpr->getOp();
        
        IR::Instruction::OpCode opCode = IR::Instruction::OpCode::kError;
        TokenId op = tok.getTokenId();
        struct map {
            TokenId tok;
            IR::Instruction::OpCode op;

        };

        // language support binary operation 
        static const map strOpCode[] = {
            { TokenId::kw_plus,         IR::Instruction::OpCode::kAdd          },
            { TokenId::kw_minus,        IR::Instruction::OpCode::kMinus        },
            { TokenId::kw_star ,        IR::Instruction::OpCode::kMul          },
            { TokenId::kw_slash,        IR::Instruction::OpCode::kDiv          },
            { TokenId::kw_percent,      IR::Instruction::OpCode::kMod          },
            { TokenId::kw_starstar,     IR::Instruction::OpCode::kExp          },
            { TokenId::kw_equalequal,   IR::Instruction::OpCode::kEqual        },
            { TokenId::kw_exclaimequal, IR::Instruction::OpCode::kNotEqual     },
            { TokenId::kw_less,         IR::Instruction::OpCode::kLess         },
            { TokenId::kw_lessequal,    IR::Instruction::OpCode::kLessEqual    },
            { TokenId::kw_greater,      IR::Instruction::OpCode::kGreater      },
            { TokenId::kw_greaterequal, IR::Instruction::OpCode::kGreaterEqual },
        };
        for (size_t i = 0; i < sizeof(strOpCode) / sizeof(strOpCode[0]); ++i) {
            if (op == strOpCode[i].tok) {
                opCode = strOpCode[i].op;
                break;
            }
        }
        auto resultType = IR::TypeChecker::checkOp(*m_context, opCode, collectValue1.getValue(), collectValue2.getValue() );
        if ( nullptr == resultType) {
            
        }
        else {
        
            IR::Value* result = _GenTempValue( resultType );
            IR::IRBuilder(m_context).emitBinaryOpIns(opCode, result, collectValue1.getValue(), collectValue2.getValue());
            static_cast<CollectIRValue*>(collect)->setValue(result);
        }
        return nullptr;
    }
    std::shared_ptr<AST::AstObjectExpr> AST_IR_Codegen::reduceUnaryOpExpr(AST::AstUnaryOpExpr* astUnaryExpr, AST::ICollectInfoBack* collect) {
        auto rightExpr = astUnaryExpr->getExpr();
        CollectIRValue collectValue;
        rightExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue);
        IR::Instruction::OpCode op = _GetUnaryOpCode(astUnaryExpr->getOp());
        IR::Value* v = IR::IRBuilder(m_context).emitUnaryOpIns(op, collectValue.getValue());
        static_cast<CollectIRValue*>(collect)->setValue(v);
        return nullptr;
    }

    std::shared_ptr<AST::AstObjectExpr> AST_IR_Codegen::reduceConditionExpr(AST::AstConditionExpr* astConditionExpr, AST::ICollectInfoBack* collect) {
        auto contitionExpr = astConditionExpr->getCondition();
        auto trueExpr = astConditionExpr->getTrueExpr();
        auto falseExpr = astConditionExpr->getFalseExpr();
        CollectIRValue collectConditionValue;
        contitionExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectConditionValue);
        IR::IRBuilder(m_context).emitBr(collectConditionValue.getValue(), "cond.true:", "cond.false:");
        IR::IRBuilder(m_context).emitLabel("con.start:");
        CollectIRValue collectTrueValue;

        trueExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectTrueValue);
        IR::IRBuilder(m_context).emitJmp("con.end:");
        CollectIRValue collectFalseValue;
        falseExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectFalseValue);
        IR::IRBuilder(m_context).emitJmp("cond.end:");

        IR::IRBuilder(m_context).emitLabel("con.end:");
        auto v = IR::IRBuilder(m_context).emitPhi(collectTrueValue.getValue(), collectFalseValue.getValue());
        static_cast<CollectIRValue*>(collect)->setValue(v);
        return nullptr;
    }

    std::shared_ptr<AST::AstObjectExpr> AST_IR_Codegen::reduceConstantExpr(AST::AstConstantExpr* astObjectExpr, AST::ICollectInfoBack* collect) {
        Token tok = astObjectExpr->getToken();
        if (tok.getTokenId() == TokenId::kw_integer) {
            static_cast<CollectIRValue*>(collect)->setValue(new IR::IntegerConstant(m_context->getTypeManger().getTypeFromName("i32"), std::atoi(tok.toString().c_str())));
        }
        else if (tok.getTokenId() == TokenId::kw_real) {
            static_cast<CollectIRValue*>(collect)->setValue(new IR::FloatConstant(m_context->getTypeManger().getTypeFromName("f32"), std::atof(tok.toString().c_str())));
        }
        else if (tok.getTokenId() == TokenId::kw_true) {
            static_cast<CollectIRValue*>(collect)->setValue(new IR::TrueConstant(m_context->getTypeManger().getTypeFromName("bool")));
        }
        else if (tok.getTokenId() == TokenId::kw_false) {
            static_cast<CollectIRValue*>(collect)->setValue(new IR::FalseConstant(m_context->getTypeManger().getTypeFromName("bool")));
        }
        else {
            _ASSERT(false);
        }
        return nullptr;
    }

    std::shared_ptr<AST::AstObjectExpr> AST_IR_Codegen::reduceObjectExpr(AST::AstObjectExpr* astObjectExpr, AST::ICollectInfoBack* collect) {
        /// 这里最重要的逻辑就是查询当前已分配的节点数据,也就是IValue
        CollectIRValue collectValue;
        auto env = _GetCurrentEnv();
        auto type = env->find(std::string(astObjectExpr->getObject().toStringView()));
        if ( nullptr == type) {
            Diagnose::errorMsg("can not find the value");
        }
        else {
            if (SymType::kValue == type->getSymType()) {
                static_cast<CollectIRValue*>(collect)->setValue( env->get<IR::Value>(  std::string(astObjectExpr->getObject().toStringView()) ));
            }
            else {
                Diagnose::errorMsg("can not find the value");
            }
        }
        return nullptr;
    }

    std::shared_ptr<AST::AstObjectExpr> AST_IR_Codegen::reduceVoidExpr(AST::AstVoidExpr* astVoidExpr, AST::ICollectInfoBack* collect) {
        CollectIRValue collectValue;
        astVoidExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue);
        return nullptr;
    }

    // decl ::= type variable;
    //      ::= type variable = expr
    //      AstDecl -> type variable AssignExpr( variable,expr )
    std::shared_ptr<AST::AstObjectExpr> AST_IR_Codegen::reduceDecl(AST::AstDecl* astDecl, AST::ICollectInfoBack* collect) {
        auto env = _GetCurrentEnv();
        auto envType = env->find(std::string(astDecl->getType().toStringView()));
        IR::Value* v = nullptr;
        if (nullptr == envType) {
            Diagnose::errorMsg("can not find the type");
            return nullptr;
        }
        else {
            if (SymType::kClass == envType->getSymType()) {

            }
            else if (SymType::kType == envType->getSymType()) {
                auto type = env->get<IR::Type>(std::string(astDecl->getType().toStringView()));
                std::string str(astDecl->getName().toStringView());
                v = IR::IRBuilder(m_context).emitAlloc(type, str.c_str());
                env->put(str, v);
            }
            else {
                Diagnose::errorMsg("can not find the type");
            }
        }
        auto expr = astDecl->getExpr();
        CollectIRValue collectValue;
        if (expr) {
            expr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue);
        }
        static_cast<CollectIRValue*>(collect)->setValue(v);
        return nullptr;
    }

    std::shared_ptr<AST::AstObjectExpr> AST_IR_Codegen::reduceDecls(AST::AstDecls* astDecls, AST::ICollectInfoBack* collect) {
        CollectIRValue collectValue;
        for (auto iter = astDecls->begin(); iter != astDecls->end(); ++iter) {
            (*iter)->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue);
        }
        static_cast<CollectIRValue*>(collect)->setValue(collectValue.getValue());
        return nullptr;
    }

    // 这条语句很特殊,因为完成了定值操作
    std::shared_ptr<AST::AstObjectExpr> AST_IR_Codegen::reduceAssign(AST::AstAssign* astAssign, AST::ICollectInfoBack* collect) {
        auto env = _GetCurrentEnv();
        CollectIRValue collectValue1;
        astAssign->getResultExpr()->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue1);
        CollectIRValue collectValue2;
        astAssign->getExpr()->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue2);

        auto f = [this, &collectValue1, &collectValue2, &collect](IR::Instruction::OpCode op1, IR::Instruction::OpCode op2) {
            IR::Value* v = IR::IRBuilder(m_context).emitBinaryOpIns(IR::Instruction::OpCode::kAdd, collectValue1.getValue(), collectValue2.getValue());
            IR::Value* v2 = IR::IRBuilder(m_context).emitAssign(collectValue1.getValue(), v);
            static_cast<CollectIRValue*>(collect)->setValue(v2);
        };
        auto op = astAssign->getToken().toStringView();
        if (op == "=") {
            IR::Value* v = IR::IRBuilder(m_context).emitAssign(collectValue1.getValue(), collectValue2.getValue());
            static_cast<CollectIRValue*>(collect)->setValue(v);
            return nullptr;
        }
        else {
            if (op == "+=") {
                f(IR::Instruction::OpCode::kAdd, IR::Instruction::OpCode::kAssign);
                return nullptr;
            }
            else if (op == "-=") {
                f(IR::Instruction::OpCode::kMinus, IR::Instruction::OpCode::kAssign);
                return nullptr;
            }
            else if (op == "*=") {
                f(IR::Instruction::OpCode::kMul, IR::Instruction::OpCode::kAssign);
                return nullptr;
            }
            else if (op == "/=") {
                f(IR::Instruction::OpCode::kDiv, IR::Instruction::OpCode::kAssign);
                return nullptr;
            }
            else if (op == "%=") {
                f(IR::Instruction::OpCode::kMod, IR::Instruction::OpCode::kAssign);
                return nullptr;
            }
            else if (op == "|=") {
                f(IR::Instruction::OpCode::kOr, IR::Instruction::OpCode::kAssign);
                return nullptr;
            }
            else if (op == "&=") {
                f(IR::Instruction::OpCode::kAnd, IR::Instruction::OpCode::kAssign);
                return nullptr;
            }
            else if (op == "^=") {
                f(IR::Instruction::OpCode::kXor, IR::Instruction::OpCode::kAssign);
                return nullptr;
            }
            //else if (op == "<<=") {
            //    f(IR::Instruction::OpCode::k, IR::Instruction::OpCode::kAssign);
            //    return nullptr;
            //}
            //else if (op == ">>=") {
            //    f(IR::Instruction::OpCode::kOr, IR::Instruction::OpCode::kAssign);
            //    return nullptr;
            //}
            return nullptr;
        }
        return nullptr;
    }

    std::shared_ptr<AST::AstObjectExpr> AST_IR_Codegen::reduceExprs(AST::AstExprs* astExprs, AST::ICollectInfoBack* collect) {
        CollectIRValue collectValue;
        for (auto iter = astExprs->begin(); iter != astExprs->end(); ++iter) {
            (*iter)->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue);
        }
        static_cast<CollectIRValue*>(collect)->setValue(collectValue.getValue());
        return nullptr;
    }

    Symbol const* AST_IR_Codegen::_Find(std::string const& sym) const {
        return m_currentEnv->find(sym);
    }

    void AST_IR_Codegen::_StartVisitFunction() {
        m_localValueIndex = 0;
    }

    IR::Value* AST_IR_Codegen::_GenTempValue(IR::Type const* type) {
        IR::Value* v= IR::IRBuilder(m_context).emitAlloc(type, std::to_string(m_localValueIndex).c_str());
        m_localValueIndex++;
        return v;
    }
    

    std::string AST_IR_Codegen::_GenLabel() {
        std::string label = "L"+std::to_string(m_localValueIndex);
        m_localValueIndex++;
        return label;
    }
    IR::Instruction::OpCode AST_IR_Codegen::_GetBinaryOpCode(Token tok) const {
        return IR::Instruction::getOpCode(tok.toStringView());
    }
    IR::Instruction::OpCode AST_IR_Codegen::_GetUnaryOpCode(Token tok) const {
        return IR::Instruction::getOpCode(tok.toStringView());
    }
    IR::Type* AST_IR_Codegen::_GetType(std::string_view const& str_view) const {
        return m_context->getTypeManger().getTypeFromName(str_view);
    }
    std::shared_ptr<SymTable> AST_IR_Codegen::_GetCurrentEnv() const {
        return m_currentEnv;
    }
    void AST_IR_Codegen::_SetCurrentEnv(std::shared_ptr<SymTable> env) {
        m_currentEnv = env;
    }

}