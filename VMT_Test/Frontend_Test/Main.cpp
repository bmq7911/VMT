#include <stdio.h>
#include <iostream>
#include "Frontend/Lexer/Lexer.h"
#include "Frontend/Lexer/FileLexer.h"
#include "Frontend/Parser/ProgramParser.h"


int main( int argc, char * argv[]) {
    if (argc != 2) {
		return 0;
	}

    std::shared_ptr<FileLexer> lex = std::make_shared<FileLexer>( argv[1]);
    uint32_t lastLine = 0;
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
    //std::shared_ptr<ProgramParser> parser = std::make_shared<ProgramParser>( lex );
    //parser->startParser( );
	printf("\n");
}
