#include "Frontend/Parser/ProgramParser.h"

ProgramParser::ProgramParser(std::shared_ptr<TokenReader> parserCore)
    :ParserProxy( parserCore)
{
    /// 每个程序都有个env
    m_program = std::make_shared<AST::AstProgram>();
}

void ProgramParser::startParser() {
    program();
}

/// 注释可以在词法分析阶段给剔除掉
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
        /// 错误处理,并且还的做好恢复功能
    }
    return nullptr;
}

std::shared_ptr<AST::AstProgram>  ProgramParser::getProgram() {
    return m_program;
}

