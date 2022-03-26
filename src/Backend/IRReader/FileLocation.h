#pragma once
#include <memory>
#include "Backend/IRReader/File.h"


namespace IR {
	class FileLocation {
	public:
		
	private:
		size_t m_col;
		size_t m_row;
		std::shared_ptr<File>   m_file;
	};

}