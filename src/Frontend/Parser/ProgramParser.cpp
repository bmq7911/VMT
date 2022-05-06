#include "Frontend/Parser/ProgramParser.h"

ProgramParser::ProgramParser(std::shared_ptr<TokenReader> parserCore)
    :ParserProxy( parserCore)
{
    /// ÿ�������и�env
    m_program = std::make_shared<AST::AstProgram>();
}

void ProgramParser::startParser() {
    program();
}

/// ע�Ϳ����ڴʷ������׶θ��޳���
void ProgramParser::program() {
    Token tok = readToken();
    
    while (!tok.match(TokenId::kw_eof )) {
        if (tok.match(TokenId::kw_func)) {
             std::shared_ptr<AST::AstTree> top = ParseFunction();
        }
        else if (tok.match(TokenId::kw_template)) {
        
        }
        else if (tok.match(TokenId::kw_struct)) {
            
        }
        tok = readToken();
    }
}

std::shared_ptr<AST::AstFunction> ProgramParser::ParseFunction( ) {
    Token tok = getToken( );
    if (tok.match(TokenId::kw_func)) {
        std::shared_ptr<FunctionParser> funcParser = std::make_shared<FunctionParser>( get());
        return funcParser->begin();
    }
    else {
        /// ������,���һ������ûָ�����
    }
    return nullptr;
}

std::shared_ptr<AST::AstProgram>  ProgramParser::getProgram() {
    return m_program;
}

