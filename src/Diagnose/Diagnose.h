#pragma once
#include <string_view>
#include "Frontend/Lexer/Token.h"


class Diagnose {
public:
	static void expectBut( TokenId expect, Token but);
	static void expectBut( TokenId expect, TokenId but);
	static void errorMsg(const char*);
	static void errorMsg(const char* msg, const char* expect);
	static void errorMsg(const char* msg, std::string_view const& expect);
private:

};

