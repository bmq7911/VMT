#include "Frontend/AST/AstForStmt.h"
#include "Frontend/AST/AstIfStmt.h"
#include "Frontend/AST/AstDoWhileStmt.h"

#include "Frontend/AST/AstVisitor.h"

#define DECL_AST_SPACE( x) AST



namespace DECL_AST_SPACE(AstIfStmt) {
    AstIfStmt::AstIfStmt(std::shared_ptr<AstExpr> boolexpr,
        std::shared_ptr<AST::AstStmt> ifstmt,
        std::shared_ptr<AST::AstElseStmt> elsestmt)
        : m_boolExpr(boolexpr)
        , m_stmt(ifstmt)
        , m_else(elsestmt)
    {

    }
    std::shared_ptr<AST::AstExpr> AstIfStmt::getBoolExpr() {
        return m_boolExpr;
    }
    std::shared_ptr<AST::AstStmt> AstIfStmt::getIfStmt() {
        return m_stmt;
    }
    std::shared_ptr<AST::AstElseStmt> AstIfStmt::getElseStmt() {
        return m_else;
    }
    /// 本质也是生成一种中间表示形式,且是四元式
    void AstIfStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor)  {
        visitor->visitIfStmt( this );
    }
}

namespace DECL_AST_SPACE(AstElseStmt) {
    AstElseStmt::AstElseStmt(std::shared_ptr<AST::AstStmt> elsestmts)
        :m_stmt(elsestmts)
    {}
    std::shared_ptr<AST::AstStmt> AstElseStmt::getStmt() {
        return m_stmt;
    }
    void AstElseStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor)  {
        visitor->visitElseStmt( this );
    }
}


namespace DECL_AST_SPACE(AstForStmt) {
    AstForStmt::AstForStmt(std::shared_ptr<AST::AstExpr> initExpr, std::shared_ptr<AST::AstExpr> boolExpr,
        std::shared_ptr<AST::AstExpr> tailExpr, std::shared_ptr<AST::AstStmt> stmt)
        : AstLoopStmt(boolExpr)
        , m_initExpr(initExpr)
        , m_tailExpr(tailExpr)
        , m_stmt(stmt)
    {
    }
    std::shared_ptr<AST::AstExpr> AstForStmt::getInitExpr() {
        return m_initExpr;
    }
    std::shared_ptr<AST::AstExpr> AstForStmt::getTailExpr() {
        return m_tailExpr;
    }
    std::shared_ptr<AST::AstStmt> AstForStmt::getStmt() {
        return m_stmt;
    }
    void AstForStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor) {
        visitor->visitForStmt( this );
    }
}

namespace DECL_AST_SPACE(AstDoWhileStmt) {
    AstDoWhileStmt::AstDoWhileStmt(std::shared_ptr<AST::AstExpr> expr, std::shared_ptr<AST::AstStmt> stmt)
        : AstLoopStmt(expr)
        , m_stmt(stmt)
    {
    }

    std::shared_ptr<AST::AstStmt> AstDoWhileStmt::getStmt() {
        return m_stmt;
    }
    void AstDoWhileStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor)  {
        visitor->visitDoWhileStmt( this );
    }

}

namespace DECL_AST_SPACE(AstWhileStmt) {
    AstWhileStmt::AstWhileStmt(std::shared_ptr<AST::AstExpr> expr, std::shared_ptr<AST::AstStmt> stmt)
        : AstLoopStmt(expr)
        , m_stmt(stmt)
    {
    }

    std::shared_ptr<AST::AstStmt> AstWhileStmt::getStmt() {
        return m_stmt;
    }
    void AstWhileStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor) {
        visitor->visitWhileStmt( this );
    }
}

namespace DECL_AST_SPACE( AstBreakStmt ) {
    void AstBreakStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor)  {
        visitor->visitBreakStmt( this );
    }

}

namespace DECL_AST_SPACE( AstContinueStmt) {
    void AstContinueStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor)  {
        visitor->visitContinueStmt( this );
    }
}

namespace DECL_AST_SPACE(AstExprStmt) {
    AstExprStmt::AstExprStmt(std::shared_ptr<AstExpr> & expr)
        : m_expr(expr)
    {

    }
    std::shared_ptr<AST::AstExpr> AstExprStmt::getExpr() {
        return m_expr;
    }

    void AstExprStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor) {
        visitor->visitExprStmt( this );
    }

}

namespace DECL_AST_SPACE(AstStmts) {
    void AstStmts::add(std::shared_ptr<AST::AstStmt> stmt) {
        m_stmts.push_back(stmt);
    }
    size_t AstStmts::size() const {
        return m_stmts.size();
    }
    std::shared_ptr<AST::AstStmt> AstStmts::at(size_t index) {
        if (index < m_stmts.size()) {
            return m_stmts.at(index);
        }
        return nullptr;
    }
    void AstStmts::gen(std::shared_ptr<AST::IASTVisitor> visitor) {
        visitor->visitStmts( this );
    }
}

namespace DECL_AST_SPACE(AstReturnStmt) {
    AstReturnStmt::AstReturnStmt(std::shared_ptr<AST::AstExprStmt> stmt)
        : m_returnExprStmt(stmt)
    {

    }
    std::shared_ptr<AST::AstExprStmt> AstReturnStmt::getStmt(){
        return m_returnExprStmt;
    }
    void AstReturnStmt::gen(std::shared_ptr<AST::IASTVisitor> visitor) {
        visitor->visitReturnStmt( this );
    }

}





