#include <stdio.h>
#include <iostream>
#include "Frontend/Lexer/Lexer.h"
#include "Frontend/Lexer/FileLexer.h"
#include "Frontend/Parser/ProgramParser.h"
#include "Frontend/Parser/FunctionParser.h"
#include "IRAstVisitor.h"

int main( int argc, char * argv[]) {
    if (argc != 2) {
		return 0;
	}

    std::shared_ptr<FileLexer> lex = std::make_shared<FileLexer>( argv[1]);
    uint32_t lastLine = 0;

    std::shared_ptr<TokenReader>        reader     = std::make_shared<TokenReader>(lex);
    std::shared_ptr<FunctionParser>     parser     = std::make_shared<FunctionParser>(reader);
    std::shared_ptr<AST::AstFunction>   funtion    = parser->begin();
    std::shared_ptr<TS::AST_IR_Codegen> ir_visitor = std::make_shared<TS::AST_IR_Codegen>();
    funtion->gen(ir_visitor, nullptr);
	printf("\n");
}
