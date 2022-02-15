#pragma once
#include "Frontend/AST/Expr.h"
#include <string>
namespace ENV {
    class Env;
}
namespace AST {
    /// �����id��Ӧ�ű���,����˵һ���ɱ������ַ�Ķ���
    /// ��������,Ҳ�����������,���ʱ��Id�϶���ûʲô������
    /// ���ƿռ�Ҳ�����������
    /// ��ô���ĵķ��ű���ôʵ��,��֯��
    /// Id�Ǹ�ʲô,Id�Ǹ���������,Id����ĵ�����
    class ObjectExpr : public Expr { /// ����� Identifier �ǲ�ͬ��
    public:
        ObjectExpr(std::shared_ptr<ENV::TypeId> type) 
            : Expr( type )
        {
            
        }
        virtual std::string toString() const = 0;
        virtual std::shared_ptr<ENV::ObjectId> getObjectId() = 0;
    private:
    };
}

