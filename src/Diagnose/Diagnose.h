#pragma once
#include <string_view>
#include "Frontend/Lexer/Token.h"


class Diagnose {
public:
	static void expectBut( TokenId expect, Token but);
	static void expectBut( TokenId expect, TokenId but);
private:

};

