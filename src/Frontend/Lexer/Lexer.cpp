#include "Frontend/Lexer/Lexer.h"

Lexer::Lexer() {

}

Lexer::Lexer(const char * filePath)
    :Lexer()
{
    std::fstream file;
    file.open(filePath, std::ios::in);
    if (!file.is_open()) {
        std::cout << "OpenFile Error" << std::endl;
        std::abort();
    }
    else {
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        file.seekg(0, std::ios::beg);
        m_strSrc.resize(size);
        file.read(m_strSrc.data(), size);
    }
}


Token Lexer::scan() {
    /// 过滤循环
    for (; ; _Readch()) { /// 非现实字符是在这里剔除的,而非在readch之中
        if ( m_peek == ' ' || m_peek == '\t') {
            continue;
        }
        else if (m_peek == EOF) {
            return _GenToken(TokenId::kw_eof);
        }
        else if (m_peek == '\r') {
            char c = _OffsetRead(1);
            if (c == '\n') {
                _Readch();
                m_lineStart = m_readPtr + 2;
                continue;
            }
            m_lineStart = m_readPtr + 1;
            continue;
        }
        else if (m_peek == '\n') {
            m_line = m_line + 1;
            m_col = 1;
            m_lineStart = m_readPtr+1;
            continue;
        }
        else 
            break;
    }
    /// 数字开头
    if (std::isdigit(m_peek)) { /// 数字开头
        return _ScanConstant();
    }
    /// 字母或者underline begin
    else if ((0 != std::isalpha(m_peek)) || ('_' == m_peek)) { /// 字符或者下划线
        return _ScanIdentifier();
    }
    else if (char(0) == m_peek) {
        return _GenToken(TokenId::kw_eof);
    }
    /// 处理各种标点符号
    else { ///非下划线开头的字符
        // 开始处理各种标点符号
        return _ScanPunctuation( );
        ///  这里是最复杂的
    }
    //Token* tok = new Token(peek); 
    //peek = ' ';
    //return tok;
}


void Lexer::startToken() {

}

uint32_t Lexer::getLineNum() const {
    return m_line;
}


uint32_t Lexer::getColNum() const {
    return m_col;
}

std::string Lexer::getLine() const {
    std::string str;
    for (size_t i = m_lineStart; i < m_strSrc.length(); ++i) {
        if ('\r' == m_strSrc[i] || '\n' == m_strSrc[i]) {
            break;
        }
        str.push_back(m_strSrc[i]);
    }
    return str;
}

void Lexer::_Readch() {
    m_readPtr++;
    m_forwardPtr = m_readPtr;
    m_peek = m_strSrc[m_readPtr];
    m_col++;
}

bool Lexer::_Readch(char c) {
    _Readch();
    if (m_peek != c) {
        return false;
    }
    m_peek = ' ';
    return true;
}

void Lexer::_ForwardSearch( ) {
    m_forwardPtr++;
    m_peek = m_strSrc[m_forwardPtr];
    m_col++;
}
char Lexer::_OffsetRead(int32_t offset) {
    int32_t ptr = m_readPtr;
    if (ptr + offset < 0 || ptr + offset >= m_strSrc.size()) {
        return char(0);
    }
    return m_strSrc[m_readPtr+offset];
}

Token Lexer::_GenToken(TokenId TokenId) const {
    Token tok;
    tok.m_location = _GenFileLocation();
    tok.m_tokenId = TokenId;
    return tok;
}

FileLocation Lexer::_GenFileLocation() const{
    FileLocation location( m_col, m_line, m_strSrc.data() + m_readPtr, m_forwardPtr - m_readPtr );
    location.m_col = m_col - (m_forwardPtr - m_readPtr ) -1;
    location.m_row = m_line;
    return location;
}

void  Lexer::_ResumeReadPtr() {
    m_readPtr = m_forwardPtr;
}


///
///
Token Lexer::_ScanConstant() {
    
    int v = 0;
    do { /// 这里没有处理进制问题
        v = 10 * v + m_peek - 0x30;
        _ForwardSearch();
    } while (std::isdigit(m_peek));
    if (m_peek != '.') {
        Token tok =  _GenToken(TokenId::kw_integer);
        ///
        _ResumeReadPtr();
        return tok;
    }
    else {
        float x = v; float d = 10;
        for (;;) {
            if (!std::isdigit(m_peek)) 
                break;
            x = x + (m_peek - 0x30) / d;
            d = d * 10;
            _ForwardSearch( );
        }
        Token  tok = _GenToken(TokenId::kw_real);
        _ResumeReadPtr();
        return tok;
    }

}

Token Lexer::_ScanIdentifier() {
    std::stringstream b;
    do {
        b << m_peek; 
        _ForwardSearch();
    } while (std::isalpha(m_peek) || std::isdigit(m_peek));
    std::string s = b.str();

    auto tokid = m_keyWord->findTokenIdFormStr(s.c_str());
    if (tokid != TokenId::kw_Unknown) {
        /// 构造一个 Token,插入TokenStream之中
        Token tok = _GenToken(tokid);
        _ResumeReadPtr();
        return tok;
    }
    else {
        Token tok = _GenToken(TokenId::kw_id);
        _ResumeReadPtr();
        return tok;
    }
    //auto iter = m_Identifier.find(s);
    //if (iter != m_Identifier.end()) {
    //    return iter->second;
    //}
    //Identifier * w = new Identifier(s, TokenId::id);
    //m_Identifier.insert(std::pair(s, w));
    //return w;
}

/// 代码结构是简单的,其本质和dfa没太大区别
Token Lexer::_ScanPunctuation() {
    switch (m_peek) {
    case '[': {
        _ForwardSearch();
        Token tok = _GenToken(TokenId::kw_l_square);
        _ResumeReadPtr();
        return tok;
    }break;
    case ']': {
        _ForwardSearch();
        Token tok = _GenToken(TokenId::kw_r_square);
        _ResumeReadPtr();
        return tok;
    }break;
    case '(': {
        _ForwardSearch();
        Token tok = _GenToken(TokenId::kw_l_paren);
        _ResumeReadPtr();
        return tok;
    }break;
    case ')': {
        _ForwardSearch();
        Token tok = _GenToken(TokenId::kw_r_paren);
        _ResumeReadPtr();
        return tok;
    }break;
    case '{': {
        _ForwardSearch();
        Token tok = _GenToken(TokenId::kw_l_brace);
        _ResumeReadPtr();
        return tok;
    }break;
    case '}': {
        _ForwardSearch();
        Token tok = _GenToken(TokenId::kw_r_brace);
        _ResumeReadPtr();
        return tok;
    }break;
    case '.': {
        _ForwardSearch();
        Token tok = _GenToken(TokenId::kw_period);
        _ResumeReadPtr();
        return tok;
    }break;

    case '&': {
        _ForwardSearch();
        if ('&' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_ampamp);
            _ResumeReadPtr();
            return tok;
        }
        else {
            Token tok = _GenToken(TokenId::kw_amp);
            _ResumeReadPtr();
            return tok;
        }
    }break;
    case '*': {
        _ForwardSearch();
        if ('*' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_starstar);
            _ResumeReadPtr();
            return tok;
        }
        else if ('=' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_starequal);
            _ResumeReadPtr();
            return tok;
        }
        else {
            Token tok = _GenToken(TokenId::kw_star);
            _ResumeReadPtr();
            return tok;
        }
    }break;
    case '+': {
        _ForwardSearch();
        if ('+' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_plusplus);
            _ResumeReadPtr();
            return tok;
        }
        else if ('=' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_plusequal);
            _ResumeReadPtr();
            return tok;
        }
        else {
            Token tok = _GenToken(TokenId::kw_plus);
            _ResumeReadPtr();
            return tok;
        }
    }break;
    case '-': {
        _ForwardSearch();
        if ('>' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_arrow);
            _ResumeReadPtr();
            return tok;
        }
        else if ('-' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_minusminus);
            _ResumeReadPtr();
            return tok;
        }
        else if ('=' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_minusequal);
            _ResumeReadPtr();
            return tok;
        }
        else {
            Token tok = _GenToken(TokenId::kw_minus);
            _ResumeReadPtr();
            return tok;
        }
    }break;
    case '~': {
        _ForwardSearch();
        Token tok = _GenToken(TokenId::kw_tilde);
        _ResumeReadPtr();
        return tok;
    }break;
    case '!': {
        _ForwardSearch();
        if ('=' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_exclaimequal);
            _ResumeReadPtr();
            return tok;
        }
        else {
            Token tok = _GenToken(TokenId::kw_exclaim);
            _ResumeReadPtr();
            return tok;
        }
    }break;
    case '/': { ///  这里还需要处理注释
        _ForwardSearch();
        if ('=' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_slashequal);
            _ResumeReadPtr();
            return tok;
        }
        else {
            Token tok = _GenToken(TokenId::kw_slash);
            _ResumeReadPtr();
            return tok;
        }
    }break;
    case '%': {
        _ForwardSearch();
        if ('=' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_percentequal);
            _ResumeReadPtr();
            return tok;
        }
        else {
            Token tok = _GenToken(TokenId::kw_percent);
            _ResumeReadPtr();
            return tok;
        }
    }break;
    case '<': {
        _ForwardSearch();
        if ('<' == m_peek) {
            _ForwardSearch();
            if ('=' == m_peek) {
                _ForwardSearch();
                Token tok = _GenToken(TokenId::kw_lessless);
                _ResumeReadPtr();
                return tok;
            }
            else {
                Token tok = _GenToken(TokenId::kw_lessless);
                _ResumeReadPtr();
                return tok;
            }
        }
        else if ('=' == m_peek) {
            _ForwardSearch();
            if ('>' == m_peek) {
                _ForwardSearch();
                Token tok = _GenToken(TokenId::kw_spaceship);
                _ResumeReadPtr();
                return tok;
            }
            else {
                Token tok = _GenToken(TokenId::kw_lessequal);
                _ResumeReadPtr();
                return tok;
            }

        }
        else {
            Token tok = _GenToken(TokenId::kw_less);
            _ResumeReadPtr();
            return tok;
        }
    }break;
    case '>': {
        _ForwardSearch();
        if ('>' == m_peek) {
            _ForwardSearch();
            if ('=' == m_peek) {
                _ForwardSearch();
                Token tok = _GenToken(TokenId::kw_greatergreaterequal);
                _ResumeReadPtr();
                return tok;
            }
            else {
                Token tok = _GenToken(TokenId::kw_greatergreater);
                _ResumeReadPtr();
                return tok;
            }
        }
        else if ('=' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_greaterequal);
            _ResumeReadPtr();
            return tok; 
        }
        else {
            Token tok = _GenToken(TokenId::kw_greater);
            _ResumeReadPtr();
            return tok;
        }
    }break;
    case '^': {
        _ForwardSearch();
        if ('=' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_caretequal);
            _ResumeReadPtr();
            return tok;
        }
        else {
            Token tok = _GenToken(TokenId::kw_caret);
            _ResumeReadPtr();
            return tok;
        }
    }break;
    case '|':{
        _ForwardSearch();
        if ('|' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_pipepipe);
            _ResumeReadPtr();
            return tok;
        }
        else if ('=' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_pipeequal);
            _ResumeReadPtr();
            return tok;
        }
        else {
            Token tok = _GenToken(TokenId::kw_pipe);
            _ResumeReadPtr();
            return tok;
        }
    }break;
    case '?': {
        _ForwardSearch();
        Token tok = _GenToken(TokenId::kw_question);
        _ResumeReadPtr();
        return tok;
    }break;
    case ':': {
        _ForwardSearch();
        if (':' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_coloncolon);
            _ResumeReadPtr();
            return tok;
        }
        else {
            Token tok = _GenToken(TokenId::kw_colon);
            _ResumeReadPtr();
            return tok;
        }
    }break;
    case ';': {
        _ForwardSearch();
        Token tok = _GenToken(TokenId::kw_semi);
        _ResumeReadPtr();
        return tok;
    }break;
    case '=': {
        _ForwardSearch();
        if ('=' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_equalequal);
            _ResumeReadPtr();
            return tok;
        }
        else {
            Token tok = _GenToken(TokenId::kw_equal);
            _ResumeReadPtr();
            return tok;
        }
    }break;
    case ',': {
        _ForwardSearch();
        Token tok = _GenToken(TokenId::kw_comma);
        _ResumeReadPtr();
        return tok;
    }break;
    case '#': {
        _ForwardSearch();
        if ('#' == m_peek) {
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_hashhash);
            _ResumeReadPtr();
            return tok;
        }
        else if('@' == m_peek){
            _ForwardSearch();
            Token tok = _GenToken(TokenId::kw_hashat);
            _ResumeReadPtr();
            return tok;
        }
        else {
            Token tok = _GenToken(TokenId::kw_hash);
            _ResumeReadPtr();
            return tok;
        }
    }break;
    default: {
        _ForwardSearch();
        Token tok = _GenToken(TokenId::kw_Unknown);
        _ResumeReadPtr();
        return tok;
    }break;
    }
    
}

