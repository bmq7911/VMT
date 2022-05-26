#pragma once
#include "Frontend/AST/AstExpr/AstExpr.h"
#include <string>

namespace AST {
    class AstObjectExpr : public AstExpr { /// 这个和 Identifier 是不同的
    public:
        AstObjectExpr( Token tok ) 
            : AstExpr( )
            , m_tok( tok )
        {
        }
        Token getObject() const {
            return m_tok;
        }
        std::shared_ptr<AST::AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor, ICollectInfoBack* collect);
    private:
        Token m_tok;
    };
}

