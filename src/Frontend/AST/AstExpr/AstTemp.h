#pragma once
#include <stdint.h>
#include "Frontend/AST/AstExpr/AstObjectExpr.h"

namespace AST {
    class IASTVisitor;
    class AstTemp : public AstObjectExpr {
    public:
        using super = AstObjectExpr;
    public:
        AstTemp( int32_t i);

        std::shared_ptr<AST::AstObjectExpr> reduce( std::shared_ptr<AST::IASTVisitor>,ICollectInfoBack* collect) override;
    private:
        int32_t m_suffix = 0;
    };
}
