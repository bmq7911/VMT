#pragma once
#include <iostream>
#include "Frontend/Lexer/Lexer.h"

namespace AST {
    class  Node {
    protected:
        int lexline = 0;
    public:
        Node() {

        }
        void error(std::string const & s) {
            std::cout << "near line " << lexline << ": " << s << std::endl;
            std::abort();
        }
    };

}
