#pragma once
#include "Frontend/AST/AST.h"
#include "Frontend/Parser/ParserProxy.h"

class FunctionParser : public ParserProxy {
public:
    FunctionParser(std::shared_ptr<TokenReader>);

    std::shared_ptr<AST::AstFunction>        begin ( );
    std::shared_ptr<AST::AstType>            parseType();
    std::shared_ptr<AST::AstAttribute>       parseAttribute();
    std::shared_ptr<AST::AstFunctionBody>    parseFunctionBody();
    std::shared_ptr<AST::AstStmt>            parseFunctionStmt();
    std::shared_ptr<AST::AstParam>           param( );
    std::shared_ptr<AST::AstParamList>       paramList( );
    std::shared_ptr<AST::AstStmt>            parseFunctionBlock();
    std::shared_ptr<AST::AstStmt>            parseFunctionExpr();
    std::shared_ptr<AST::AstStmt>            parseStmt();
    std::shared_ptr<AST::AstStmt>            parseBlock();
    std::shared_ptr<AST::AstIfStmt>          parseIf();
    std::shared_ptr<AST::AstElseStmt>        parseElse();
    std::shared_ptr<AST::AstForStmt>         parseFor();
    std::shared_ptr<AST::AstWhileStmt>       parseWhile();
    std::shared_ptr<AST::AstDoWhileStmt>     parseDoWhile();
    std::shared_ptr<AST::AstStmt>            parseReturn();

    std::shared_ptr<AST::AstExpr>            parseDeclOrExpr();
    std::shared_ptr<AST::AstExpr>            parseDecl( std::shared_ptr<ENV::TypeId> type);
    
    std::shared_ptr<AST::AstExpr>            parseCommaExpr();
    std::shared_ptr<AST::AstExpr>            parseAssignExpr();
    std::shared_ptr<AST::AstExpr>            parseConditionExpr();

    std::shared_ptr<AST::AstExpr>            parseBool();
    std::shared_ptr<AST::AstExpr>            parseJoin();
    std::shared_ptr<AST::AstExpr>            parseEquality();
    std::shared_ptr<AST::AstExpr>            parseRel();
    std::shared_ptr<AST::AstExpr>            parseExpr();
    std::shared_ptr<AST::AstExpr>            parseTerm();
    std::shared_ptr<AST::AstExpr>            parseUnary();
    std::shared_ptr<AST::AstExpr>            parseFactor();
    std::shared_ptr<AST::AstExpr>            returnExpr(std::shared_ptr<AST::AstExpr> expr);

private:
    void _EntryLoop();
    void _LeaveLoop();
    bool _IsInLoop();
private:
    uint32_t m_entryLoop{0};

};