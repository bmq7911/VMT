#pragma once
#include "Frontend/Parser/ParserProxy.h"
#include "Frontend/Parser/FunctionParser.h"

class ProgramParser : public ParserProxy {
public:
    /// LL(1) �ĵݹ��½������㷨
    ProgramParser(std::shared_ptr<TokenReader> reader );
    void startParser();
    /// ע�Ϳ����ڴʷ������׶θ��޳���
    void program();
    std::shared_ptr<AST::AstFunction> ParseFunction( );
	
private:
    using ParserProxy::ParserProxy;
};