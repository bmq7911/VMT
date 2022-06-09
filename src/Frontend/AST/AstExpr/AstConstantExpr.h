#pragma once
#include <memory>
#include "Frontend/AST/AstExpr/AstObjectExpr.h"
namespace AST {

    class AstConstantExpr : public  AstObjectExpr{ 
    public:
        AstConstantExpr(  Token tok )
            : AstObjectExpr( tok )
            , m_tok(tok)
        {
        }
        Token getToken() const {
            return m_tok;
        }
        std::shared_ptr<AST::AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor,ICollectInfoBack * collect ) override;
    private:
        Token m_tok;
    };


}