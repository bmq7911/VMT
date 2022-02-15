#pragma once
#include <string>
#include "Frontend/AST/Node.h"
#include "Frontend/Lexer/Token.h"
#include "SymbolTable/TypeId.h"

namespace AST {
    ///
    class IASTVisitor;
    class ObjectExpr;

    class Expr : public Node {
    public:
        Expr() {}
        Expr(std::shared_ptr<ENV::TypeId> type) 
            : m_type( type)
        {}
        std::shared_ptr<ENV::TypeId> getTypeId() const {
            return m_type;
        }
        void setType(std::shared_ptr<ENV::TypeId> type) {
            m_type = type;
        }
        virtual std::shared_ptr<AST::ObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor) = 0;
    private:
        std::shared_ptr<ENV::TypeId>  m_type; /// 这就是一个 终结符/非终结符 的 属性
    };
}
