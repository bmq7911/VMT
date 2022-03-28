#pragma once
#include <vector>
#include <string>
#include <string_view>

namespace IR {
	
	/// <summary>
	/// 不计划字节写数据结构,不是不愿意,而是C++ STL支持的基本东西都没学好
	/// </summary>
	class IRReaderLexer {
	public:
		enum TokenId {
			kKeyWord,
			kGrobalId,
			kLocalId,
			kLabel,
			kAttribute,
			kNumConst,
			kComma,
			kLeft_paren,
			kRight_paren,
			kLeft_brace,
			kRight_brace,
			kSemi,
			kEqual,
			kString,
			kEof,
			kError,
		};

		static const char* getTokenIdString( TokenId id){
			return nullptr;
		}

		class Token {
		public:
			Token( TokenId id) 
				: m_id( id )
				, m_strView()
				, m_lineNumber( 0 )
				, m_colNumber( 0 )
			{
			}
			Token(Token const& tok) {
				m_id = tok.m_id;
				m_strView = tok.m_strView;
				m_lineNumber = tok.m_lineNumber;
				m_colNumber = tok.m_colNumber;
			}
			Token& operator=(Token const& tok) {
				if (this != &tok) {
					m_id = tok.m_id;
					m_strView = tok.m_strView;
					m_lineNumber = tok.m_lineNumber;
					m_colNumber = tok.m_colNumber;
				}
				return *this;
			}
			TokenId getTokenId() const {
				return m_id;
			}
			std::string to_string() const {
				if (m_id != TokenId::kEof && m_id != TokenId::kError) {
					return std::string(m_strView.data( ), m_strView.length());
				}
				return std::string();
			}
			std::string_view getStringView() const {
				return m_strView;
			}
			std::pair<size_t, size_t> get_location() const {
				return std::make_pair(m_lineNumber, m_colNumber);
			}
		private:
			friend class IRReaderLexer;
			TokenId m_id;
			std::string_view m_strView;
			size_t m_lineNumber;
			size_t m_colNumber;
		};

		IRReaderLexer() 
			: m_src()
			, m_scanIndex( -1 )
			, m_lineNumber( 0 )
			, m_colNumber( -1 )
		{}
		IRReaderLexer( const char * str) 
			: IRReaderLexer()
		{
			size_t length = strlen(str);
			m_src.resize(length);
			memcpy(m_src.data(), str, length);
		}
		Token scan() {
			int32_t ch = _Scan();
			if (ch == EOF) {
				return Token(TokenId::kEof);
			}
			while (ch == ' ' || ch == '\t') {
				ch = _Scan();
			}
			/// <summary>
			if (ch == '@') { /// 全局表示
				size_t start = _GetScanIndex();
				ch = _Scan();
				if ( !('a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_' || ch=='.' )) {
					_Rowback( );
					return Token(kError);
				}

				do {
					ch = _Scan();
					bool right = 'a' <= ch && ch <= 'z' ||
						'A' <= ch && ch <= 'Z' ||
						'0'<=ch && ch<='9' ||
						'.' == ch || '@'==ch;
					if (false == right) {
						_Rowback( );
						size_t end = _GetScanIndex();
						return _GenToken( TokenId::kGrobalId, start, end);
					}
				} while ( true );
	
			}
			else if (ch == '%') { /// 局部表示
				size_t start = _GetScanIndex();
				ch = _Scan();
				if ( !('a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_' || ch=='.' || '0'<=ch && ch<='9')) {
					_Rowback( );
					return Token(kError);
				}

				do {
					ch = _Scan();
					bool right = 'a' <= ch && ch <= 'z' ||
						'A' <= ch && ch <= 'Z' ||
						'0' <=ch && ch <='9' ||
						'.' == ch || '@'==ch;
					if (false == right) {
						_Rowback( );
						size_t end = _GetScanIndex();
						return _GenToken( TokenId::kLocalId, start, end);
					}
				} while ( true );
			}
			else if (ch == '#') { /// 属性
				size_t start = _GetScanIndex();
				ch = _Scan();
				if ( !('0' <= ch && ch <= '9')){
					_Rowback();
					return Token(TokenId::kError);
				}
				do {
					ch = _Scan();
					bool right = '0' <= ch && ch <= '9';
					if (false == right) {
						_Rowback();
						size_t end = _GetScanIndex();
						return _GenToken( TokenId::kAttribute, start, end);
					}
				} while ( true );
			}
			else if ('a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z') { /// 表示符号
				size_t start = _GetScanIndex();
				do {
					ch = _Scan();
					bool right = 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || '0' <= ch && ch <= '9';
					if (false == right) {
						_Rowback();
						size_t end = _GetScanIndex();
						return _GenToken( TokenId::kKeyWord, start, end);
					}
				} while (true);
			}
			else if( '0'<=ch && ch <='9') { /// 立即数
				size_t start = _GetScanIndex( );
				bool bFindPoint = false;
				do {
					ch = _Scan();
					bool right = '0' <= ch && ch <= '9';
					if (false == right) {
						if ('.' == ch && bFindPoint == false) {
							bFindPoint = true;
							continue;
						}
						else {
							_Rowback();
							size_t end = _GetScanIndex();
							return _GenToken( TokenId::kNumConst, start, end);
						}
					}
				} while (true);
			}
			else if (',' == ch) { /// 分割符号
				size_t start = _GetScanIndex();
				size_t end = start;
				return _GenToken(TokenId::kComma, start, end);
			}
			else if ('(' == ch) {
				size_t start = _GetScanIndex();
				size_t end = start;
				return _GenToken(TokenId::kLeft_paren, start, end);
			}
			else if (')' == ch) {
				size_t start = _GetScanIndex();
				size_t end = start;
				return _GenToken(TokenId::kRight_paren, start, end);
			}
			else if ('{' == ch) {
				size_t start = _GetScanIndex();
				size_t end = start;
				return _GenToken(TokenId::kLeft_brace, start, end);
			}
			else if ('}' == ch) {
				size_t start = _GetScanIndex();
				size_t end = start;
				return _GenToken(TokenId::kRight_brace, start, end);
			}
			else if ('=' == ch) {
				size_t start = _GetScanIndex();
				size_t end = start;
				return _GenToken(TokenId::kEqual, start, end);
			}
			else if (';' == ch) {
				do {
					ch = _Scan();
					if (ch != '\r' && ch != '\n') {
						continue;
					}
					else {
						_Rowback();
						break;
					}
				} while ( true );
				return scan( );
			}
			else if ('\"' == ch) {
				auto start = _GetScanIndex();
				do {
					ch = _Scan();
					if (ch == '\r' || ch == '\n') {
						auto end = _GetScanIndex();
						_Rowback( );
						return _GenToken(TokenId::kError, start, end);
					}
					else if (ch == '\"') {
						auto end = _GetScanIndex();
						return _GenToken(TokenId::kString, start, end);
					}
				
				} while ( true );
			}
			else if ('\r' == ch) {
				auto t = _Scan();
				if (t != '\n') {
					_Rowback();
				}
				m_lineNumber++;
				m_colNumber = -1;
				return scan();
			}
			else if ('\n' == ch) {
				m_lineNumber++;
				m_colNumber = -1;
				return scan();
			}
			else { /// error
				size_t start = _GetScanIndex();
				size_t end = start;
				return _GenToken(TokenId::kError, start, end);
			}
		}

	private:
		int32_t _Scan() {
			m_scanIndex++;
			m_colNumber++;
			if (m_scanIndex >= m_src.size()) {
				return EOF;
			}
			return m_src.at(m_scanIndex);
		}
		size_t _GetLineNumber() const{
			return m_lineNumber;
		}
		size_t _GetColNumber() const {
			return m_colNumber;
		}
		size_t _GetScanIndex() const {
			return m_scanIndex;
		}
		void _Rowback() {
			m_colNumber--;
			m_scanIndex--;
		}
		std::string_view _GetStringView(size_t start, size_t end) {
			return std::string_view(m_src.data() + start, end - start + 1);
		}
		Token _GenToken(TokenId tokId, size_t start, size_t end) {
			Token tok(tokId);
			tok.m_strView = _GetStringView(start, end);
			tok.m_lineNumber = _GetLineNumber();
			tok.m_colNumber = _GetColNumber() - ( end - start );
			return tok;
		}
	private:
		std::vector<char> m_src;
		size_t            m_scanIndex;
		size_t            m_lineNumber;
		size_t            m_colNumber;
	};

}