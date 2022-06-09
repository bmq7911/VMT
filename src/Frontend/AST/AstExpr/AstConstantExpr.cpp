#pragma once
#include <memory>
#include "Frontend/AST/AstVisitor.h"
#include "Frontend/AST/AstExpr/AstObjectExpr.h"
#include "Frontend/AST/AstExpr/AstConstantExpr.h"

namespace AST {



    std::shared_ptr<AST::AstObjectExpr> AstConstantExpr::reduce(std::shared_ptr<AST::IASTVisitor> visitor,ICollectInfoBack * collect ) {
		return visitor->reduceConstantExpr(this, collect);
    }


}