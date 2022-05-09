#pragma once
#include <vector>
#include "Frontend/AST/AstTree.h"
#include "Frontend/AST/AstObjectExpr.h"

namespace AST {
    class AstParam : public AstTree{
    public:
        AstParam() {
        }

        AstParam(AstParam const& param) {
            m_type = param.m_type;
            m_id = param.m_id;
        }

        AstParam& operator=(AstParam const& param) {
            if (this != &param) {
                m_type = param.m_type;
                m_id = param.m_id;
            }
            return *this;
        }

        void addId(Token type, Token id) {
            m_type = type;
            m_id = id;
        }
   private:
        Token m_type;
        Token m_id;
    };

    class AstParamList : public AstTree{
    public:
        void addParam(Token type, Token id) {
            AstParam p;
            p.addId(type, id);
            m_params.push_back(p);
        }
    private:
        std::vector<AstParam> m_params;
    };
    

}