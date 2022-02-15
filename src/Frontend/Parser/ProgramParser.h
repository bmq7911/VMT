#pragma once
#include "Frontend/Parser/ParserProxy.h"
#include "Frontend/Parser/FunctionParser.h"
#include "Frontend/AST/Program.h"

class ProgramParser : public ParserProxy {
public:
    /// LL(1) �ĵݹ��½������㷨
    ProgramParser(std::shared_ptr<TokenReader> reader );
    void startParser();
    /// ע�Ϳ����ڴʷ������׶θ��޳���
    void program();
    std::shared_ptr<AST::Function> ParseFunction( );
    std::shared_ptr<AST::Program>  getProgram();
	
private:
    std::shared_ptr<AST::Program> m_program;
    std::shared_ptr<ENV::Env> m_env;
    using ParserProxy::ParserProxy;
};