#pragma once
#include <string>
#include <vector>

namespace IR{
	class File {
	public:
		std::string const& getFilePath() const {
			return m_path;
		}

		std::string const& getFileName() const {
			return m_name;
		}
		
		std::string_view getSourceRef() const {
			return std::string_view(m_buffer.data(), m_buffer.size());
		}


	private:
		std::string m_path;
		std::string m_name;
		std::vector<char> m_buffer;
	};
}