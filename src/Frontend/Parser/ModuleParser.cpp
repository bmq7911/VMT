#include "Frontend/Parser/ModuleParser.h"


ModuleParser::ModuleParser(std::shared_ptr<TokenReader> reader)
	: ParserProxy( reader )
{
}
