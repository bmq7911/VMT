#pragma once
#include "Frontend/AST/Node.h"
/// 这个应该是语法树Node
namespace AST {
    class IASTVisitor;
    class Stmt :  public Node {
    public:
        Stmt() { }
        static Stmt * Null;
        virtual void gen(std::shared_ptr<AST::IASTVisitor> visitor) = 0;
        int m_after = 0;                   // saves label after
        static Stmt* Enclosing;// = Stmt::Null;  // used for break stmts

    };
}
