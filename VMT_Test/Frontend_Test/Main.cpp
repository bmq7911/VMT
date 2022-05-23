#include <stdio.h>
#include <iostream>
#include "Frontend/Lexer/Lexer.h"
#include "Frontend/Lexer/FileLexer.h"
#include "Frontend/Parser/ProgramParser.h"
#include "Frontend/Parser/FunctionParser.h"
#include "TestAstVisitor.h"
#include "IRAstVisitor.h"

int main( int argc, char * argv[]) {
    if (argc != 2) {
		return 0;
	}

    std::shared_ptr<FileLexer> lex = std::make_shared<FileLexer>( argv[1]);
    uint32_t lastLine = 0;
    /*
    do {
        auto tok = lex->scan();
        
        if (tok.getTokenId() != TokenId::kw_eof) {
            if (tok.getLocation().row() != lastLine) {
                lastLine = tok.getLocation().row();
                std::cout << std::endl;
            }
            std::cout << tok.toStringRef() << " ";
        }
        else {
            break;
        }
    } while ( true );
    */
    //std::shared_ptr<ProgramParser> parser = std::make_shared<ProgramParser>( lex );
    //parser->startParser( );
    std::shared_ptr<TokenReader> reader       = std::make_shared<TokenReader>(lex);
    std::shared_ptr<FunctionParser> parser    = std::make_shared<FunctionParser>(reader);
    std::shared_ptr<AST::AstFunction> funtion = parser->begin();
    std::shared_ptr<TestAstVisitor > visitor  = std::make_shared<TestAstVisitor>( );
    std::shared_ptr<TS::AST_IR_Codegen> ir_visitor = std::make_shared<TS::AST_IR_Codegen>();
    funtion->gen(visitor, nullptr );
    funtion->gen(ir_visitor, nullptr);
	printf("\n");
}
