#pragma once
#include "Frontend/Parser/ParserProxy.h"
class ModuleParser  : public ParserProxy{
public:
	ModuleParser(std::shared_ptr<TokenReader>);
private:
	
};