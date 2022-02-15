#pragma once
#include "Frontend/AST/Expr.h"
#include <string>
namespace ENV {
    class Env;
}
namespace AST {
    /// 这里的id对应着变量,或者说一个可被分配地址的对象
    /// 但是类型,也是有作用域的,这个时候Id肯定就没什么作用了
    /// 名称空间也是有作用域的
    /// 那么核心的符号表怎么实现,组织呢
    /// Id是个什么,Id是个可名对象,Id最核心的是名
    class ObjectExpr : public Expr { /// 这个和 Identifier 是不同的
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

