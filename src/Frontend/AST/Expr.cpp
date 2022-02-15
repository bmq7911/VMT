#include "Frontend/AST/ASTVisitor.h"
#include "Frontend/AST/UnaryOpExpr.h"
#include "Frontend/AST/BinaryOpExpr.h"
#include "Frontend/AST/ConditionExpr.h"
#include "Frontend/AST/Exprs.h"
#include "Frontend/AST/ObjectExpr.h"
#include "Frontend/AST/VoidExpr.h"
#include "Frontend/AST/Temp.h"
#include "Frontend/AST/VariableObjExpr.h"
#include "SymbolTable/ObjectId.h"


#define DECL_AST_SPACE( x) AST

namespace DECL_AST_SPACE(UnaryOpExpr) {
    UnaryOpExpr::UnaryOpExpr(std::shared_ptr<AST::Expr> expr, Token tok, std::shared_ptr<ENV::TypeId> type)
        : Expr(type)
        , m_expr(expr)
        , m_op(tok)

    {
    }
    std::shared_ptr<UnaryOpExpr> UnaryOpExpr::makeUnaryOpExpr(std::shared_ptr<AST::Expr> expr, Token tok) {
        auto typeId = expr->getTypeId();
        auto newType = typeId->Op(tok.getTag());
        return std::make_shared<UnaryOpExpr>(expr, tok, newType);
    }
    std::shared_ptr<AST::Expr> UnaryOpExpr::getExpr() const {
        return m_expr;
    }
    Token UnaryOpExpr::getOp() const {
        return m_op;
    }
    std::shared_ptr<AST::ObjectExpr> UnaryOpExpr::reduce(std::shared_ptr<AST::IASTVisitor> visitor)  {
        return visitor->reduceUnaryOpExpr(std::enable_shared_from_this<UnaryOpExpr>::shared_from_this());
    }
}

namespace DECL_AST_SPACE(BinaryOpExpr) {
    BinaryOpExpr::BinaryOpExpr(std::shared_ptr<Expr> left,
        std::shared_ptr<Expr> right,
        Token tok,
        std::shared_ptr<ENV::TypeId> type)
        : Expr(type)
        , m_left(left)
        , m_right(right)
        , m_op(tok)
    {

    }

    std::shared_ptr<BinaryOpExpr> BinaryOpExpr::makeBinaryOpExpr(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right, Token tok) {
        auto type = left->getTypeId();
        auto newType = type->Op(tok.getTag(), right->getTypeId());
        return std::make_shared<AST::BinaryOpExpr>(left, right, tok, newType);
    }

    std::shared_ptr<Expr> BinaryOpExpr::getLeft() const {
        return m_left;
    }

    std::shared_ptr<Expr>BinaryOpExpr::getRight() const {
        return m_right;
    }

    Token BinaryOpExpr::getOp() const {
        return m_op;
    }


    std::shared_ptr<AST::ObjectExpr> BinaryOpExpr::reduce(std::shared_ptr<AST::IASTVisitor> visitor) {
        return visitor->reduceBinaryOpExpr(std::enable_shared_from_this<BinaryOpExpr>::shared_from_this());
    }
}

namespace DECL_AST_SPACE(ConditionExpr) {
    ConditionExpr::ConditionExpr(std::shared_ptr<AST::Expr> condition, std::shared_ptr<AST::Expr> True, std::shared_ptr<AST::Expr> False)
        : m_condition(condition)
        , m_true(True)
        , m_false(False)
    {
    }
    std::shared_ptr<AST::Expr> ConditionExpr::getCondition() {
        return m_condition;
    }
    std::shared_ptr<AST::Expr> ConditionExpr::getTrueExpr() {
        return m_true;
    }
    std::shared_ptr<AST::Expr> ConditionExpr::getFalseExpr() {
        return m_false;
    }
    std::shared_ptr<AST::ObjectExpr> ConditionExpr::reduce(std::shared_ptr<AST::IASTVisitor> visitor) {
        return visitor->reduceConditionExpr(std::enable_shared_from_this<AST::ConditionExpr>::shared_from_this());
    }

}

namespace DECL_AST_SPACE(ConstantExpr) {

}

namespace DECL_AST_SPACE(Exprs) {
    void Exprs::add(std::shared_ptr<AST::Expr> expr) {
        m_exprs.push_back(expr);
    }
    size_t Exprs::size() const {
        return m_exprs.size();
    }
    std::shared_ptr<AST::Expr> Exprs::at(uint32_t i) const {
        if (i < size()) {
            return m_exprs.at(i);
        }
        return nullptr;
    }
    std::shared_ptr<AST::ObjectExpr> Exprs::reduce(std::shared_ptr<AST::IASTVisitor> visitor)  {
        auto exprs = std::enable_shared_from_this<AST::Exprs>::shared_from_this();
        return visitor->reduceExprs(std::enable_shared_from_this<AST::Exprs>::shared_from_this());
    }

}

namespace DECL_AST_SPACE(VariableObjExpr) {
    VariableObjExpr::VariableObjExpr(Token id, std::shared_ptr<ENV::TypeId> p ,std::shared_ptr<ENV::ObjectId> objectId)
        : ObjectExpr(p)
        , m_token(id)
        , m_type(p)
        , m_objectId( objectId)
    {
        m_env = nullptr;
    }
    VariableObjExpr::VariableObjExpr(const VariableObjExpr& obj)
        :ObjectExpr(obj)
    {
        m_token = obj.m_token;
        m_type = obj.m_type;
        m_objectId = obj.m_objectId;
        m_env = obj.m_env;
    }
    void VariableObjExpr::setEnv(std::shared_ptr<ENV::Env>  env) {
        this->m_env = env;
    }
    void VariableObjExpr::setObjectId(std::shared_ptr<ENV::ObjectId> objectId) {
        m_objectId = objectId;
    }
    std::shared_ptr<ENV::ObjectId> VariableObjExpr::getObjectId() {
        return m_objectId;
    }

    std::string VariableObjExpr::toString() const {
        return m_token.toString();
    }
    std::shared_ptr<ObjectExpr> VariableObjExpr::reduce(std::shared_ptr<AST::IASTVisitor> visitor ) {
        return visitor->reduceObjectExpr( std::enable_shared_from_this<AST::VariableObjExpr>::shared_from_this());
    }
}

namespace DECL_AST_SPACE( VoidExpr) {
    
    std::shared_ptr<AST::ObjectExpr> VoidExpr::reduce(std::shared_ptr<AST::IASTVisitor> visitor) {
        return visitor->reduceVoidExpr(std::enable_shared_from_this<AST::VoidExpr>::shared_from_this());
    }


}

namespace DECL_AST_SPACE( Temp ) {
    int Temp::count = 0;
    Temp::Temp(std::shared_ptr<ENV::TypeId> p)
        :ObjectExpr( p )
    {
        //m_object = std::make_shared<AST::ObjectExpr>();
        number = ++count;
    }

    std::string Temp::toString() const {
        return std::string("t") + std::to_string(number);
    }
    std::shared_ptr<ENV::ObjectId> Temp::getObjectId() {
        //Token tok();
        std::string name = "%" + std::to_string(number);
        return std::make_shared<ENV::ObjectId>( name.c_str(), getTypeId() );
    }
    std::shared_ptr<AST::ObjectExpr> Temp::reduce( std::shared_ptr<AST::IASTVisitor> visitor) {
        return visitor->reduceTemp(std::enable_shared_from_this<Temp>::shared_from_this());
    }
}
