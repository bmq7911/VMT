#pragma once
#include "Frontend/AST/AstStmt.h"
#include "Frontend/AST/AstExpr.h"

namespace AST {
    class AstLoopStmt : public AstStmt {
    public:
        AstLoopStmt(std::shared_ptr<AST::AstExpr> expr) 
            : m_loopExpr(expr)
        {}
        std::shared_ptr<AST::AstExpr>& getLoopExpr() {
            return m_loopExpr;
        }
    private:
        std::shared_ptr<AST::AstExpr> m_loopExpr;
    };



}