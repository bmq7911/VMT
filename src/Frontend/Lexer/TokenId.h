#pragma once 
#include <limits>
#include <string>
#include <string_view>
enum TokenId : uint32_t {
#define DECL_KEY_WORD(x,y,...) kw_##x,
#include "Frontend/Lexer/KeyWord.def"
#undef DECL_KEY_WORD
    kw_Unknown = std::numeric_limits<uint32_t>::max(),
};

std::string_view toTokenIdString(TokenId tag);
bool             isKeyWord(TokenId tag);
