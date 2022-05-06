#pragma once
#include "Frontend/AST/AstTree.h"
#include "Frontend/AST/AstFunction.h"
#include "Frontend/AST/AstStructure.h"
#include "Frontend/AST/AstPair.h"

namespace AST {
    class AstProgram :public AstTree {
    public:
    private:
        std::shared_ptr<AST::AstPair<AST::AstFunction>> m_function;
        std::shared_ptr<AST::AstPair<AST::AstStructure>> m_structure;
    };
}