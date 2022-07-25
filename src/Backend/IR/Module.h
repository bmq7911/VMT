#pragma once
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "Backend/IR/Value.h"
#include "Backend/IR/Function.h"
#include "Backend/IR/Type.h"

namespace IR {
	class Module {
	public:
		
	private:
		std::string            m_mudleName;
		std::vector<Value*>    m_globalValue;
		std::vector<Function*> m_globalFunctions;
		std::vector<Type*>     m_type;
	};

}