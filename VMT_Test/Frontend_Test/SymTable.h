#pragma once
#include <map>
#include <string_view>
#include <string>
#include "Backend/IR/Type.h"
#include "Backend/IR/Value.h"
#include "SymFunction.h"
#include "SymNamespace.h"
#include "SymClass.h"
#include "SymOperator.h"

enum SymType {
	kValue,     // 变量
	kType,      // 类型
	kFunction,  // 函数
	kClass,     // 类
	kNamespace, // 名称空间
	kOperator,  // 算子

	kUnknown = 0xFFFFFFF,
};

class Symbol {
public:
	Symbol(IR::Value* value) 
		: m_type( SymType::kValue)
		, m_value( value )
	{
	}

	Symbol(IR::Type* type) 
		: m_type( SymType::kType)
		, m_value( type )
	{
	}

	template<typename T, typename ... _Args>
	Symbol( _Args &&... args ) 
		: m_type( __Symbol_traits<T>::stype )
		, m_value( new T(std::forward<_Args>(args) ...) )
	{
	}

	~Symbol() {
		_Destroy();
	}
	SymType getSymType() const {
		return m_type;
	}
	template<typename T>
	T* get( ) const {
		return _Is_equal<__Symbol_traits<T>::stype>(m_type) ? (T*)m_value : (T*)nullptr;
	}
private:
	template<typename T>
	static void __wrap_dctor(void* ptr)  {
		if (nullptr != ptr ) {
			delete (T*)ptr;
		}
	}
	void _Destroy() {
		if (m_type == SymType::kValue || m_type == SymType::kType) {
			
		}
		else {
			struct __dctor {
				SymType type;
				void(*d)(void*);
			};
			static const __dctor dctors[] = {
				{kFunction,  __wrap_dctor<SymFunction>  },
				{kClass,     __wrap_dctor<SymClass>     },
				{kNamespace, __wrap_dctor<SymNamespace> },
				{kOperator,  __wrap_dctor<SymOperator>  },
				// you can add your type in there


				{kUnknown, nullptr}
			};
			for (__dctor const * ptr = dctors; ptr->type != SymType::kUnknown; ++ptr) {
				if (ptr->type == m_type) {
					ptr->d(m_value);
					break;
				}
			}
		}
	}

	template<SymType T>
	static bool _Is_equal(SymType type) {
		return T == type ? true : false;
	}

	template<typename T>
	struct __Symbol_traits;

#define __SYMTABLE_DEFINE_SYMBOL_TRAITS( x, y)\
	template<>\
	struct __Symbol_traits<x> {\
		static const SymType stype = SymType::y;\
		using type = x;\
	};\

	__SYMTABLE_DEFINE_SYMBOL_TRAITS( IR::Value,			kValue)
	__SYMTABLE_DEFINE_SYMBOL_TRAITS( IR::Type,			kType)
	__SYMTABLE_DEFINE_SYMBOL_TRAITS( SymFunction,		kFunction)
	__SYMTABLE_DEFINE_SYMBOL_TRAITS( SymClass,			kClass)
	__SYMTABLE_DEFINE_SYMBOL_TRAITS( SymNamespace,		kNamespace)
	__SYMTABLE_DEFINE_SYMBOL_TRAITS( SymOperator,		kOperator)

#undef __SYMTABLE_DEFINE_SYMBOL_TRAITS

private:
	SymType			  m_type;
	void*			  m_value;
};

class SymTable : public std::enable_shared_from_this<SymTable> {
public:
	static std::shared_ptr<SymTable> makeSymTable(std::shared_ptr<SymTable> parent) {
		return std::make_shared<SymTable>( parent );
	}
	std::shared_ptr<SymTable> getParent() const {
		return m_lpParent;
	}
	Symbol const *find(std::string const& sym) const {
		auto iter = m_symTypes.find( sym );
		if ( m_symTypes.end() == iter) {
			return nullptr;
		}
		return &iter->second;
	}
	template<typename T>
	T* get( std::string const & sym ) const {
		auto iter = m_symTypes.find(sym);
		if (m_symTypes.end() == iter)
			return nullptr;
		else {
			return iter->second.get<T>();
		}
	}
	size_t size() const {
		return m_symTypes.size();
	}
	bool empty()const {
		return m_symTypes.empty();
	}
	bool put( std::string const& sym, IR::Value * v) {
		auto pair = m_symTypes.insert(std::make_pair(sym, Symbol(v)));
		return pair.second;
	}
	bool put(std::string const& sym, IR::Type* v) {
		auto pair = m_symTypes.insert(std::make_pair(sym, Symbol(v)));
		return pair.second;
	}
	template<typename T, typename ... _Args>
	bool put(std::string const& sym, _Args && ... args) {
		auto pair = m_symTypes.insert(std::make_pair(sym, Symbol<T>(std::forward<_Args>(args) ...)));
		return pair.second( );
	}
	SymTable() { }
	SymTable(std::shared_ptr<SymTable> parent ) 
		: m_lpParent( parent )
	{}
	
private:
	std::shared_ptr<SymTable>           m_lpParent;
	std::map<std::string, Symbol>		m_symTypes;

};
