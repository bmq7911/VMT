#pragma once
#include <memory>
#include "Frontend/AST/AstExpr/AstObjectExpr.h"
#include "Frontend/AST/AstExpr/AstTemp.h"
namespace AST {

    template<typename _T>
    class AstConstantExpr : public  AstObjectExpr{ 
    public:
        using HostType = _T;
        AstConstantExpr(  Token tok,HostType value)
            : AstObjectExpr( )
            , m_tok(tok)
            , m_const(value)
        {
        }
        std::shared_ptr<AST::AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor,ICollectInfoBack * collect ) override {
            return nullptr;
        }
    private:
        Token m_tok;
        HostType m_const;
    };


}