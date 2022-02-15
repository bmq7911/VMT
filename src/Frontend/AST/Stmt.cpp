#include "Frontend/AST/ForStmt.h"
#include "Frontend/AST/IfStmt.h"
#include "Frontend/AST/DoWhileStmt.h"

#include "Frontend/AST/ASTVisitor.h"

#define DECL_AST_SPACE( x) AST



namespace DECL_AST_SPACE(IfStmt) {
    IfStmt::IfStmt(std::shared_ptr<Expr> boolexpr,
        std::shared_ptr<AST::Stmt> ifstmt,
        std::shared_ptr<AST::ElseStmt> elsestmt)
        : m_boolExpr(boolexpr)
        , m_stmt(ifstmt)
        , m_else(elsestmt)
    {

    }
    std::shared_ptr<AST::Expr> IfStmt::getBoolExpr() {
        return m_boolExpr;
    }
    std::shared_ptr<AST::Stmt> IfStmt::getIfStmt() {
        return m_stmt;
    }
    std::shared_ptr<AST::ElseStmt> IfStmt::getElseStmt() {
        return m_else;
    }
    /// 本质也是生成一种中间表示形式,且是四元式
    void IfStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor)  {
        visitor->visitIfStmt(shared_from_this());
    }
}

namespace DECL_AST_SPACE(ElseStmt) {
    ElseStmt::ElseStmt(std::shared_ptr<AST::Stmt> elsestmts)
        :m_stmt(elsestmts)
    {}
    std::shared_ptr<AST::Stmt> ElseStmt::getStmt() {
        return m_stmt;
    }
    void ElseStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor)  {
        visitor->visitElseStmt(shared_from_this());
    }
}


namespace DECL_AST_SPACE(ForStmt) {
    ForStmt::ForStmt(std::shared_ptr<AST::Expr> initExpr, std::shared_ptr<AST::Expr> boolExpr,
        std::shared_ptr<AST::Expr> tailExpr, std::shared_ptr<AST::Stmt> stmt)
        : LoopStmt(boolExpr)
        , m_initExpr(initExpr)
        , m_tailExpr(tailExpr)
        , m_stmt(stmt)
    {
    }
    std::shared_ptr<AST::Expr> ForStmt::getInitExpr() {
        return m_initExpr;
    }
    std::shared_ptr<AST::Expr> ForStmt::getTailExpr() {
        return m_tailExpr;
    }
    std::shared_ptr<AST::Stmt> ForStmt::getStmt() {
        return m_stmt;
    }
    void ForStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor) {
        visitor->visitForStmt(shared_from_this());
    }
}

namespace DECL_AST_SPACE(DoWhileStmt) {
    DoWhileStmt::DoWhileStmt(std::shared_ptr<AST::Expr> expr, std::shared_ptr<AST::Stmt> stmt)
        : LoopStmt(expr)
        , m_stmt(stmt)
    {
    }

    std::shared_ptr<AST::Stmt> DoWhileStmt::getStmt() {
        return m_stmt;
    }
    void DoWhileStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor)  {
        visitor->visitDoWhileStmt(shared_from_this());
    }

}

namespace DECL_AST_SPACE(WhileStmt) {
    WhileStmt::WhileStmt(std::shared_ptr<AST::Expr> expr, std::shared_ptr<AST::Stmt> stmt)
        : LoopStmt(expr)
        , m_stmt(stmt)
    {
    }

    std::shared_ptr<AST::Stmt> WhileStmt::getStmt() {
        return m_stmt;
    }
    void WhileStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor) {
        visitor->visitWhileStmt(shared_from_this());
    }
}

namespace DECL_AST_SPACE( BreakStmt ) {
    void BreakStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor)  {
        visitor->visitBreakStmt(shared_from_this());
    }

}

namespace DECL_AST_SPACE( ContinueStmt) {
    void ContinueStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor)  {
        visitor->visitContinueStmt(shared_from_this());
    }
}

namespace DECL_AST_SPACE(ExprStmt) {
    ExprStmt::ExprStmt(std::shared_ptr<Expr> & expr)
        : m_expr(expr)
    {

    }
    std::shared_ptr<AST::Expr> ExprStmt::getExpr() {
        return m_expr;
    }

    void ExprStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor) {
        visitor->visitExprStmt(shared_from_this());
    }

}

namespace DECL_AST_SPACE(Stmts) {
    void Stmts::add(std::shared_ptr<AST::Stmt> stmt) {
        m_stmts.push_back(stmt);
    }
    size_t Stmts::size() const {
        return m_stmts.size();
    }
    std::shared_ptr<AST::Stmt> Stmts::at(size_t index) {
        if (index < m_stmts.size()) {
            return m_stmts.at(index);
        }
        return nullptr;
    }
    void Stmts::gen(std::shared_ptr<AST::IASTVisitor> visitor) {
        visitor->visitStmts(shared_from_this());
    }
}

namespace DECL_AST_SPACE(ReturnStmt) {
    ReturnStmt::ReturnStmt(std::shared_ptr<AST::ExprStmt> stmt)
        : m_returnExprStmt(stmt)
    {

    }
    std::shared_ptr<AST::ExprStmt> ReturnStmt::getStmt(){
        return m_returnExprStmt;
    }
    void ReturnStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor) {
        visitor->visitReturnStmt(shared_from_this());
    }

}





