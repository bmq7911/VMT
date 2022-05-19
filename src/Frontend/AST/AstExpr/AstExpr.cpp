#include "Frontend/AST/AstVisitor.h"
#include "Frontend/AST/AstExpr/AstUnaryOpExpr.h"
#include "Frontend/AST/AstExpr/AstBinaryOpExpr.h"
#include "Frontend/AST/AstExpr/AstConditionExpr.h"
#include "Frontend/AST/AstExpr/AstObjectExpr.h"
#include "Frontend/AST/AstExpr/AstVoidExpr.h"
#include "Frontend/AST/AstExpr/AstTemp.h"
#include "Frontend/AST/AstExpr/AstVariableObjExpr.h"
#include "SymbolTable/ObjectId.h"


#define DECL_AST_SPACE( x) AST

namespace DECL_AST_SPACE(AstUnaryOpExpr) {
    AstUnaryOpExpr::AstUnaryOpExpr(std::shared_ptr<AST::AstExpr> expr, Token op)
        : m_expr(expr)
        , m_op( op )

    {
    }
    std::shared_ptr<AstUnaryOpExpr> AstUnaryOpExpr::makeUnaryOpExpr(std::shared_ptr<AST::AstExpr> expr, Token op) {
        return std::make_shared<AstUnaryOpExpr>(expr, op);
    }
    std::shared_ptr<AST::AstExpr> AstUnaryOpExpr::getExpr() const {
        return m_expr;
    }
    Token AstUnaryOpExpr::getOp() const {
        return m_op;
    }
    std::shared_ptr<AST::AstObjectExpr> AstUnaryOpExpr::reduce(std::shared_ptr<AST::IASTVisitor> visitor)  {
        return visitor->reduceUnaryOpExpr( this );
    }
}

namespace DECL_AST_SPACE(AstBinaryOpExpr) {
    AstBinaryOpExpr::AstBinaryOpExpr(std::shared_ptr<AstExpr> left,
        std::shared_ptr<AstExpr> right,
        Token tok)
        : m_left(left)
        , m_right(right)
        , m_op(tok)
    {

    }

    std::shared_ptr<AstBinaryOpExpr> AstBinaryOpExpr::makeBinaryOpExpr(std::shared_ptr<AstExpr> left, std::shared_ptr<AstExpr> right, Token tok) {
        return std::make_shared<AST::AstBinaryOpExpr>(left, right, tok);
    }

    std::shared_ptr<AstExpr> AstBinaryOpExpr::getLeft() const {
        return m_left;
    }

    std::shared_ptr<AstExpr> AstBinaryOpExpr::getRight() const {
        return m_right;
    }

    Token AstBinaryOpExpr::getOp() const {
        return m_op;
    }


    std::shared_ptr<AST::AstObjectExpr> AstBinaryOpExpr::reduce(std::shared_ptr<AST::IASTVisitor> visitor) {
        return visitor->reduceBinaryOpExpr( this );
    }
}

namespace DECL_AST_SPACE(AstConditionExpr) {
    AstConditionExpr::AstConditionExpr(std::shared_ptr<AST::AstExpr> condition, std::shared_ptr<AST::AstExpr> True, std::shared_ptr<AST::AstExpr> False)
        : m_condition(condition)
        , m_true(True)
        , m_false(False)
    {
    }
    std::shared_ptr<AST::AstExpr> AstConditionExpr::getCondition() {
        return m_condition;
    }
    std::shared_ptr<AST::AstExpr> AstConditionExpr::getTrueExpr() {
        return m_true;
    }
    std::shared_ptr<AST::AstExpr> AstConditionExpr::getFalseExpr() {
        return m_false;
    }
    std::shared_ptr<AST::AstObjectExpr> AstConditionExpr::reduce(std::shared_ptr<AST::IASTVisitor> visitor) {
        return visitor->reduceConditionExpr( this );
    }

}

namespace DECL_AST_SPACE(AstConstantExpr) {

}


namespace DECL_AST_SPACE(AstVariableObjExpr) {
    AstVariableObjExpr::AstVariableObjExpr(Token id)
        : AstObjectExpr(  )
        , m_token(id)
    {
    }
    AstVariableObjExpr::AstVariableObjExpr(const AstVariableObjExpr& obj)
        : AstObjectExpr(obj)
    {
        m_token = obj.m_token;
    }
    std::shared_ptr<AstObjectExpr> AstVariableObjExpr::reduce(std::shared_ptr<AST::IASTVisitor> visitor ) {
        return visitor->reduceObjectExpr( this );
    }
}

namespace DECL_AST_SPACE( AstVoidExpr) {
    
    std::shared_ptr<AST::AstObjectExpr> AstVoidExpr::reduce(std::shared_ptr<AST::IASTVisitor> visitor) {
        return visitor->reduceVoidExpr( this );
    }


}

namespace DECL_AST_SPACE( AstTemp ) {
    AstTemp::AstTemp( int32_t t)
        :  m_suffix( t )
    {
        //m_object = std::make_shared<AST::ObjectExpr>();
    }

    std::shared_ptr<AST::AstObjectExpr> AstTemp::reduce( std::shared_ptr<AST::IASTVisitor> visitor) {
        return visitor->reduceTemp( this );
    }
}
