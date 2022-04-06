#pragma once
/// 这里就会存在顶层标签
#include "SymbolTable/Env.h"
class ModuleParser {
public:
private:
	std::shared_ptr<ENV::Env> m_env;
};