
#include "Frontend/Parser/FunctionParser.h"
#include "SymbolTable/FunctionId.h"
#include "SymbolTable/ObjectId.h"
#include "Frontend/AST/AstOther/AstType.h"
#include "Diagnose/Diagnose.h"

FunctionParser::FunctionParser(std::shared_ptr<TokenReader> reader)
    : ParserProxy(reader)
{}

/// function_def ::= type attribute func_name "=" func_body
std::shared_ptr<AST::AstFunction> FunctionParser::begin( ) {
    std::shared_ptr<AST::AstType> type = parseType( );
    std::shared_ptr<AST::AstAttribute> atrribuye = parseAttribute();
    auto name = readToken();
    if( name.notMatch(TokenId::kw_id)){
        Diagnose::expectBut( TokenId::kw_id, name );
    }
    auto tok = readToken();
    if( tok.notMatch(TokenId::kw_equal)){
        Diagnose::expectBut( TokenId::kw_equal, tok);
        return nullptr;
    }
    tok = readToken();
    if (tok.notMatch(TokenId::kw_func)) {
        Diagnose::expectBut(TokenId::kw_func, tok);
        return nullptr;
    }
    std::shared_ptr<AST::AstParamList> paramList = parseParamList();
    tok = readToken();
    if (tok.notMatch(TokenId::kw_arrow)) {
        Diagnose::expectBut(TokenId::kw_arrow, tok);
        return nullptr;
    }
    std::shared_ptr<AST::AstBlock> block = parseBlock();
    std::shared_ptr<AST::AstFunction> function = std::make_shared<AST::AstFunction>( name, type,paramList, block);
    return function;
}

std::shared_ptr<AST::AstType> FunctionParser::parseType() {
    auto tok = readToken( );
    if( tok.notMatch( TokenId::kw_id )){
            Diagnose::expectBut( TokenId::kw_id, tok);
    }
    return std::make_shared<AST::AstType>( tok );
}


std::shared_ptr<AST::AstAttribute> FunctionParser::parseAttribute() {
    //auto tok = readToken( );
    auto tok = advanceToken( );
    if( tok.match(TokenId::kw_const, TokenId::kw_static)){
        tok = readToken( );
        return std::make_shared<AST::AstAttribute>(tok);
    }
    else if (tok.match(TokenId::kw_id) && tok.toStringView() == "__attribute__") {
        tok = readToken( );
    }
    return nullptr;
}

/// function_body::="func" "(" function_decl_param_list ")" "->" function_stmt
///              ::= call_stmt ";"


std::shared_ptr<AST::AstStmt> FunctionParser::parseFunctionStmt() {
    Token tok = advanceToken();
    if (tok.match(TokenId::kw_l_brace)) {
        return parseFunctionBlock();
    }
    else {
        return parseFunctionExpr( );
    }

}

// paramlist ::="(" params ")"
// params ::= ε
// params_l ::= param_l
// params_l ::= param , param_l
// param    ::= type objname

std::shared_ptr<AST::AstParamList>  FunctionParser::parseParamList() {
    std::shared_ptr<AST::AstParamList> paramList = std::make_shared<AST::AstParamList>();
    auto tok = readToken();
    //1. deal the left paren
    if (tok.notMatch(TokenId::kw_l_paren)) {
        Diagnose::expectBut(TokenId::kw_l_paren, tok);
        return nullptr;
    }
    //2. look forward the token to check is right paren
    tok = advanceToken();
    if (tok.match(TokenId::kw_r_paren)) { //2.1 the next token is right paren
        tok = readToken();                //    we consume the token
        return paramList;
    }
    else {
        //2.2 there is a param list
        do {
            auto type = readToken();
            //2.2.1 we except the token is a type(id)
            if (type.notMatch(TokenId::kw_id)) {
                Diagnose::expectBut(TokenId::kw_id, type);
            }
            auto id = readToken();
            //2.2.2 we ecpect the token is a id
            if (id.notMatch(TokenId::kw_id)) {
                Diagnose::expectBut(TokenId::kw_id,id);
            }
            paramList->addParam(type, id );
            //2.2.3 check to see if there is a next param
            tok = advanceToken( );
            if (tok.match(TokenId::kw_comma)) {
                tok = readToken();
                continue;
            }
            else {
                break;
            }
        } while ( true );
    }

    tok = readToken();
    if (tok.notMatch(TokenId::kw_r_paren)) {
        Diagnose::expectBut(TokenId::kw_r_paren, tok);
        return nullptr;
    }
    return paramList;
}

/// function_block ::= block_stmt
std::shared_ptr<AST::AstStmt>     FunctionParser::parseFunctionBlock() {
    return parseBlock();
}

/// function_expr ::= expr_stmt
///               ::= block_stmt

std::shared_ptr<AST::AstStmt> FunctionParser::parseFunctionExpr() {
    Token tok = advanceToken( );
    if (tok.match( TokenId::kw_l_brace)) {
        return parseFunctionBlock();
    }
    else {
        return parseStmt( );
    }
}

std::shared_ptr<AST::AstStmt> FunctionParser::parseStmt() {
    Token tok = advanceToken( ); /// look forward a token to determine which subprocess 
    std::shared_ptr<AST::AstStmt> stmt;
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
        return std::make_shared<AST::AstContinueStmt>();
    }break;
    case TokenId::kw_break: {
        if (false == _IsInLoop()) {
            //error("break must in loop stmts else switch stmts");
        }
        tok = readToken();
        tok.match( TokenId::kw_semi);
        return std::make_shared<AST::AstBreakStmt>();
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
    default: { 
        std::shared_ptr<AST::AstExpr> expr = parseDeclOrExpr();
        if (expr) {
            stmt = std::make_shared<AST::AstExprStmt>(expr);
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


std::shared_ptr<AST::AstBlock>                FunctionParser::parseBlock( ) {
    Token tok = readToken();
    tok.match( TokenId::kw_l_brace);
    std::shared_ptr<AST::AstBlock> block = std::make_shared<AST::AstBlock>( );
    do {
        std::shared_ptr<AST::AstStmt> stmt = parseStmt();
        block->addStmt(stmt);
        tok = advanceToken( );
        if (tok.match(TokenId::kw_r_brace)) {
            readToken();
            break;
        }
        // 由于源代码本身不符合语法规则而导致的问题,该怎么处理,特别是EOF
        //else if (tok.match(TokenId::kw_eof)) { }
    } while (true);
    return block;
}

std::shared_ptr<AST::AstIfStmt>                  FunctionParser::parseIf( ) {
    Token tok = getToken();
    tok.match( TokenId::kw_if);
    tok = readToken();
    tok.match( TokenId::kw_l_paren);
    std::shared_ptr<AST::AstExpr> boolexpr = parseCommaExpr();
    tok = readToken();
    tok.match(TokenId::kw_r_paren);
    std::shared_ptr<AST::AstStmt> stmt = parseStmt();
    tok = readToken();
    std::shared_ptr<AST::AstElseStmt>  elseStmt;
    if (tok.match(TokenId::kw_else)) {
        elseStmt = parseElse();
    }
    std::shared_ptr< AST::AstIfStmt> ifStmt = std::make_shared<AST::AstIfStmt>(boolexpr, stmt, elseStmt);
    return ifStmt;
}

std::shared_ptr<AST::AstElseStmt>                FunctionParser::parseElse() {
    Token tok = getToken();
    tok.match( TokenId::kw_else);
    std::shared_ptr<AST::AstStmt> stmt = parseStmt();
    
    std::shared_ptr<AST::AstElseStmt> elsestmt = std::make_shared<AST::AstElseStmt>(stmt);
    return elsestmt;
}
std::shared_ptr<AST::AstForStmt>             FunctionParser::parseFor(){
    _EntryLoop();
    Token tok = readToken();
    tok.match( TokenId::kw_l_paren );
    readToken();
    std::shared_ptr< AST::AstExpr> initExpr = parseDeclOrExpr();
    tok = readToken();
    tok.match( TokenId::kw_semi);
    readToken();
    std::shared_ptr<AST::AstExpr> boolExpr = parseDeclOrExpr();
    //std::shared_ptr<ENV::TypeId> boolType = boolExpr->getTypeId();
    //if (boolType != ENV::getTopEnv()->getBasicType(ENV::BasicType::kBool)) {
    //    std::cout <<"the bool expr must bool type in for loop stmt" <<std::endl;
    //}
    tok = readToken();
    tok.match( TokenId::kw_semi);
    readToken();
    std::shared_ptr<AST::AstExpr> tailExpr = parseDeclOrExpr();
    tok = readToken();
    tok.match( TokenId::kw_r_paren);

    std::shared_ptr<AST::AstStmt> stmt = parseStmt();

    std::shared_ptr<AST::AstForStmt> forLoop = std::make_shared<AST::AstForStmt>(initExpr, boolExpr, tailExpr, stmt);
    _LeaveLoop();
    return forLoop;
}
std::shared_ptr<AST::AstWhileStmt>           FunctionParser::parseWhile() {
    _EntryLoop();
    Token tok = readToken();
    tok.match( TokenId::kw_l_paren);
    std::shared_ptr<AST::AstExpr> boolexpr = parseCommaExpr();
    //auto type = boolexpr->getTypeId();
    //if (type != ENV::getTopEnv()->getBasicType(ENV::BasicType::kBool)) {
    //    
    //    std::cout << "&&&&&&&&&&&&&&\nnot bool Expr\n&&&&&&&&&&&&" <<std::endl;
    //}
    tok = getToken();
    tok.match( TokenId::kw_r_paren);
    readToken();
    std::shared_ptr<AST::AstStmt> stmt = parseStmt();
    _LeaveLoop();
    return std::make_shared<AST::AstWhileStmt>( boolexpr, stmt);
}


std::shared_ptr<AST::AstDoWhileStmt>              FunctionParser::parseDoWhile() {
    _EntryLoop();
    std::shared_ptr<AST::AstStmt> stmt = parseStmt();
    Token tok = readToken();
    tok.match( TokenId::kw_while);
    tok = readToken();
    tok.match(TokenId::kw_l_paren);
    std::shared_ptr<AST::AstExpr> whileExpr = parseCommaExpr();
    tok = readToken();
    tok.match( TokenId::kw_r_paren);
    tok = readToken();
    tok.match( TokenId::kw_semi);
    _LeaveLoop();
    return std::make_shared<AST::AstDoWhileStmt>( whileExpr, stmt);

}

std::shared_ptr<AST::AstStmt>                FunctionParser::parseReturn() {
    std::shared_ptr<AST::AstExpr> expr = parseCommaExpr();
    Token tok = getToken();
    tok.match( TokenId::kw_semi);
    std::shared_ptr<AST::AstExprStmt> exprStmt = std::make_shared<AST::AstExprStmt>( expr);
    std::shared_ptr<AST::AstReturnStmt> returnStmt = std::make_shared<AST::AstReturnStmt>( exprStmt);
    return returnStmt;
}
// decl ::=type id  ";" | "=" expr ';'
// main_expr ::= decl_expr 
//           ::= compute_exprs
std::shared_ptr<AST::AstExpr>                FunctionParser::parseDeclOrExpr() {
    Token tok = advanceToken();
    if (tok.match(TokenId::kw_id)) {
        // 这里就会存在一个问题,那就是
        tok = readToken();
        auto nextToken = advanceToken();
        if (nextToken.match(TokenId::kw_id)) { // this condition indicate that there is a declaretion express
            auto type = tok;
            std::shared_ptr<AST::AstDecls> decls = std::make_shared<AST::AstDecls>( );
            do {
                auto name = readToken();
                tok = readToken();
                if (tok.notMatch(TokenId::kw_equal)) {
                
                }
                std::shared_ptr<AST::AstExpr>   expr = parseExpr();
                std::shared_ptr<AST::AstAssign> assignExpr = std::make_shared<AST::AstAssign>( name , expr );
                std::shared_ptr<AST::AstDecl>   declExpr   = std::make_shared<AST::AstDecl>( type, name, assignExpr );
                tok = advanceToken();
                
                decls->push( declExpr);
            } while ( tok.match(TokenId::kw_comma));
            return decls;
        }
        else { /// with must a expr
            nextToken = readToken( );
            auto leftExpr = std::make_shared<AST::AstVariableObjExpr>(tok);
            auto rightExpr = parseExpr( );
            if (nullptr == rightExpr) {
                return leftExpr;
            }
            else {
                return std::make_shared<AST::AstBinaryOpExpr>( leftExpr, rightExpr, nextToken);
            }
            //return 
        }
    }
    else {
        return parseExpr( );
    }

}


std::shared_ptr<AST::AstExpr>            FunctionParser::parseDecl(std::shared_ptr<ENV::TypeId> type) {
    
    Token mark;
    std::shared_ptr<AST::AstExprs> exprs = std::make_shared<AST::AstExprs>();
    do {
        Token id = readToken();
        id.match( TokenId::kw_id);
        mark = readToken();
        if (mark.match(TokenId::kw_equal)) {
            std::shared_ptr<AST::AstExpr> assignExpr = parseAssignExpr();
            std::shared_ptr<AST::AstVariableObjExpr> objExpr = std::make_shared<AST::AstVariableObjExpr>(id);
            std::shared_ptr<AST::AstBinaryOpExpr> assignOp = AST::AstBinaryOpExpr::makeBinaryOpExpr(objExpr, assignExpr, mark);
            exprs->add(assignOp);

            mark = getToken();
        }
        else {
            std::shared_ptr<AST::AstVariableObjExpr> objExpr = std::make_shared<AST::AstVariableObjExpr>(id );
            exprs->add(objExpr);
        }
    } while (mark.match(TokenId::kw_comma));


    return exprs;
    
    return nullptr;
}

std::shared_ptr<AST::AstExpr>                FunctionParser::parseCommaExpr() {
    std::shared_ptr<AST::AstExpr> expr = parseAssignExpr();
    Token tok = readToken();
    if (tok.match(TokenId::kw_comma)) {
        std::shared_ptr<AST::AstExpr> binaryOpExpr  = expr;
        while (tok.match(TokenId::kw_comma)) {
            std::shared_ptr<AST::AstExpr> right = parseAssignExpr();
            //binaryOpExpr = std::make_shared<AST::AstBinaryOpExpr>(binaryOpExpr, right, tok);
            binaryOpExpr = AST::AstBinaryOpExpr::makeBinaryOpExpr(binaryOpExpr, right, tok);
            tok = readToken();
        }
        return returnExpr(binaryOpExpr);
    }
    else {
        return returnExpr(expr);
    }
}

std::shared_ptr<AST::AstExpr>                FunctionParser::parseAssignExpr() {
    std::shared_ptr<AST::AstExpr> expr = parseConditionExpr();
    Token tok = advanceToken();

    switch (tok.getTokenId()){
        case TokenId::kw_equal: {
            std::shared_ptr<AST::AstExpr> right = parseAssignExpr(); ///
            //return returnExpr( std::make_shared<AST::AstBinaryOpExpr>( expr, right, tok));
            return returnExpr(AST::AstBinaryOpExpr::makeBinaryOpExpr(expr, right, tok));
        }break;
        case TokenId::kw_starequal:
        case TokenId::kw_slashequal:
        case TokenId::kw_plusequal:
        case TokenId::kw_minusequal:
        case TokenId::kw_percentequal:
        case TokenId::kw_lesslessequal:
        case TokenId::kw_greatergreaterequal: {
            std::shared_ptr<AST::AstExpr> right = parseConditionExpr();

            //std::shared_ptr<AST::AstBinaryOpExpr> binaryOpExpr = std::make_shared<AST::AstBinaryOpExpr>( expr, binaryOpExpr, tok );
            auto binaryOpExpr = AST::AstBinaryOpExpr::makeBinaryOpExpr(expr, right, tok);
        }break;
        default: {
            return returnExpr(expr);
        }
        break;
    }
}

std::shared_ptr<AST::AstExpr>                FunctionParser::parseConditionExpr() {
    std::shared_ptr<AST::AstExpr> condition = parseBool();
    Token tok = advanceToken();

    if (tok.match(TokenId::kw_question)) {
        tok = readToken();
        std::shared_ptr<AST::AstExpr> True = parseBool();
        Token tok = advanceToken();
        if (tok.notMatch(TokenId::kw_colon)) {
            Diagnose::expectBut(TokenId::kw_colon, tok);
            return nullptr;
        }
        std::shared_ptr<AST::AstExpr> False = parseBool();
        return returnExpr( std::make_shared<AST::AstConditionExpr>(condition, True, False));
    }
    else {
        return returnExpr(condition);
    }



}

std::shared_ptr<AST::AstExpr>                FunctionParser::parseBool() {
    std::shared_ptr<AST::AstExpr>  binaryOpExpr = parseJoin();
    Token tok = advanceToken();
    while (tok.match(TokenId::kw_or)) {
        tok = readToken();
        std::shared_ptr<AST::AstExpr> right = parseJoin();
        //binaryOpExpr = std::make_shared<AST::AstBinaryOpExpr>(binaryOpExpr, right, tok);
        binaryOpExpr = AST::AstBinaryOpExpr::makeBinaryOpExpr(binaryOpExpr, right, tok);
        tok = advanceToken();
    }
    return returnExpr(binaryOpExpr);
}

std::shared_ptr<AST::AstExpr>                FunctionParser::parseJoin() {
    std::shared_ptr<AST::AstExpr>  binaryOpExpr = parseEquality();
    Token tok = advanceToken();
    while (tok.match(TokenId::kw_and) ) {
        tok = readToken();
        std::shared_ptr<AST::AstExpr> right = parseEquality();
        //binaryOpExpr = std::make_shared<AST::AstBinaryOpExpr>(binaryOpExpr, right, tok);
        binaryOpExpr = AST::AstBinaryOpExpr::makeBinaryOpExpr(binaryOpExpr, right, tok);
        tok = advanceToken();
    }
    return returnExpr(binaryOpExpr);
}

std::shared_ptr<AST::AstExpr>                FunctionParser::parseEquality() {
    std::shared_ptr<AST::AstExpr>  binaryOpExpr = parseRel();
    Token tok = advanceToken();
    if (tok.match(TokenId::kw_equalequal) || tok.match(TokenId::kw_exclaimequal) ) {
        tok = readToken( );
        std::shared_ptr<AST::AstExpr> right = parseRel();
        //binaryOpExpr = std::make_shared<AST::AstBinaryOpExpr>(binaryOpExpr, right, tok);
        binaryOpExpr = AST::AstBinaryOpExpr::makeBinaryOpExpr(binaryOpExpr, right, tok);
    }
    return returnExpr(binaryOpExpr);
}

std::shared_ptr<AST::AstExpr>                FunctionParser::parseRel() {
    std::shared_ptr<AST::AstExpr>  binaryOpExpr = parseExpr();
    Token tok = readToken();
    if (tok.match(TokenId::kw_less) || tok.match(TokenId::kw_lessequal) || tok.match(TokenId::kw_greater) || tok.match(TokenId::kw_greaterequal)) {
        std::shared_ptr<AST::AstExpr> right = parseExpr();
        //auto type = binaryOpExpr->getTypeId( );
        //binaryOpExpr = std::make_shared<AST::AstBinaryOpExpr>(binaryOpExpr, right, tok);
        binaryOpExpr = AST::AstBinaryOpExpr::makeBinaryOpExpr(binaryOpExpr, right, tok);
    }
    return returnExpr(binaryOpExpr);
}

std::shared_ptr<AST::AstExpr>                FunctionParser::parseExpr() {
    std::shared_ptr<AST::AstExpr>  binaryOpExpr = parseTerm();
    Token tok = advanceToken();
    while (tok.match(TokenId::kw_plus) || tok.match(TokenId::kw_minus)) {
        tok = readToken();
        std::shared_ptr<AST::AstExpr> right = parseTerm();
        //binaryOpExpr = std::make_shared<AST::AstBinaryOpExpr>(binaryOpExpr, right, tok);
        binaryOpExpr = AST::AstBinaryOpExpr::makeBinaryOpExpr(binaryOpExpr, right, tok);
        tok = advanceToken();
    }
    return returnExpr(binaryOpExpr);

}

std::shared_ptr<AST::AstExpr>                FunctionParser::parseTerm() {
    std::shared_ptr<AST::AstExpr>  binaryOpExpr = parseUnary( );
    Token tok = advanceToken( ); 
    while (tok.match(TokenId::kw_star) || tok.match(TokenId::kw_slash)) {
        tok = readToken();
        std::shared_ptr<AST::AstExpr> right = parseUnary();
        //binaryOpExpr = std::make_shared<AST::AstBinaryOpExpr>(binaryOpExpr, right, tok);
        binaryOpExpr = AST::AstBinaryOpExpr::makeBinaryOpExpr(binaryOpExpr, right, tok);
        tok = advanceToken( );
    }
    return returnExpr(binaryOpExpr);
}

std::shared_ptr<AST::AstExpr>                FunctionParser::parseUnary() {
    Token tok = advanceToken();
    if (tok.getTokenId() == TokenId::kw_not || tok.getTokenId() == TokenId::kw_minus) {
        tok = readToken();
        std::shared_ptr<AST::AstExpr> factor = parseFactor();
        std::shared_ptr<AST::AstUnaryOpExpr> expr = AST::AstUnaryOpExpr::makeUnaryOpExpr( factor, tok);
        return returnExpr(expr);
    }
    else {
        auto expr = parseFactor();
        return expr;
    }
}

std::shared_ptr<AST::AstExpr>                FunctionParser::parseFactor() {
    Token tok = readToken();
    switch (tok.getTokenId()) {
    case TokenId::kw_l_paren: {
        std::shared_ptr<AST::AstExpr> expr = parseCommaExpr();
        tok = readToken();
        tok.match( TokenId::kw_r_paren);
        return expr;
    }break;
    case TokenId::kw_id: {
        //std::shared_ptr<ENV::ObjectId> id= getEnv()->getObjectId(tok.toString());
        //if (nullptr == id) {
        //    std::string errMsg = "the id " + tok.toString() + " not found";
        //    //error(errMsg.c_str());
        //}
        //std::shared_ptr<ENV::TypeId> type = id->getObjType();
        std::shared_ptr<AST::AstVariableObjExpr> objExpr = std::make_shared<AST::AstVariableObjExpr>(tok );
        
        return objExpr;
    }break;
    case TokenId::kw_true: {
        //std::shared_ptr<ENV::TypeId> type = ENV::TopEnv::getBasicType(ENV::BasicType::kBool);
        //std::shared_ptr<ENV::ObjectId> id = getEnv()->getObjectId("true");
        //std::shared_ptr<ENV::TypeId>   type = id->getObjType();
        std::shared_ptr<AST::AstConstantExpr<bool>> objExpr = std::make_shared<AST::AstConstantExpr<bool>>( tok,true);
        return objExpr;
    }break;
    case TokenId::kw_false: {
        //std::shared_ptr<ENV::ObjectId> id = getEnv()->getObjectId("false");
        //std::shared_ptr<ENV::TypeId> type = id->getObjType();
        //std::shared_ptr<ENV::TypeId> type = ENV::TopEnv::getBasicType(ENV::BasicType::kBool);
        std::shared_ptr<AST::AstConstantExpr<bool>> objExpr = std::make_shared<AST::AstConstantExpr<bool>>(tok,false);
        return objExpr;
    }break;
    case TokenId::kw_integer: {
        //std::shared_ptr<ENV::TypeId> type = ENV::TopEnv::getBasicType(ENV::BasicType::kI32);
        std::shared_ptr<AST::AstConstantExpr<int8_t>> constId = std::make_shared<AST::AstConstantExpr<int8_t>>( tok,1 );
        return constId;
    }break;
    case TokenId::kw_real: {
        //std::shared_ptr<ENV::TypeId> type = ENV::TopEnv::getBasicType(ENV::BasicType::kF32);
        std::shared_ptr<AST::AstConstantExpr<float>> constId = std::make_shared<AST::AstConstantExpr<float>>( tok, 1.0f);
        return constId;
    }break;
    default: {
        //std::shared_ptr<ENV::TypeId> type = ENV::TopEnv::getBasicType(ENV::BasicType::kVoid);
        std::shared_ptr<AST::AstVoidExpr> voidExpr = std::make_shared<AST::AstVoidExpr>();
        return voidExpr;
        break;
    }
    }
}


std::shared_ptr<AST::AstExpr>            FunctionParser::returnExpr(std::shared_ptr<AST::AstExpr> expr) {
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

