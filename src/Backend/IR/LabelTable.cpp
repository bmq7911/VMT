#include "LabelTable.h"
#include "Instruction.h"
namespace IR {
	
	Label* LabelTable::findLabel(std::string const& name) const{
		auto iter = m_lableMaps.find(name);
		if (iter == m_lableMaps.end()) {
			return nullptr;
		}
		return iter->second;
	}
	bool LabelTable::insertLabel(std::string const& name, Label* label) {
		if (nullptr != findLabel(name)) {
			return false;
		}
		else {
			m_lableMaps.insert(std::make_pair( name, label));
			return true;
		}
	}
	bool LabelTable::empty() const {
		return m_lableMaps.empty();
	}
	size_t LabelTable::size() const {
		return m_lableMaps.size();
	}
}