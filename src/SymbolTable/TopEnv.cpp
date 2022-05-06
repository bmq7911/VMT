#include <string.h>
#include "SymbolTable/TopEnv.h"
#include "SymbolTable/ObjectId.h"
#include "Frontend/AST/AstConstantExpr.h"
#include "Frontend/AST/AstBoolConstantExpr.h"
#include "SymbolTable/IntegerType.h"
#include "SymbolTable/BoolType.h"
#include "SymbolTable/RealType.h"
#include "SymbolTable/VoidType.h"
#include "SymbolTable/ArbitraryType.h"

namespace ENV {
    TopEnv::TopEnv()
        :Env(nullptr)
    {

#ifndef __ENV_TOP_ENV_INPUT
#define __ENV_TOP_ENV_INPUT(name, type ) put(name, getBasicType(ENV::BasicType::type ))
        __ENV_TOP_ENV_INPUT("i8",kI8);
        __ENV_TOP_ENV_INPUT("i16",kI16);
        __ENV_TOP_ENV_INPUT("i32",kI32);
        __ENV_TOP_ENV_INPUT("i64",kI64);
        __ENV_TOP_ENV_INPUT("ui8",kUI8);
        __ENV_TOP_ENV_INPUT("ui16",kUI16);
        __ENV_TOP_ENV_INPUT("ui32",kUI32);
        __ENV_TOP_ENV_INPUT("ui64",kUI64);
        __ENV_TOP_ENV_INPUT("f32",kF32);
        __ENV_TOP_ENV_INPUT("f64",kF64);
        __ENV_TOP_ENV_INPUT("void",kVoid);
        __ENV_TOP_ENV_INPUT("bool",kBool);
        __ENV_TOP_ENV_INPUT("arbitrary", kArbitrary);
#undef __ENV_TOP_ENV_INPUT
#endif ///__ENV_TOP_ENV_INPUT
        //std::shared_ptr<AST::Expr> falseExpr = std::make_shared<AST::BoolConstantExpr>(  getBasicType(ENV::BasicType::kBool), Token(Tag::kw_false), false);
        //std::shared_ptr<AST::Expr> trueExpr = std::make_shared<AST::BoolConstantExpr>(  getBasicType(ENV::BasicType::kBool), Token(Tag::kw_true), true);
        
        
        std::shared_ptr<ENV::ObjectId> falseObj = std::make_shared<ENV::ObjectId>("false", getBasicType( BasicType::kBool ) );
        std::shared_ptr<ENV::ObjectId> trueObj = std::make_shared<ENV::ObjectId>("true",  getBasicType(BasicType::kBool));

        put("false", falseObj);
        put("true", trueObj);
    }


    std::shared_ptr<ENV::TypeId> TopEnv::getBasicType(const char * name) {
        struct StrEnumMap {
            const char* name;
            BasicType   type;
        };

        static StrEnumMap map[] = {
#ifndef __ENV_TOP_ENV_INPUT
#define __ENV_TOP_ENV_INPUT(name, type ) {name, ENV::BasicType::type }
        __ENV_TOP_ENV_INPUT("i8",kI8),
        __ENV_TOP_ENV_INPUT("i16",kI16),
        __ENV_TOP_ENV_INPUT("i32",kI32),
        __ENV_TOP_ENV_INPUT("i64",kI64),
        __ENV_TOP_ENV_INPUT("ui8",kUI8),
        __ENV_TOP_ENV_INPUT("ui16",kUI16),
        __ENV_TOP_ENV_INPUT("ui32",kUI32),
        __ENV_TOP_ENV_INPUT("ui64",kUI64),
        __ENV_TOP_ENV_INPUT("f32",kF32),
        __ENV_TOP_ENV_INPUT("f64",kF64),
        __ENV_TOP_ENV_INPUT("void",kVoid),
        __ENV_TOP_ENV_INPUT("bool",kBool),
        __ENV_TOP_ENV_INPUT(nullptr,kBool),
#undef __ENV_TOP_ENV_INPUT
#endif ///__ENV_TOP_ENV_INPUT
        };



        for (StrEnumMap* t =&map[0]; t->name != nullptr; ++t ) {
            if (0 == strcmp(t->name, name)) {
                return getBasicType(t->type);
            }
        }
        return nullptr;
    }

    std::shared_ptr<ENV::TypeId> TopEnv::getBasicType(BasicType type) {
        switch (type) {
#ifndef __ENV_TOP_ENV_INPUT
#define __ENV_TOP_ENV_INPUT(name,type, Enum) case ENV::BasicType::Enum : {static std::shared_ptr<ENV::type> t= std::make_shared<ENV::type>(#name); return t;}break
            __ENV_TOP_ENV_INPUT(i8, IntegerType<int8_t>, kI8);
            __ENV_TOP_ENV_INPUT(i16, IntegerType<int16_t>, kI16);
            __ENV_TOP_ENV_INPUT(i32, IntegerType<int32_t>, kI32);
            __ENV_TOP_ENV_INPUT(i64, IntegerType<int64_t>, kI64);
            __ENV_TOP_ENV_INPUT(ui8, IntegerType<uint8_t>, kUI8);
            __ENV_TOP_ENV_INPUT(ui16, IntegerType<uint16_t>, kUI16);
            __ENV_TOP_ENV_INPUT(ui32, IntegerType<uint32_t>, kUI32);
            __ENV_TOP_ENV_INPUT(ui64, IntegerType<uint64_t>, kUI64);
            __ENV_TOP_ENV_INPUT(f32, RealType<float>, kF32);
            __ENV_TOP_ENV_INPUT(f64, RealType<double>, kF64);
            __ENV_TOP_ENV_INPUT(void, VoidType, kVoid);
            __ENV_TOP_ENV_INPUT(bool, BoolType, kBool);
#undef __ENV_TOP_ENV_INPUT
        case BasicType::kArbitrary: {
            static std::shared_ptr<ENV::TypeId> t = std::make_shared<ENV::ArbitraryType>( "arbitrary" );
            return t;
        }
#endif ///__ENV_TOP_ENV_INPUT
        default:
            break;
        }
    
    }
    std::shared_ptr<TopEnv> getTopEnv() {
        static std::shared_ptr<TopEnv> top;
        if ( !top) {
            top = std::make_shared<ENV::TopEnv>();
        }
        return top;
    }

}
