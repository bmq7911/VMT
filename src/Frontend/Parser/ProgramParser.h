#pragma once
#include "Frontend/Parser/ParserProxy.h"
#include "Frontend/Parser/FunctionParser.h"
#include "Frontend/AST/AstProgram.h"

class ProgramParser : public ParserProxy {
public:
    /// LL(1) 的递归下降分析算法
    ProgramParser(std::shared_ptr<TokenReader> reader );
    void startParser();
    /// 注释可以在词法分析阶段给剔除掉
    void program();
    std::shared_ptr<AST::AstFunction> ParseFunction( );
    std::shared_ptr<AST::AstProgram>  getProgram();
	
private:
    std::shared_ptr<AST::AstProgram> m_program;
    std::shared_ptr<ENV::Env> m_env;
    using ParserProxy::ParserProxy;
};