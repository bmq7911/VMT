#pragma once
#include "Frontend/AST/AstVisitor.h"
#include "Backend/IR/IRContext.h"
#include "Diagnose/Diagnose.h"
#include "Backend/IR/IRBuilder.h"
#include "Backend/IRWriter/TextIRWriteVisitor.h"
#include "SymTable.h"
#include "Env.h"
#include <iostream>

namespace TS {
    class AST_IR_Codegen;

    // 本质上AST_IR_Codegen才是真正的语义分析过程,符号表本质上也是用于语义分析的上下文作用
    class AST_IR_Codegen  : public std::enable_shared_from_this<AST_IR_Codegen>, public AST::IASTVisitor {
    public:
        friend class EnvRAII;
        AST_IR_Codegen();

        void visitFunction(AST::AstFunction* astFunction, AST::ICollectInfoBack * collect );

        void visitForStmt(AST::AstForStmt* forstmt, AST::ICollectInfoBack* collect) override;

        void visitWhileStmt(AST::AstWhileStmt*, AST::ICollectInfoBack* collect) override;

        void visitDoWhileStmt(AST::AstDoWhileStmt*, AST::ICollectInfoBack* collect) override;

        void visitIfStmt(AST::AstIfStmt* ifstmt , AST::ICollectInfoBack* collect) override;

        void visitElseStmt(AST::AstElseStmt*, AST::ICollectInfoBack* collect) override;

        void visitStmts(AST::AstStmts*, AST::ICollectInfoBack* collect) override;

        void visitReturnStmt(AST::AstReturnStmt* ,AST::ICollectInfoBack* collect) override;

        void visitBreakStmt(AST::AstBreakStmt*, AST::ICollectInfoBack* collect) override;

        void visitContinueStmt(AST::AstContinueStmt*, AST::ICollectInfoBack* collect) override;

        void visitExprStmt(AST::AstExprStmt* astExprStmt, AST::ICollectInfoBack* collect) override;
        
        void visitType(AST::AstType*, AST::ICollectInfoBack* collect) override;

        void visitParamList(AST::AstParamList*, AST::ICollectInfoBack* collect) override;

        void visitBlock(AST::AstBlock* astBlock, AST::ICollectInfoBack* collect) override;


        std::shared_ptr<AST::AstObjectExpr> reduceBinaryOpExpr(AST::AstBinaryOpExpr* astBinaryOpExpr , AST::ICollectInfoBack* collect) override;

        std::shared_ptr<AST::AstObjectExpr> reduceUnaryOpExpr(AST::AstUnaryOpExpr* astUnaryExpr, AST::ICollectInfoBack* collect) override;

        std::shared_ptr<AST::AstObjectExpr> reduceConditionExpr(AST::AstConditionExpr* astConditionExpr, AST::ICollectInfoBack* collect) override;

        std::shared_ptr<AST::AstObjectExpr> reduceConstantExpr(AST::AstConstantExpr* astObjectExpr, AST::ICollectInfoBack* collect) override;

        std::shared_ptr<AST::AstObjectExpr> reduceObjectExpr(AST::AstObjectExpr* astObjectExpr, AST::ICollectInfoBack* collect) override;
        
        std::shared_ptr<AST::AstObjectExpr> reduceVoidExpr(AST::AstVoidExpr* astVoidExpr, AST::ICollectInfoBack* collect) override;

        // decl ::= type variable;
        //      ::= type variable = expr
        //      AstDecl -> type variable AssignExpr( variable,expr )
        std::shared_ptr<AST::AstObjectExpr> reduceDecl(AST::AstDecl* astDecl, AST::ICollectInfoBack* collect) override;

        std::shared_ptr<AST::AstObjectExpr> reduceDecls(AST::AstDecls* astDecls, AST::ICollectInfoBack* collect) override;
        
        // 这条语句很特殊,因为完成了定值操作
        std::shared_ptr<AST::AstObjectExpr> reduceAssign(AST::AstAssign* astAssign, AST::ICollectInfoBack* collect) override;

        std::shared_ptr<AST::AstObjectExpr> reduceExprs(AST::AstExprs* astExprs, AST::ICollectInfoBack* collect) override;

    private:
        Symbol const* _Find(std::string const& sym) const;
        template<typename T>
        T* _Cast(std::string const& sym) const {
            return m_currentEnv->get<T>(sym);
        }
        void _StartVisitFunction();
        IR::Value* _GenTempValue(IR::Type const* type);
        IR::Value* _GenTempValue(IR::Type const* type, const char * name);
        std::string _GenLabel();
        IR::Instruction::OpCode _GetBinaryOpCode(Token tok) const;
        IR::Instruction::OpCode _GetUnaryOpCode(Token tok) const;
        IR::Type* _GetType(std::string_view const& str_view) const;
        std::shared_ptr<SymTable>  _GetCurrentEnv() const;
        void _SetCurrentEnv(std::shared_ptr<SymTable> env);
    private:
        uint32_t                        m_localValueIndex;
        std::shared_ptr<SymTable>       m_env;
        std::shared_ptr<SymTable>       m_currentEnv;
        std::shared_ptr<IR::IRContext>  m_context;
    };

    class EnvRAII {
    public:
        EnvRAII( AST_IR_Codegen * codegen) 
            :m_codegen( codegen )
        {
            m_env = SymTable::makeSymTable( codegen->m_currentEnv );
        }
        ~EnvRAII() {
            if (nullptr != m_codegen)
                m_codegen->_SetCurrentEnv( m_env->getParent());
        }
        
    private:
        AST_IR_Codegen*           m_codegen;
        std::shared_ptr<SymTable> m_env;
    };

}