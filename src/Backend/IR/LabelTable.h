#pragma once
#include <map>
#include <string>

namespace IR {
	class Label;
	class LabelTable {
	public:
		Label* findLabel(std::string const& name) const;
		bool   insertLabel(std::string const& name, Label* label);
		bool   empty() const;
		size_t size() const;
	private:
		std::map<std::string, Label*> m_lableMaps;
	};

}