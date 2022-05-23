#pragma once
#include "Frontend/AST/AstExpr/AstObjectExpr.h"

namespace AST {
    /// 这个对象可以被赋值, 可能是变量也可能是临时变量(object)
    class AstVariableObjExpr :  public AstObjectExpr {
    public:
        using super = AstObjectExpr;
        AstVariableObjExpr(Token id);
        AstVariableObjExpr( const AstVariableObjExpr& obj);
        std::shared_ptr<AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor>,ICollectInfoBack* collect)override;
    private:
        Token       m_token;
    };
}
