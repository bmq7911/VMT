#pragma once
#include <stdint.h>
#include <string>
#include <set>
#include <memory>
#include "ADT/rbtree.hpp"

namespace IR {
#define PAGE_SIZE 4096
	struct StrPage {
		size_t remain;
		char* page;
		static std::shared_ptr<StrPage> makeStrPage(size_t length) {
			if (0 == length)
				return nullptr;
			char* page = (char*)malloc(length);
			auto strpage = std::make_shared<StrPage>();
			strpage->remain = length;
			strpage->page = page;
		}
	};
	class StringTable {
	public:
		std::string_view put(std::string const& value) {
			if ( value.empty()) {
				return std::string_view();
			}
			else {
				size_t length = value.length() + 1;
			}
		}
		std::string_view put(const char* strPage) {}
	private:
		ADT::rbtree<StrPage> m_tables;
	};

}
