#pragma once
#include "Frontend/AST/ObjectExpr.h"

namespace AST {
    class IASTVisitor;
    class Temp : public std::enable_shared_from_this<Temp>, public ObjectExpr {
    public:
        using super = Expr;
    public:
        Temp(std::shared_ptr<ENV::TypeId> p);
        std::string toString() const override;
        std::shared_ptr<ENV::ObjectId> getObjectId() override;

        std::shared_ptr<AST::ObjectExpr> reduce( std::shared_ptr<AST::IASTVisitor>) override;
    private:
        static int count;
        int number = 0;
    };
}
