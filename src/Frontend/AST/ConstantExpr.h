#pragma once
#include <memory>
#include "Frontend/AST/ObjectExpr.h"
#include "Frontend/AST/Temp.h"
#include "SymbolTable/ObjectId.h"
namespace AST {

    template<typename _T>
    class ConstantExpr : public  ObjectExpr ,public std::enable_shared_from_this< ConstantExpr<_T> >{ 
    public:
        using HostType = _T;
        ConstantExpr( std::shared_ptr<ENV::TypeId> id, Token tok,HostType value)
            : ObjectExpr( id )
            , m_tok(tok)
            , m_const(value)
        {
        }
        std::shared_ptr<AST::ObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor) override {
            return std::enable_shared_from_this<ConstantExpr<_T>>::shared_from_this();
        }
        std::string toString() const override{
            return m_tok.toString();
        }
        std::shared_ptr<ENV::ObjectId> getObjectId()  override{
            return std::make_shared<ENV::ObjectId>( toString().c_str(), getTypeId() );
        }
    private:
        Token m_tok;
        HostType m_const;
    };


}