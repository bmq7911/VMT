#pragma once
#include <vector>
#include "Frontend/AST/AstTree.h"
#include "Frontend/AST/AstObjectExpr.h"

namespace AST {
    class AstParam : public AstTree{
    public:
        void addId( std::shared_ptr<AST::AstObjectExpr> id) {
            m_params.push_back(id);
        }
        size_t getSize() const {
            return m_params.size();
        }
        std::shared_ptr<AST::AstObjectExpr> at(size_t index) {
            if (index >= m_params.size()) {
                return nullptr;
            }
            else {
                return m_params[index];
            }
        }
   private:
        std::vector<std::shared_ptr<AST::AstObjectExpr> > m_params;
    };

    class AstParamList : public AstTree{
    public:
        size_t getSize() const {
            if (nullptr != m_params) {
                return m_params->getSize();
            }
            return 0;
        }
        std::shared_ptr<AST::AstObjectExpr> at(size_t index) {
            if (nullptr != m_params) {
                return m_params->at(index);
            }
            else {
                return nullptr;
            }
        }
        void setParam(std::shared_ptr<AstParam> param) {
            m_params = param;
        }
    private:
        std::shared_ptr<AstParam> m_params;
    };
    

}