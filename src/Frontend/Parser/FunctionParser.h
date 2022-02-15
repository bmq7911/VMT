#pragma once
#include "Frontend/Parser/ParserProxy.h"

class FunctionParser : public ParserProxy {
public:
    FunctionParser(std::shared_ptr<TokenReader>);
    std::shared_ptr<AST::Function>  begin ( );
    std::shared_ptr<AST::Param>     param( );
    std::shared_ptr<AST::ParamList> paramList( );
    std::shared_ptr<AST::Stmt>      parseFunctionBlock();
    std::shared_ptr<AST::Stmt>      parseStmt();
    std::shared_ptr<AST::Stmt>            parseBlock();
    std::shared_ptr<AST::IfStmt>          parseIf();
    std::shared_ptr<AST::ElseStmt>        parseElse();
    std::shared_ptr<AST::ForStmt>         parseFor();
    std::shared_ptr<AST::WhileStmt>       parseWhile();
    std::shared_ptr<AST::DoWhileStmt>     parseDoWhile();
    std::shared_ptr<AST::Stmt>            parseReturn();

    std::shared_ptr<AST::Expr>            parseDeclOrExpr();
    std::shared_ptr<AST::Expr>            parseDecl( std::shared_ptr<ENV::TypeId> type);
    
    std::shared_ptr<AST::Expr>            parseCommaExpr();
    std::shared_ptr<AST::Expr>            parseAssignExpr();
    std::shared_ptr<AST::Expr>            parseConditionExpr();

    std::shared_ptr<AST::Expr>            parseBool();
    std::shared_ptr<AST::Expr>            parseJoin();
    std::shared_ptr<AST::Expr>            parseEquality();
    std::shared_ptr<AST::Expr>            parseRel();
    std::shared_ptr<AST::Expr>            parseExpr();
    std::shared_ptr<AST::Expr>            parseTerm();
    std::shared_ptr<AST::Expr>            parseUnary();
    std::shared_ptr<AST::Expr>            parseFactor();
    std::shared_ptr<AST::Expr>            returnExpr(std::shared_ptr<AST::Expr> expr);
    //AST::Stmt* block();
    //void decls();
    //void id_type();
    //void id_list(Type* type);
    //Type* type();
    //Type* dims(Type* p);
    //AST::Stmt* stmts();
    //AST::ExprStmt* exprStmt();
    //AST::Stmt* stmt();
    //
    //AST::Stmt* assign();
    //AST::Expr* boolexpr();
    //AST::Expr* join();
    //AST::Expr* equality();
    //AST::Expr* rel();    

    //AST::Expr* expr();
    //AST::Expr* term();
    //AST::Expr* unary();
    //AST::Expr* factor();
    //AST::Access* offset(AST::Id* a);

private:
    void _EntryLoop();
    void _LeaveLoop();
    bool _IsInLoop();
private:
    uint32_t m_entryLoop{0};

};