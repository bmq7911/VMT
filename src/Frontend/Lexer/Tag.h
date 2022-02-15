
#pragma once 

enum Tag : uint32_t {
#define ENUM_KEYWORD
#include "Frontend/Lexer/KeyWord.def"
#undef ENUM_KEYWORD
};


static inline const char * toString(Tag tag) {
    switch (tag) {

#define TAG_TO_STRING
#include "Frontend/Lexer/KeyWord.def"
#undef TAG_TO_STRING
    
        default: {
            return nullptr;
        }break;
    }

}
