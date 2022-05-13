#pragma once
namespace AST{
    class IASTVisitor;
}

#include "Frontend/AST/AstTree.h"
#include "Frontend/AST/AstPair.h"

#include "Frontend/AST/AstIfStmt.h"
#include "Frontend/AST/AstElseStmt.h"
#include "Frontend/AST/AstExpr.h"
#include "Frontend/AST/AstExprs.h"


#include "Frontend/AST/AstBinaryOpExpr.h"
#include "Frontend/AST/AstUnaryOpExpr.h"
#include "Frontend/AST/AstConstantExpr.h"
#include "Frontend/AST/AstObjectExpr.h"
#include "Frontend/AST/AstConditionExpr.h"
#include "Frontend/AST/AstVoidExpr.h"
#include "Frontend/AST/AstVariableObjExpr.h"
#include "Frontend/AST/AstDecl.h"
#include "Frontend/AST/AstAssign.h"
#include "Frontend/AST/AstStmt.h"
#include "Frontend/AST/AstStmts.h"
#include "Frontend/AST/AstExprStmt.h"
#include "Frontend/AST/AstReturnStmt.h"
#include "Frontend/AST/AstLoopStmt.h"
#include "Frontend/AST/AstWhileStmt.h"
#include "Frontend/AST/AstDoWhileStmt.h"
#include "Frontend/AST/AstForStmt.h"
#include "Frontend/AST/AstBreakStmt.h"
#include "Frontend/AST/AstContinueStmt.h"
#include "Frontend/AST/AstProgram.h"
#include "Frontend/AST/AstTemp.h"
#include "Frontend/AST/AstAttribute.h"
#include "Frontend/AST/AstType.h"
#include "Frontend/AST/AstFunctionBody.h"
#include "Frontend/AST/AstBlock.h"
#include "Frontend/AST/AstProgram.h"


