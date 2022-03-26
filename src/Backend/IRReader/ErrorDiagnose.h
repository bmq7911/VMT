
#pragma once

namespace IR {
	class ErrorDiagnose {
	public:
		void expectBut( const char * expect, const char *but    ) {
			std::string_view expect_v(expect);
			std::string_view but_v(but);
			expectBut(expect_v, but_v);
		}

		void expectBut(std::string_view const& expect, std::string_view const& but) {

		}
	private:

	};

}