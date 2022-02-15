#pragma once
#include "Frontend/AST/Node.h"
#include "Frontend/AST/ObjectExpr.h"
#include "Frontend/AST/TopElement.h"
#include "Frontend/AST/Stmt.h"
#include "SymbolTable/TypeId.h"
#include "SymbolTable/FunctionId.h"

#include <vector>

namespace AST {
    class Param : public Node{
    public:
        void addId( std::shared_ptr<AST::ObjectExpr> id) {
            m_params.push_back(id);
        }
        size_t getSize() const {
            return m_params.size();
        }
        std::shared_ptr<AST::ObjectExpr> at(size_t index) {
            if (index >= m_params.size()) {
                return nullptr;
            }
            else {
                return m_params[index];
            }
        }
   private:
        std::vector<std::shared_ptr<AST::ObjectExpr> > m_params;
    };

    class ParamList : public Node {
    public:
        size_t getSize() const {
            if (nullptr != m_params) {
                return m_params->getSize();
            }
            return 0;
        }
        std::shared_ptr<AST::ObjectExpr> at(size_t index) {
            if (nullptr != m_params) {
                return m_params->at(index);
            }
            else {
                return nullptr;
            }
        }
        void setParam(std::shared_ptr<Param> param) {
            m_params = param;
        }
    private:
        std::shared_ptr<Param> m_params;
    };
    
    /// ������AST,�����﷨��
    /// �����﷨��:ÿ���ڲ��ڵ����һ�������,�ýڵ���ӽڵ�����������
    /// ���ǿ��԰�������俴��һ������,���غͱ�ʾҲ��ͳһ��Ϊ������
    /// ��������ô����, ����(�Ǻ�������),������������,������������(struct,template struct) 
    /// ��Щ������ô����,������ǰѺ�����������(����ĳ�����͵Ķ���),��ô����ͱ�Ϊ�˾������Ͷ����Ԥ�㼯��
    /// 
    class Function : public std::enable_shared_from_this<Function>, public  TopElement {
    public:
        void init(std::shared_ptr<ENV::TypeId>  type, Token name, std::shared_ptr<AST::Stmt> stmt, std::shared_ptr<ParamList> param, std::shared_ptr<ENV::Env> env) {
            m_type    = type;
            m_funName = name;
            m_args    = param;
            m_functionEnv = env;
            m_stmts       = stmt;
        }
        std::string getFunctionName() const{
            return m_funName.toString();
        }
        std::shared_ptr<AST::ParamList> getParamList() {
            return m_args;
        }
        std::shared_ptr<AST::Stmt>      getStmt() {
            return m_stmts;
        }
    private:
        std::shared_ptr<ENV::TypeId>     m_type;
        Token                            m_funName;
        std::shared_ptr<ParamList>       m_args;
        std::shared_ptr<AST::Stmt>       m_stmts;

        std::shared_ptr<ENV::Env>        m_functionEnv; 
        std::shared_ptr<ENV::FunctionId> m_functionInfo;
    };
}