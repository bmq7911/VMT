#pragma once
#include <vector>
#include <memory>

#include "Frontend/AST/AstTree.h"
#include "Frontend/AST/AstObjectExpr.h"
#include "Frontend/AST/AstStmt.h"
#include "Frontend/AST/AstType.h"
#include "Frontend/AST/AstAttribute.h"
#include "Frontend/AST/AstFunctionBody.h"
#include "Frontend/AST/AstParamList.h"
#include "SymbolTable/TypeId.h"
#include "SymbolTable/FunctionId.h"


namespace AST {

    class AstFunction :  public  AstTree{
    public:
        AstFunction( Token name, std::shared_ptr<AstType> type,std::shared_ptr<AstFunctionBody> body) 
            : m_funName( name)
            , m_type( type )
            , m_functionBody( body )
        {
        }
        Token getFunctionName() const;
        std::shared_ptr<AST::AstType> getFunctionType() const;
        std::shared_ptr<AST::AstFunctionBody> getFunctionBody() const;
        void gen(std::shared_ptr<AST::IASTVisitor> visitor);
    private:
        Token                                 m_funName;
        std::shared_ptr<AST::AstType>         m_type;
        std::shared_ptr<AST::AstAttribute>    m_attribute;
        std::shared_ptr<AST::AstFunctionBody> m_functionBody;
    };
}