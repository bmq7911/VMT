#pragma once
#include <map>
#include "Frontend/Lexer/File.h"

class FileManger {
private:
	FileManger() {
		
	}

private:
	std::map<uint32_t, std::shared_ptr<File>> m_files;
};