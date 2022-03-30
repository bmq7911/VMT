#include "Frontend/Lexer/TokenId.h"

std::string_view toTokenIdString(TokenId tokid) {
    switch (tokid) {
#define DECL_KEY_WORD(x,y,...) case TokenId::kw_##x:return std::string_view(#y,sizeof(#y));
#include "Frontend/Lexer/KeyWord.def"
#undef DECL_KEY_WORD
    case kw_Unknown:
    default: {
        return std::string_view("kw_Unknown", sizeof("kw_Unknown"));
    }break;
    }
}

bool             isKeyWord(TokenId tok) {
    switch (tok) {
#define DECL_KEY_WORD(x,y,__is_keyword,...) return __is_keyword;
#include "Frontend/Lexer/KeyWord.def"
#undef DECL_KEY_WORD
    case kw_Unknown:
    default: {
        return false;
    }break;
    
    }
    return true;
}

bool isPunctuator(TokenId tok) {
    switch (tok) {
#define DECL_KEY_WORD(x,y,__is_keyword,__is_punctuatir,...) return __is_punctuatir;
#include "Frontend/Lexer/KeyWord.def"
#undef DECL_KEY_WORD
    case kw_Unknown:
    default: {
        return false;
    }break;

    }
    return true;
}
