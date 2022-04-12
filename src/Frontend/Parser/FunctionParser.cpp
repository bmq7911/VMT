#pragma once
#include "Frontend/Parser/FunctionParser.h"
#include "SymbolTable/FunctionId.h"
#include "SymbolTable/ObjectId.h"
#include "SymbolTable/TopEnv.h"


FunctionParser::FunctionParser(std::shared_ptr<TokenReader> reader)
    : ParserProxy(reader)
{}

// 符号表该记录什么,怎么记录都是值得考虑的问题
// 同样的,我们面临着回退的问题
std::shared_ptr<AST::Function> FunctionParser::begin( ) {

    std::shared_ptr<ENV::Env> savedEnv = getEnv();
    /// 这个目标是为了更好查询使用
    std::shared_ptr<ENV::Env> f_env = std::make_shared<ENV::Env>(savedEnv);
    bool isConst = false;

    Token tok = readToken( );
    if (match(tok, TokenId::kw_const)) {
        // 处理函数
        isConst = true;
        tok = readToken();
    }
    if (match(tok, TokenId::kw_id)) {
        std::string tokname = tok.toString();
        std::shared_ptr<ENV::TypeId> returnType = getEnv()->getTypeId( tokname );
        if (!returnType) {
            return nullptr;
        }
    }
    tok = readToken( );
    if (!match(tok, TokenId::kw_equal)) {
       
    }




    setEnv(f_env);
    Token tok = readToken();
    match(tok, TokenId::kw_id);
    Token funcname = tok;

    tok = readToken();
    match(tok, TokenId::kw_l_paren);
    std::shared_ptr<AST::ParamList> paramlist = paramList();
    tok = readToken();
    match(tok, TokenId::kw_arrow);
    tok = readToken();
    std::shared_ptr<ENV::TypeId> returnType = getEnv()->getTypeId(tok.toString());
    
    if (tok.match(TokenId::kw_id)) { /// 类型名
        /// 检查时否是已知类型
    }
    //else if(tok.match(TokenId::kw_basic_type) ){ /// 基础数据类新型
    //    
    //}
    tok = readToken();
    std::shared_ptr<AST::Stmt> stmts;
    if (tok.match(TokenId::kw_l_brace)) {
        stmts = parseFunctionBlock();
    }
    else if (tok.match(TokenId::kw_equal)) {
        //

    }

    setEnv(savedEnv);

    std::shared_ptr<AST::Function> function = std::make_shared<AST::Function>();
    function->init( returnType, funcname, stmts, paramlist,f_env);
    /// 函数在符号表之中的信息
    std::shared_ptr<ENV::FunctionId> functionEnv= std::make_shared<ENV::FunctionId>(funcname.toString().c_str());
    functionEnv->setEnv(f_env);


    savedEnv->put(funcname.toString(), functionEnv);

    return function;
}
/// 
std::shared_ptr<AST::Param> FunctionParser::param() {
    std::shared_ptr<AST::Param> param = std::make_shared<AST::Param>( );
    Token token = getTokenReader()->getToken();
    std::shared_ptr<ENV::TypeId> type = getEnv()->getTypeId( token.toString());
    if (type ) { /// 获取数据类型
        
    }
    else {
        
    }
    
    token = readToken();
    std::shared_ptr<ENV::ObjectId>        objectId = std::make_shared<ENV::ObjectId>(token.toString().c_str(), type );
    std::shared_ptr<AST::VariableObjExpr> idExpr   = std::make_shared<AST::VariableObjExpr>(token, type, objectId );
    param->addId(idExpr);
    /// 符号表就没记录相关其他属性
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
        /// 这个是AST上的信息,AST上的Object需要知道自己在符号表之中吗??需要知道符号表这个东西嘛???
        std::shared_ptr<ENV::ObjectId> objectId = std::make_shared<ENV::ObjectId>(token.toString().c_str(),type);
        std::shared_ptr<AST::VariableObjExpr> idExpr = std::make_shared<AST::VariableObjExpr>(token, type, objectId );
        param->addId(idExpr);
        /// 符号表就没记录相关其他属性
        getEnv()->put(token.toString(), objectId);
        token = readToken();
    }
    return param;
}

std::shared_ptr<AST::ParamList>  FunctionParser::paramList() { /// 这里可能为空,这里是没讨论的
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
///  这里的写法是递归下降分析,通过递归下降分析,分析出产生式,通过产生式和语义规则进行语法制导翻译,这里的语法制导翻译是指导生成抽象语法树
///  在后面的由抽象语法树到三地址格式使用的语法制导翻译是 通过产生式和语义规则,将抽象语法树转化为三地址码
/// </summary>
/// <returns></returns>
std::shared_ptr<AST::Stmt>     FunctionParser::parseFunctionBlock() {
    Token tok = getToken();
    if (match(tok, TokenId::kw_l_brace)) {
        return parseBlock();
    }
    return nullptr;
}

//// 这里就是处理各种表达是的逻辑
//// 这个解析逻辑有问题
std::shared_ptr<AST::Stmt> FunctionParser::parseStmt() {
    Token tok = readToken();
    std::shared_ptr<AST::Stmt> stmt;
    switch (tok.getTokenId()) {
    case TokenId::kw_l_brace: {
        stmt = parseBlock();
    }break;
    case TokenId::kw_if: {
        stmt = parseIf();
    }break;
    case TokenId::kw_for: {
        stmt = parseFor();
    }break;
    case TokenId::kw_while: {
        stmt = parseWhile();
    }break;
    case TokenId::kw_do: {
        stmt = parseDoWhile();
    }break;
    case TokenId::kw_continue: {
        if (false == _IsInLoop()) {
            error("continue must in loop stmts");
        }
        tok = readToken();
        match(tok, TokenId::kw_semi);
        return std::make_shared<AST::ContinueStmt>();
    }break;
    case TokenId::kw_break: {
        if (false == _IsInLoop()) {
            error("break must in loop stmts else switch stmts");
        }
        tok = readToken();
        match(tok, TokenId::kw_semi);
        return std::make_shared<AST::BreakStmt>();
    }break;
    case TokenId::kw_semi: { /// semikolon
        tok = readToken();
        return nullptr;
    }break;
    case TokenId::kw_return: {
        stmt = parseReturn();
        tok = readToken();
        match(tok, TokenId::kw_semi);
    }break;
    default: { /// 考虑表达式
        std::shared_ptr<AST::Expr> expr = parseDeclOrExpr();
        if (expr) {
            stmt = std::make_shared<AST::ExprStmt>(expr);
            tok = readToken();
            match(tok, TokenId::kw_semi);
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
    match(tok, TokenId::kw_l_brace);
    std::shared_ptr<AST::Stmts> stmts = std::make_shared<AST::Stmts>();
    do {
        std::shared_ptr<AST::Stmt> stmt = parseStmt();
        stmts->add(stmt);
        tok = readToken();
        if (tok.match(TokenId::kw_r_brace)) {
            break;
        }
        else {
            fallbackToken();
        }
    } while (true);
    match(tok, TokenId::kw_r_brace);
    setEnv(savedEnv);
    return stmts;
}

std::shared_ptr<AST::IfStmt>                  FunctionParser::parseIf( ) {
    Token tok = getToken();
    match(tok.getTokenId(), TokenId::kw_if);
    tok = readToken();
    match(tok.getTokenId(), TokenId::kw_l_paren);
    std::shared_ptr<AST::Expr> boolexpr = parseCommaExpr();
    tok = readToken();
    match(tok.getTokenId(),TokenId::kw_r_paren);
    std::shared_ptr<AST::Stmt> stmt = parseStmt();
    tok = readToken();
    std::shared_ptr<AST::ElseStmt>  elseStmt;
    if (match(tok, TokenId::kw_else)) {
        elseStmt = parseElse();
    }
    std::shared_ptr< AST::IfStmt> ifStmt = std::make_shared<AST::IfStmt>(boolexpr, stmt, elseStmt);
    return ifStmt;
}

std::shared_ptr<AST::ElseStmt>                FunctionParser::parseElse() {
    Token tok = getToken();
    match(tok, TokenId::kw_else);
    std::shared_ptr<AST::Stmt> stmt = parseStmt();
    
    std::shared_ptr<AST::ElseStmt> elsestmt = std::make_shared<AST::ElseStmt>(stmt);
    return elsestmt;
}
std::shared_ptr<AST::ForStmt>             FunctionParser::parseFor(){
    _EntryLoop();
    Token tok = readToken();
    match(tok.getTokenId(), TokenId::kw_l_paren );
    readToken();
    std::shared_ptr< AST::Expr> initExpr = parseDeclOrExpr();
    tok = readToken();
    match(tok, TokenId::kw_semi);
    readToken();
    std::shared_ptr<AST::Expr> boolExpr = parseDeclOrExpr();
    std::shared_ptr<ENV::TypeId> boolType = boolExpr->getTypeId();
    if (boolType != ENV::getTopEnv()->getBasicType(ENV::BasicType::kBool)) {
        /// 这里是一个错误,怎么提示这个错误
        /// 如何进行错误处理
        std::cout <<"the bool expr must bool type in for loop stmt" <<std::endl;
    }
    tok = readToken();
    match(tok, TokenId::kw_semi);
    readToken();
    std::shared_ptr<AST::Expr> tailExpr = parseDeclOrExpr();
    tok = readToken();
    match(tok, TokenId::kw_r_paren);

    std::shared_ptr<AST::Stmt> stmt = parseStmt();

    std::shared_ptr<AST::ForStmt> forLoop = std::make_shared<AST::ForStmt>(initExpr, boolExpr, tailExpr, stmt);
    _LeaveLoop();
    return forLoop;
}
/// break 和 continue not support right now
std::shared_ptr<AST::WhileStmt>           FunctionParser::parseWhile() {
    _EntryLoop();
    Token tok = readToken();
    match(tok.getTokenId(), TokenId::kw_l_paren);
    std::shared_ptr<AST::Expr> boolexpr = parseCommaExpr();
    auto type = boolexpr->getTypeId();
    //if (type != ENV::getTopEnv()->getBasicType(ENV::BasicType::kBool)) {
    //    
    //    std::cout << "&&&&&&&&&&&&&&\nnot bool Expr\n&&&&&&&&&&&&" <<std::endl;
    //}
    tok = getToken();
    match(tok, TokenId::kw_r_paren);
    readToken();
    std::shared_ptr<AST::Stmt> stmt = parseStmt();
    _LeaveLoop();
    return std::make_shared<AST::WhileStmt>( boolexpr, stmt);
}


std::shared_ptr<AST::DoWhileStmt>              FunctionParser::parseDoWhile() {
    _EntryLoop();
    std::shared_ptr<AST::Stmt> stmt = parseStmt();
    Token tok = readToken();
    match(tok, TokenId::kw_while);
    tok = readToken();
    match(tok, TokenId::kw_l_paren);
    std::shared_ptr<AST::Expr> whileExpr = parseCommaExpr();
    tok = readToken();
    match(tok, TokenId::kw_r_paren);
    tok = readToken();
    match(tok, TokenId::kw_semi);
    _LeaveLoop();
    return std::make_shared<AST::DoWhileStmt>( whileExpr, stmt);

}

std::shared_ptr<AST::Stmt>                FunctionParser::parseReturn() {
    std::shared_ptr<AST::Expr> expr = parseCommaExpr();
    Token tok = getToken();
    match(tok, TokenId::kw_semi);
    std::shared_ptr<AST::ExprStmt> exprStmt = std::make_shared<AST::ExprStmt>( expr);
    std::shared_ptr<AST::ReturnStmt> returnStmt = std::make_shared<AST::ReturnStmt>( exprStmt);
    return returnStmt;
}

std::shared_ptr<AST::Expr>                FunctionParser::parseDeclOrExpr() {
    Token tok = getToken();
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
    case TokenId::kw_bool: { /// 这里是声明
        std::shared_ptr<ENV::TypeId> type = getEnv()->getTypeId(tok.toString());
        expr = parseDecl(type);
    }break;
    case TokenId::kw_id: {
        std::shared_ptr<ENV::TypeId> type = getEnv()->getTypeId( tok.toString() );
        if (type) { /// 声明
            expr = parseDecl(type);
        }
        else { ///
            fallbackToken(); /// 由Expr的解析逻辑自己处理解析操作
            expr= parseCommaExpr();
        }
    }break;
    case TokenId::kw_void: 
    default: {/// 这里应该报错
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
        match(id, TokenId::kw_id);
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
            std::shared_ptr<AST::Expr> right = parseAssignExpr(); /// 这是一种递归的形式
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
    /// 条件表达式
    if (tok.match(TokenId::kw_question)) {
        std::shared_ptr<AST::Expr> True = parseBool();
        Token tok = readToken();
        match(tok, TokenId::kw_colon);
        std::shared_ptr<AST::Expr> False = parseBool();
        return returnExpr( std::make_shared<AST::ConditionExpr>(condition, True, False));
    }
    else {
        return returnExpr(condition);
    }



}
/// 这里实际是最低优先级
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
    /// 1.通过递归实现 
    /// 2.通过循环实现 这就说明某种形式的递归可以转换为循环,尾递归是可以的
    /// term -> term * factor | term / factor | factor 按道理这个是非尾递归,是会陷入无限循环的,但是我们可以手动
    /// 终止递归
    /// 3.我的LeftPair设计的结构是为串行非相关结构设计的 像 a * b * c * d;这种结构是串行相关的
    /// 4.像 stmts -> stmts stmt 就是串行不相关结构,这个时候我们可用 leftPair ,而不用实现 Stmts这个AST
    std::shared_ptr<AST::Expr>  binaryOpExpr = parseUnary();
    Token tok = readToken( ); ///难点是什么时候该read,什么时候该get
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

/// 这里实际是最高优先级
std::shared_ptr<AST::Expr>                FunctionParser::parseFactor() {
    Token tok = getToken();
    switch (tok.getTokenId()) {
    case TokenId::kw_l_paren: {
        std::shared_ptr<AST::Expr> expr = parseCommaExpr();
        tok = readToken();
        match(tok, TokenId::kw_r_paren);
        return expr;
    }break;
    case TokenId::kw_id: {
        std::shared_ptr<ENV::ObjectId> id= getEnv()->getObjectId(tok.toString());
        if (nullptr == id) {
            std::string errMsg = "the id " + tok.toString() + " not found";
            error(errMsg.c_str());
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
    fallbackToken();
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

