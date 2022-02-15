#include "Frontend/Parser/ProgramParser.h"

ProgramParser::ProgramParser(std::shared_ptr<TokenReader> parserCore)
    :ParserProxy( parserCore)
{
    /// ÿ�������и�env
    m_program = std::make_shared<AST::Program>();
}

void ProgramParser::startParser() {
    program();
}

/// ע�Ϳ����ڴʷ������׶θ��޳���
void ProgramParser::program() {
    Token tok = readToken();
    
    while (!tok.match(Tag::eof )) {
        if (tok.match(Tag::kw_func)) {
             std::shared_ptr<AST::TopElement> top = ParseFunction();
             m_program->addTopElement( top );
        }
        else if (tok.match(Tag::kw_template)) {
        
        }
        else if (tok.match(Tag::kw_struct)) {
            
        }
        tok = readToken();
    }
}

std::shared_ptr<AST::Function> ProgramParser::ParseFunction( ) {
    Token tok = getToken( );
    if (tok.match(Tag::kw_func)) {
        std::shared_ptr<FunctionParser> funcParser = std::make_shared<FunctionParser>( get());
        return funcParser->begin();
    }
    else {
        /// ������,���һ������ûָ�����
    }
    return nullptr;
}

std::shared_ptr<AST::Program>  ProgramParser::getProgram() {
    return m_program;
}

