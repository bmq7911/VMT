#pragma once 
#include "Backend/IR/Constant.h"
namespace IR {
	class ConstantTable {
	public:

	private:
		std::set<Constant*> m_ConstantSets;
	};
}