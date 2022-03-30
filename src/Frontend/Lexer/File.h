#pragma once
#include <fstream>
#include <string>
#include <vector>

class File {
public:
	File(const char* strPath) 
		: m_path( strPath)
	{
		std::fstream fs;
		fs.open(strPath, std::ios::binary | std::ios::in );
		if (fs.is_open()) {
			fs.seekg(0, std::ios::end);
			auto size= fs.tellg();
			m_buffer.resize(size_t(size) + 1, char(0));
			fs.seekg(0, std::ios::beg);
			fs.read(m_buffer.data(), size);
		}
	}
	std::string const& getFilePath() const {
		return m_path;
	}

	std::string const& getFileName() const {
		return m_name;
	}

	std::string_view getSourceRef() const {
		return std::string_view(m_buffer.data(), m_buffer.size());
	}
	uint32_t getFileId() const {
		return m_fileId;
	}
private:
	std::string m_path;
	std::string m_name;
	std::vector<char> m_buffer;
	uint32_t          m_fileId;
};