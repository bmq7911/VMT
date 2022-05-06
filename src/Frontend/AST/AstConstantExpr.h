#pragma once
#include <memory>
#include "Frontend/AST/AstObjectExpr.h"
#include "Frontend/AST/AstTemp.h"
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
        std::shared_ptr<AST::AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor) override {
            return nullptr;
        }
        std::string toString() const override{
            return m_tok.toString();
        }
    private:
        Token m_tok;
        HostType m_const;
    };


}