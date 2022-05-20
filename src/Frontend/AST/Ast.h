#pragma once
namespace AST{
    class IASTVisitor;
}

#include "Frontend/AST/AstTree.h"

#include "Frontend/AST/AstOther/AstAttribute.h"
#include "Frontend/AST/AstOther/AstType.h"
#include "Frontend/AST/AstOther/AstParamList.h"
#include "Frontend/AST/AstOther/AstPair.h"

#include "Frontend/AST/AstExpr/AstExpr.h"
#include "Frontend/AST/AstExpr/AstTemp.h"
#include "Frontend/AST/AstExpr/AstBinaryOpExpr.h"
#include "Frontend/AST/AstExpr/AstUnaryOpExpr.h"
#include "Frontend/AST/AstExpr/AstConstantExpr.h"
#include "Frontend/AST/AstExpr/AstObjectExpr.h"
#include "Frontend/AST/AstExpr/AstConditionExpr.h"
#include "Frontend/AST/AstExpr/AstVoidExpr.h"
#include "Frontend/AST/AstExpr/AstVariableObjExpr.h"
#include "Frontend/AST/AstExpr/AstDecl.h"
#include "Frontend/AST/AstExpr/AstAssign.h"

#include "Frontend/AST/AstStmt/AstStmt.h"
#include "Frontend/AST/AstStmt/AstStmts.h"
#include "Frontend/AST/AstStmt/AstExprStmt.h"
#include "Frontend/AST/AstStmt/AstReturnStmt.h"
#include "Frontend/AST/AstStmt/AstLoopStmt.h"
#include "Frontend/AST/AstStmt/AstWhileStmt.h"
#include "Frontend/AST/AstStmt/AstDoWhileStmt.h"
#include "Frontend/AST/AstStmt/AstForStmt.h"
#include "Frontend/AST/AstStmt/AstBreakStmt.h"
#include "Frontend/AST/AstStmt/AstContinueStmt.h"
#include "Frontend/AST/AstStmt/AstIfStmt.h"
#include "Frontend/AST/AstStmt/AstElseStmt.h"


#include "Frontend/AST/AstBlock.h"

#include "Frontend/AST/AstFunction/AstFunction.h"
#include "Frontend/AST/AstFunction/AstTemplateFunction.h"

#include "Frontend/AST/AstClass/AstClass.h"
#include "Frontend/AST/AstClass/AstTemplateClass.h"

#include "Frontend/AST/AstModule/AstModule.h"
