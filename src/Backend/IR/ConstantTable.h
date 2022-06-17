#pragma once 
#include <set>
#include "Backend/IR/Constant.h"
namespace IR {
	class ConstantTable {
	public:

	private:
		std::set<Constant*> m_ConstantSets;
	};
}