#pragma once
#include "Frontend/AST/ObjectExpr.h"

namespace AST {
    /// ���������Ա���ֵ, �����Ǳ���Ҳ��������ʱ����(object)
    class VariableObjExpr :public std::enable_shared_from_this<VariableObjExpr>, public ObjectExpr {

    public:
        using super = ObjectExpr;
        VariableObjExpr(Token id, std::shared_ptr<ENV::TypeId> p ,std::shared_ptr<ENV::ObjectId> objectId);
        VariableObjExpr( const VariableObjExpr& obj);
        void setEnv(std::shared_ptr<ENV::Env>  env);
        void setObjectId( std::shared_ptr<ENV::ObjectId> objectId);
        std::string toString() const;
        std::shared_ptr<ENV::ObjectId> getObjectId() override;
        std::shared_ptr<ObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor>)override;
    private:
        Token       m_token;
        std::shared_ptr<ENV::TypeId>   m_type;
        std::shared_ptr<ENV::ObjectId> m_objectId;
        std::shared_ptr<ENV::Env>      m_env; /// �����SSD ֮�е��ս��/���ս�� �� ����
    };
}
