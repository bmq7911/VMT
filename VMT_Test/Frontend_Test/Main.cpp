#include <stdio.h>
#include <iostream>
#include "Frontend/Lexer/Lexer.h"
#include "Frontend/Parser/ParserCore.h"
#include "Frontend/Parser/ProgramsParser.h"


int main( int argc, char * argv[]) {
    if (argc != 2) {
		return 0;
	}
    std::shared_ptr<Lexer> lex = std::make_shared<Lexer>( argv[1]);// Lexer(argv[1]);
    std::shared_ptr<ParserCore> parserCore = std::make_shared<ParserCore>(lex);
    std::shared_ptr<ProgramsParser> parser = std::make_shared<ProgramsParser>();
    parser->set(parserCore);
    parser->startParser( );
	printf("\n");
}
