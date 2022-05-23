#pragma once
#include "Frontend/AST/AstExpr/AstExpr.h"
#include <string>
namespace ENV {
    class Env;
}

namespace AST {
    class AstObjectExpr : public AstExpr { /// 这个和 Identifier 是不同的
    public:
        AstObjectExpr( ) 
            : AstExpr( )
        {
        }
        Token getObject() const {
            return m_tok;
        }
        virtual std::shared_ptr<AST::AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor,ICollectInfoBack* collect ) = 0;
    private:
        Token m_tok;
    };
}

