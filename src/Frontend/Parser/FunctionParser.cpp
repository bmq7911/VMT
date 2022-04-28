#pragma once
#include "Frontend/Parser/FunctionParser.h"
#include "SymbolTable/FunctionId.h"
#include "SymbolTable/ObjectId.h"
#include "SymbolTable/TopEnv.h"
#include "Frontend/AST/Type.h"
#include "Diagnose/Diagnose.h"

FunctionParser::FunctionParser(std::shared_ptr<TokenReader> reader)
    : ParserProxy(reader)
{}

/// function_def ::= type attribute func_name "=" func_body
std::shared_ptr<AST::Function> FunctionParser::begin( ) {
    std::shared_ptr<AST::Type> type = parseType( );
    std::shared_ptr<AST::Attribute> atrribuye = parseAttribute();
    auto tok = readToken();
    if( tok.not_match(TokenId::kw_id)){
        Diagnose::expectBut( TokenId::kw_id, tok);
    }
    tok = readToken();
    if( tok.not_match(TokenId::kw_equal)){
        Diagnose::expectBut( TokenId::kw_equal, tok);
    }
    std::shared_ptr<AST::FunctionBody> body = parseFunctionBody( );

    return nullptr;
}

std::shared_ptr<AST::Type> FunctionParser::parseType() {
    auto tok = readToken( );
    if( tok.not_match( TokenId::kw_id )){
            Diagnose::expectBut( TokenId::kw_id, tok);
    }
    return std::make_shared<AST::Type>( tok );
}


std::shared_ptr<AST::Attribute> FunctionParser::parseAttribute() {
    auto tok = readToken();
    if( tok.not_match(TokenId::kw_const)){

    }
}

std::shared_ptr<AST::FunctionBody> FunctionParser::parseFunctionBody( ){


}
std::shared_ptr<AST::Param> FunctionParser::param() {
    std::shared_ptr<AST::Param> param = std::make_shared<AST::Param>( );
    Token token = getTokenReader()->getToken();
    std::shared_ptr<ENV::TypeId> type = getEnv()->getTypeId( token.toString());
    if (type ) { 
        
    }
    else {
        
    }
    
    token = readToken();
    std::shared_ptr<ENV::ObjectId>        objectId = std::make_shared<ENV::ObjectId>(token.toString().c_str(), type );
    std::shared_ptr<AST::VariableObjExpr> idExpr   = std::make_shared<AST::VariableObjExpr>(token, type, objectId );
    param->addId(idExpr);
    /// ���ű���û��¼�����������
    getEnv()->put(token.toString(), objectId);
    token = readToken();
    /// 
    while ( token.match(TokenId::kw_comma)) {
        token = readToken();
        std::shared_ptr<ENV::TypeId> type = getEnv()->getTypeId(token.toString());
        if (type && ENV::SymbolType::kType == type->getSymbolType()) {
            
        }
        else {
        
        }
        token = readToken();
        token.match(TokenId::kw_id);
        /// �����AST�ϵ���Ϣ,AST�ϵ�Object��Ҫ֪���Լ��ڷ��ű�֮����??��Ҫ֪�����ű����������???
        std::shared_ptr<ENV::ObjectId> objectId = std::make_shared<ENV::ObjectId>(token.toString().c_str(),type);
        std::shared_ptr<AST::VariableObjExpr> idExpr = std::make_shared<AST::VariableObjExpr>(token, type, objectId );
        param->addId(idExpr);
        /// ���ű���û��¼�����������
        getEnv()->put(token.toString(), objectId);
        token = readToken();
    }
    return param;
}

std::shared_ptr<AST::ParamList>  FunctionParser::paramList() { /// �������Ϊ��,������û���۵�
    std::shared_ptr<AST::ParamList> paramList = std::make_shared<AST::ParamList>();
    Token token = readToken();
    std::shared_ptr<AST::Param> param = std::make_shared<AST::Param>();
    if (!token.match(TokenId::kw_r_paren)) {
        param = this->param();
    }
    paramList->setParam(param);
    return paramList;
}

/// <summary>
///  �����д���ǵݹ��½�����,ͨ���ݹ��½�����,����������ʽ,ͨ������ʽ�������������﷨�Ƶ�����,������﷨�Ƶ�������ָ�����ɳ����﷨��
///  �ں�����ɳ����﷨��������ַ��ʽʹ�õ��﷨�Ƶ������� ͨ������ʽ���������,�������﷨��ת��Ϊ����ַ��
/// </summary>
/// <returns></returns>
std::shared_ptr<AST::Stmt>     FunctionParser::parseFunctionBlock() {
    Token tok = readToken();
    if (tok.match( TokenId::kw_l_brace)) {
        return parseBlock();
    }
    return nullptr;
}

/// function_expr ::= expr_stmt
///               ::= block_stmt

std::shared_ptr<AST::Stmt> FunctionParser::parseFunctionExpr() {
    Token tok = advanceToken( );
    if (tok.match( TokenId::kw_l_brace)) {
        return parseFunctionBlock();
    }
    else {
        return parseStmt( );
    }
}

std::shared_ptr<AST::Stmt> FunctionParser::parseStmt() {
    Token tok = advanceToken( ); /// look forward a token to determine which subprocess 
    std::shared_ptr<AST::Stmt> stmt;
    switch (tok.getTokenId( )) {
    case TokenId::kw_l_brace: {
        stmt = parseBlock( );
    }break;
    case TokenId::kw_if: {
        stmt = parseIf( );
    }break;
    case TokenId::kw_for: {
        stmt = parseFor( );
    }break;
    case TokenId::kw_while: {
        stmt = parseWhile( );
    }break;
    case TokenId::kw_do: {
        stmt = parseDoWhile( );
    }break;
    case TokenId::kw_continue: {
        if (false == _IsInLoop( )) {
            //error("continue must in loop stmts");
        }
        tok = readToken();
        tok.match( TokenId::kw_semi);
        return std::make_shared<AST::ContinueStmt>();
    }break;
    case TokenId::kw_break: {
        if (false == _IsInLoop()) {
            //error("break must in loop stmts else switch stmts");
        }
        tok = readToken();
        tok.match( TokenId::kw_semi);
        return std::make_shared<AST::BreakStmt>();
    }break;
    case TokenId::kw_semi: { /// semikolon
        tok = readToken();
        return nullptr;
    }break;
    case TokenId::kw_return: {
        stmt = parseReturn();
        tok = readToken();
        tok.match(TokenId::kw_semi);
    }break;
    default: { /// ���Ǳ���ʽ
        std::shared_ptr<AST::Expr> expr = parseDeclOrExpr();
        if (expr) {
            stmt = std::make_shared<AST::ExprStmt>(expr);
            tok = readToken();
            tok.match( TokenId::kw_semi);
        }
        else {
            return stmt;
        }
    } break;
    }
    return stmt;
}


std::shared_ptr<AST::Stmt>                FunctionParser::parseBlock() {
    std::shared_ptr<ENV::Env> savedEnv = getEnv();
    std::shared_ptr<ENV::Env> f_env = std::make_shared<ENV::Env>(savedEnv);
    Token tok = getToken();
    tok.match( TokenId::kw_l_brace);
    std::shared_ptr<AST::Stmts> stmts = std::make_shared<AST::Stmts>();
    do {
        std::shared_ptr<AST::Stmt> stmt = parseStmt();
        stmts->add(stmt);
        //tok = readToken();
        tok = advanceToken( );
        if (tok.match(TokenId::kw_r_brace)) {
            readToken();
            break;
        }
    } while (true);
    tok.match(TokenId::kw_r_brace);
    setEnv(savedEnv);
    return stmts;
}

std::shared_ptr<AST::IfStmt>                  FunctionParser::parseIf( ) {
    Token tok = getToken();
    tok.match( TokenId::kw_if);
    tok = readToken();
    tok.match( TokenId::kw_l_paren);
    std::shared_ptr<AST::Expr> boolexpr = parseCommaExpr();
    tok = readToken();
    tok.match(TokenId::kw_r_paren);
    std::shared_ptr<AST::Stmt> stmt = parseStmt();
    tok = readToken();
    std::shared_ptr<AST::ElseStmt>  elseStmt;
    if (tok.match(TokenId::kw_else)) {
        elseStmt = parseElse();
    }
    std::shared_ptr< AST::IfStmt> ifStmt = std::make_shared<AST::IfStmt>(boolexpr, stmt, elseStmt);
    return ifStmt;
}

std::shared_ptr<AST::ElseStmt>                FunctionParser::parseElse() {
    Token tok = getToken();
    tok.match( TokenId::kw_else);
    std::shared_ptr<AST::Stmt> stmt = parseStmt();
    
    std::shared_ptr<AST::ElseStmt> elsestmt = std::make_shared<AST::ElseStmt>(stmt);
    return elsestmt;
}
std::shared_ptr<AST::ForStmt>             FunctionParser::parseFor(){
    _EntryLoop();
    Token tok = readToken();
    tok.match( TokenId::kw_l_paren );
    readToken();
    std::shared_ptr< AST::Expr> initExpr = parseDeclOrExpr();
    tok = readToken();
    tok.match( TokenId::kw_semi);
    readToken();
    std::shared_ptr<AST::Expr> boolExpr = parseDeclOrExpr();
    std::shared_ptr<ENV::TypeId> boolType = boolExpr->getTypeId();
    if (boolType != ENV::getTopEnv()->getBasicType(ENV::BasicType::kBool)) {
        /// ������һ������,��ô��ʾ�������
        /// ��ν��д�����
        std::cout <<"the bool expr must bool type in for loop stmt" <<std::endl;
    }
    tok = readToken();
    tok.match( TokenId::kw_semi);
    readToken();
    std::shared_ptr<AST::Expr> tailExpr = parseDeclOrExpr();
    tok = readToken();
    tok.match( TokenId::kw_r_paren);

    std::shared_ptr<AST::Stmt> stmt = parseStmt();

    std::shared_ptr<AST::ForStmt> forLoop = std::make_shared<AST::ForStmt>(initExpr, boolExpr, tailExpr, stmt);
    _LeaveLoop();
    return forLoop;
}
/// break �� continue not support right now
std::shared_ptr<AST::WhileStmt>           FunctionParser::parseWhile() {
    _EntryLoop();
    Token tok = readToken();
    tok.match( TokenId::kw_l_paren);
    std::shared_ptr<AST::Expr> boolexpr = parseCommaExpr();
    auto type = boolexpr->getTypeId();
    //if (type != ENV::getTopEnv()->getBasicType(ENV::BasicType::kBool)) {
    //    
    //    std::cout << "&&&&&&&&&&&&&&\nnot bool Expr\n&&&&&&&&&&&&" <<std::endl;
    //}
    tok = getToken();
    tok.match( TokenId::kw_r_paren);
    readToken();
    std::shared_ptr<AST::Stmt> stmt = parseStmt();
    _LeaveLoop();
    return std::make_shared<AST::WhileStmt>( boolexpr, stmt);
}


std::shared_ptr<AST::DoWhileStmt>              FunctionParser::parseDoWhile() {
    _EntryLoop();
    std::shared_ptr<AST::Stmt> stmt = parseStmt();
    Token tok = readToken();
    tok.match( TokenId::kw_while);
    tok = readToken();
    tok.match(TokenId::kw_l_paren);
    std::shared_ptr<AST::Expr> whileExpr = parseCommaExpr();
    tok = readToken();
    tok.match( TokenId::kw_r_paren);
    tok = readToken();
    tok.match( TokenId::kw_semi);
    _LeaveLoop();
    return std::make_shared<AST::DoWhileStmt>( whileExpr, stmt);

}

std::shared_ptr<AST::Stmt>                FunctionParser::parseReturn() {
    std::shared_ptr<AST::Expr> expr = parseCommaExpr();
    Token tok = getToken();
    tok.match( TokenId::kw_semi);
    std::shared_ptr<AST::ExprStmt> exprStmt = std::make_shared<AST::ExprStmt>( expr);
    std::shared_ptr<AST::ReturnStmt> returnStmt = std::make_shared<AST::ReturnStmt>( exprStmt);
    return returnStmt;
}

std::shared_ptr<AST::Expr>                FunctionParser::parseDeclOrExpr() {
    Token tok = readToken();
    std::shared_ptr<AST::Expr> expr;
    switch (tok.getTokenId()) {
    case TokenId::kw_i8:
    case TokenId::kw_i16:
    case TokenId::kw_i32:
    case TokenId::kw_i64:
    case TokenId::kw_ui8:
    case TokenId::kw_ui16:
    case TokenId::kw_ui32:
    case TokenId::kw_ui64:
    case TokenId::kw_f32:
    case TokenId::kw_f64:
    case TokenId::kw_bool: { /// ����������
        std::shared_ptr<ENV::TypeId> type = getEnv()->getTypeId(tok.toString());
        expr = parseDecl(type);
    }break;
    case TokenId::kw_id: {
        std::shared_ptr<ENV::TypeId> type = getEnv()->getTypeId( tok.toString() );
        if (type) { /// ����
            expr = parseDecl(type);
        }
        else { ///
            //fallbackToken(); /// ��Expr�Ľ����߼��Լ�������������
            expr= parseCommaExpr();
        }
    }break;
    case TokenId::kw_void: 
    default: {/// ����Ӧ�ñ���
        expr = nullptr;
    } break;
    }
    return returnExpr(expr);
}


std::shared_ptr<AST::Expr>            FunctionParser::parseDecl(std::shared_ptr<ENV::TypeId> type) {
    Token mark;
    std::shared_ptr<AST::Exprs> exprs = std::make_shared<AST::Exprs>();
    do {
        Token id = readToken();
        id.match( TokenId::kw_id);
        mark = readToken();
        if (mark.match(TokenId::kw_equal)) {
            std::shared_ptr<AST::Expr> assignExpr = parseAssignExpr();
            std::shared_ptr<ENV::ObjectId> obj = std::make_shared<ENV::ObjectId>( id.toString().c_str(), type);
            std::shared_ptr<AST::VariableObjExpr> objExpr = std::make_shared<AST::VariableObjExpr>(id, type, obj);
            //std::shared_ptr<ENV::ObjectId> obj = std::make_shared<ENV::ObjectId>( id.toString().c_str(), objExpr);
            getEnv()->put(id.toString(), obj);
            //std::shared_ptr<AST::BinaryOpExpr> assignOp = std::make_shared<AST::BinaryOpExpr>( objExpr, assignExpr, mark  );
            std::shared_ptr<AST::BinaryOpExpr> assignOp = AST::BinaryOpExpr::makeBinaryOpExpr(objExpr, assignExpr, mark);
            exprs->add(assignOp);

            mark = getToken();
        }
        else {
            std::shared_ptr<ENV::ObjectId> obj = std::make_shared<ENV::ObjectId>(id.toString().c_str(), type);
            std::shared_ptr<AST::VariableObjExpr> objExpr = std::make_shared<AST::VariableObjExpr>(id, type, obj);
            getEnv()->put(id.toString(), obj);
            exprs->add(objExpr);
        }
    } while (mark.match(TokenId::kw_comma));


    return exprs;
}

std::shared_ptr<AST::Expr>                FunctionParser::parseCommaExpr() {
    std::shared_ptr<AST::Expr> expr = parseAssignExpr();
    Token tok = readToken();
    if (tok.match(TokenId::kw_comma)) {
        std::shared_ptr<AST::Expr> binaryOpExpr  = expr;
        while (tok.match(TokenId::kw_comma)) {
            std::shared_ptr<AST::Expr> right = parseAssignExpr();
            //binaryOpExpr = std::make_shared<AST::BinaryOpExpr>(binaryOpExpr, right, tok);
            binaryOpExpr = AST::BinaryOpExpr::makeBinaryOpExpr(binaryOpExpr, right, tok);
            tok = readToken();
        }
        return returnExpr(binaryOpExpr);
    }
    else {
        return returnExpr(expr);
    }
}

std::shared_ptr<AST::Expr>                FunctionParser::parseAssignExpr() {
    std::shared_ptr<AST::Expr> expr = parseConditionExpr();
    Token tok = readToken();

    switch (tok.getTokenId()){
        case TokenId::kw_equal: {
            std::shared_ptr<AST::Expr> right = parseAssignExpr(); /// ����һ�ֵݹ����ʽ
            //return returnExpr( std::make_shared<AST::BinaryOpExpr>( expr, right, tok));
            return returnExpr(AST::BinaryOpExpr::makeBinaryOpExpr(expr, right, tok));
        }break;
        case TokenId::kw_starequal:
        case TokenId::kw_slashequal:
        case TokenId::kw_plusequal:
        case TokenId::kw_minusequal:
        case TokenId::kw_percentequal:
        case TokenId::kw_lesslessequal:
        case TokenId::kw_greatergreaterequal: {
            std::shared_ptr<AST::Expr> right = parseConditionExpr();

            //std::shared_ptr<AST::BinaryOpExpr> binaryOpExpr = std::make_shared<AST::BinaryOpExpr>( expr, binaryOpExpr, tok );
            auto binaryOpExpr = AST::BinaryOpExpr::makeBinaryOpExpr(expr, right, tok);
        }break;
        default: {
            return returnExpr(expr);
        }
        break;
    }
}

std::shared_ptr<AST::Expr>                FunctionParser::parseConditionExpr() {
    std::shared_ptr<AST::Expr> condition = parseBool();
    Token tok = readToken();
    /// ��������ʽ
    if (tok.match(TokenId::kw_question)) {
        std::shared_ptr<AST::Expr> True = parseBool();
        Token tok = readToken();
        tok.match( TokenId::kw_colon);
        std::shared_ptr<AST::Expr> False = parseBool();
        return returnExpr( std::make_shared<AST::ConditionExpr>(condition, True, False));
    }
    else {
        return returnExpr(condition);
    }



}
/// ����ʵ����������ȼ�
std::shared_ptr<AST::Expr>                FunctionParser::parseBool() {
    std::shared_ptr<AST::Expr>  binaryOpExpr = parseJoin();
    Token tok = readToken();
    while (tok.match(TokenId::kw_or)) {
        std::shared_ptr<AST::Expr> right = parseJoin();
        //binaryOpExpr = std::make_shared<AST::BinaryOpExpr>(binaryOpExpr, right, tok);
        binaryOpExpr = AST::BinaryOpExpr::makeBinaryOpExpr(binaryOpExpr, right, tok);
        tok = readToken();
    }
    return returnExpr(binaryOpExpr);
}

std::shared_ptr<AST::Expr>                FunctionParser::parseJoin() {
    std::shared_ptr<AST::Expr>  binaryOpExpr = parseEquality();
    Token tok = readToken();
    while (tok.match(TokenId::kw_and) ) {
        std::shared_ptr<AST::Expr> right = parseEquality();
        //binaryOpExpr = std::make_shared<AST::BinaryOpExpr>(binaryOpExpr, right, tok);
        binaryOpExpr = AST::BinaryOpExpr::makeBinaryOpExpr(binaryOpExpr, right, tok);
        tok = readToken();
    }
    return returnExpr(binaryOpExpr);
}

std::shared_ptr<AST::Expr>                FunctionParser::parseEquality() {
    std::shared_ptr<AST::Expr>  binaryOpExpr = parseRel();
    Token tok = readToken();
    if (tok.match(TokenId::kw_equalequal) || tok.match(TokenId::kw_exclaimequal) ) {
        std::shared_ptr<AST::Expr> right = parseRel();
        //binaryOpExpr = std::make_shared<AST::BinaryOpExpr>(binaryOpExpr, right, tok);
        binaryOpExpr = AST::BinaryOpExpr::makeBinaryOpExpr(binaryOpExpr, right, tok);
    }
    return returnExpr(binaryOpExpr);
}

std::shared_ptr<AST::Expr>                FunctionParser::parseRel() {
    std::shared_ptr<AST::Expr>  binaryOpExpr = parseExpr();
    Token tok = readToken();
    if (tok.match(TokenId::kw_less) || tok.match(TokenId::kw_lessequal) || tok.match(TokenId::kw_greater) || tok.match(TokenId::kw_greaterequal)) {
        std::shared_ptr<AST::Expr> right = parseExpr();
        auto type = binaryOpExpr->getTypeId( );
        //binaryOpExpr = std::make_shared<AST::BinaryOpExpr>(binaryOpExpr, right, tok);
        binaryOpExpr = AST::BinaryOpExpr::makeBinaryOpExpr(binaryOpExpr, right, tok);
    }
    return returnExpr(binaryOpExpr);
}

std::shared_ptr<AST::Expr>                FunctionParser::parseExpr() {
    std::shared_ptr<AST::Expr>  binaryOpExpr = parseTerm();
    Token tok = readToken();
    while (tok.match(TokenId::kw_plus) || tok.match(TokenId::kw_minus)) {
        std::shared_ptr<AST::Expr> right = parseTerm();
        //binaryOpExpr = std::make_shared<AST::BinaryOpExpr>(binaryOpExpr, right, tok);
        binaryOpExpr = AST::BinaryOpExpr::makeBinaryOpExpr(binaryOpExpr, right, tok);
        tok = readToken();
    }
    return returnExpr(binaryOpExpr);

}

std::shared_ptr<AST::Expr>                FunctionParser::parseTerm() {
    /// 1.ͨ���ݹ�ʵ�� 
    /// 2.ͨ��ѭ��ʵ�� ���˵��ĳ����ʽ�ĵݹ����ת��Ϊѭ��,β�ݹ��ǿ��Ե�
    /// term -> term * factor | term / factor | factor ����������Ƿ�β�ݹ�,�ǻ���������ѭ����,�������ǿ����ֶ�
    /// ��ֹ�ݹ�
    /// 3.�ҵ�LeftPair��ƵĽṹ��Ϊ���з���ؽṹ��Ƶ� �� a * b * c * d;���ֽṹ�Ǵ�����ص�
    /// 4.�� stmts -> stmts stmt ���Ǵ��в���ؽṹ,���ʱ�����ǿ��� leftPair ,������ʵ�� Stmts���AST
    std::shared_ptr<AST::Expr>  binaryOpExpr = parseUnary();
    Token tok = readToken( ); ///�ѵ���ʲôʱ���read,ʲôʱ���get
    while (tok.match(TokenId::kw_star) || tok.match(TokenId::kw_slash)) {
        std::shared_ptr<AST::Expr> right = parseUnary();
        //binaryOpExpr = std::make_shared<AST::BinaryOpExpr>(binaryOpExpr, right, tok);
        binaryOpExpr = AST::BinaryOpExpr::makeBinaryOpExpr(binaryOpExpr, right, tok);
        tok = readToken( );
    }
    return returnExpr(binaryOpExpr);
}

std::shared_ptr<AST::Expr>                FunctionParser::parseUnary() {
    Token tok = readToken();
    if (tok.getTokenId() == TokenId::kw_not || tok.getTokenId() == TokenId::kw_minus) {
        std::shared_ptr<AST::Expr> factor = parseFactor();
        std::shared_ptr<AST::UnaryOpExpr> expr = AST::UnaryOpExpr::makeUnaryOpExpr( factor, tok);
        readToken();
        return returnExpr(expr);
    }
    else {
        auto expr = parseFactor();
        readToken();
        return returnExpr(expr);
    }
}

/// ����ʵ����������ȼ�
std::shared_ptr<AST::Expr>                FunctionParser::parseFactor() {
    Token tok = getToken();
    switch (tok.getTokenId()) {
    case TokenId::kw_l_paren: {
        std::shared_ptr<AST::Expr> expr = parseCommaExpr();
        tok = readToken();
        tok.match( TokenId::kw_r_paren);
        return expr;
    }break;
    case TokenId::kw_id: {
        std::shared_ptr<ENV::ObjectId> id= getEnv()->getObjectId(tok.toString());
        if (nullptr == id) {
            std::string errMsg = "the id " + tok.toString() + " not found";
            //error(errMsg.c_str());
        }
        std::shared_ptr<ENV::TypeId> type = id->getObjType();
        std::shared_ptr<AST::VariableObjExpr> objExpr = std::make_shared<AST::VariableObjExpr>(tok, type,id);
        
        return objExpr;
    }break;
    case TokenId::kw_true: {
        std::shared_ptr<ENV::TypeId> type = ENV::TopEnv::getBasicType(ENV::BasicType::kBool);
        //std::shared_ptr<ENV::ObjectId> id = getEnv()->getObjectId("true");
        //std::shared_ptr<ENV::TypeId>   type = id->getObjType();
        std::shared_ptr<AST::ConstantExpr<bool>> objExpr = std::make_shared<AST::ConstantExpr<bool>>( type,tok, true);
        return objExpr;
    }break;
    case TokenId::kw_false: {
        //std::shared_ptr<ENV::ObjectId> id = getEnv()->getObjectId("false");
        //std::shared_ptr<ENV::TypeId> type = id->getObjType();
        std::shared_ptr<ENV::TypeId> type = ENV::TopEnv::getBasicType(ENV::BasicType::kBool);
        std::shared_ptr<AST::ConstantExpr<bool>> objExpr = std::make_shared<AST::ConstantExpr<bool>>(type,tok,false);
        return objExpr;
    }break;
    case TokenId::kw_integer: {
        std::shared_ptr<ENV::TypeId> type = ENV::TopEnv::getBasicType(ENV::BasicType::kI32);
        std::shared_ptr<AST::ConstantExpr<int8_t>> constId = std::make_shared<AST::ConstantExpr<int8_t>>( type,tok,1 );
        return constId;
    }break;
    case TokenId::kw_real: {
        std::shared_ptr<ENV::TypeId> type = ENV::TopEnv::getBasicType(ENV::BasicType::kF32);
        std::shared_ptr<AST::ConstantExpr<float>> constId = std::make_shared<AST::ConstantExpr<float>>(type, tok, 1.0f);
        return constId;
    }break;
    default: {
        //std::shared_ptr<ENV::TypeId> type = ENV::TopEnv::getBasicType(ENV::BasicType::kVoid);
        std::shared_ptr<AST::VoidExpr> voidExpr = std::make_shared<AST::VoidExpr>();
        return voidExpr;
        break;
    }
    }
}


std::shared_ptr<AST::Expr>            FunctionParser::returnExpr(std::shared_ptr<AST::Expr> expr) {
    ///fallbackToken();
    return expr;
}
void FunctionParser::_EntryLoop() {
    m_entryLoop++;
}
void FunctionParser::_LeaveLoop() {
    m_entryLoop--;
}
bool FunctionParser::_IsInLoop() {
    return 0 != m_entryLoop;
}

