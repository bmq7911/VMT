#pragma once
#include "Frontend/AST/AstObjectExpr.h"

namespace AST {
    /// ���������Ա���ֵ, �����Ǳ���Ҳ��������ʱ����(object)
    class AstVariableObjExpr :  public AstObjectExpr {
    public:
        using super = AstObjectExpr;
        AstVariableObjExpr(Token id);
        AstVariableObjExpr( const AstVariableObjExpr& obj);
        std::shared_ptr<AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor>)override;
    private:
        Token       m_token;
    };
}