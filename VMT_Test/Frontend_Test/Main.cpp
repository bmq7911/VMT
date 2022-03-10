#include <stdio.h>
#include <iostream>
#include "Frontend/Lexer/Lexer.h"
#include "Frontend/Parser/ProgramParser.h"


int main( int argc, char * argv[]) {
    if (argc != 2) {
		return 0;
	}
    std::shared_ptr<Lexer> lex = std::make_shared<Lexer>( argv[1]);// Lexer(argv[1]);
    std::shared_ptr<ProgramParser> parser = std::make_shared<ProgramParser>( lex );
    parser->startParser( );
	printf("\n");
}
