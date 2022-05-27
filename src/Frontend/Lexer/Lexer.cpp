#include "Frontend/Lexer/Lexer.h"

Lexer::Lexer() {

#define DECL_KEY_WORD(x,y,...)
#define KEYWORD(x) m_keyWordMap.insert( std::make_pair(#x, kw_##x) );
#include "Frontend/Lexer/KeyWord.def"
#undef KEYWORD
#undef DECL_KEY_WORD
    
}



Token Lexer::scan() {
    /// ����ѭ��
    for ( ; ; m_peek = _Readch()) { /// ����ʵ�ַ����������޳���,������readch֮��
        if ( m_peek == ' ' || m_peek == '\t') {
            continue;
        }
        else if (m_peek == EOF) {
            startToken();
            return genToken(TokenId::kw_eof);
        }
        else 
            break;
    }
    /// ���ֿ�ͷ
    if (std::isdigit(m_peek)) { /// ���ֿ�ͷ
        startToken();
        auto token = _ScanConstant();
        return token;
    }
    /// ��ĸ����underline begin
    else if ((0 != std::isalpha(m_peek)) || ('_' == m_peek)) { /// �ַ������»���
        startToken();
        return _ScanIdentifier();
    }
    else if (char(0) == m_peek) {
        startToken();
        return genToken(TokenId::kw_eof);
    }
    else if ('\r' == m_peek) {
        m_peek = _Readch( );
        if ('\n' == m_peek) {
            nextLine();
            m_peek = _Readch( );
            return scan();
        }
        else {
            nextLine();
            return scan( );
        }
    }
    else if ('\n' == m_peek) {
        nextLine();
        m_peek = _Readch();
        return scan();
    }
    else { ///���»��߿�ͷ���ַ�
        // ��ʼ������ֱ�����
        startToken();
        return _ScanPunctuation( );
        ///  ��������ӵ�
    }
}


void Lexer::startToken() {

}

Token Lexer::genToken(TokenId id) {
    return Token(id);
}

std::string_view Lexer::genLexeme( ) {
    return std::string_view();
}

void Lexer::nextLine() {

}

///
///
Token Lexer::_ScanConstant( ) {
    
    int v = 0;
    do { /// ����û�д����������
        v = 10 * v + m_peek - 0x30;
        m_peek = _Readch();
    } while (std::isdigit(m_peek));
    if (m_peek != '.') {
        Token tok =  genToken(TokenId::kw_integer);
        return tok;
    }
    else {
        m_peek = _Readch( );
        float x = v; float d = 10;
        for (;;) {
            if (!std::isdigit(m_peek)) 
                break;
            x = x + (m_peek - 0x30) / d;
            d = d * 10;
            m_peek = _Readch();
        }
        Token  tok = genToken(TokenId::kw_real);
        return tok;
    }

}

Token Lexer::_ScanIdentifier() {
    do {
        m_peek = _Readch();
    } while ( std::isalpha(m_peek) || std::isdigit(m_peek) || '_' == m_peek);
    std::string_view lexeme = genLexeme( );
    auto iter = m_keyWordMap.find( static_cast<std::string>(lexeme));
    if (iter != m_keyWordMap.end()) {
        return genToken(iter->second);
    }
    return genToken(TokenId::kw_id);
}

/// ����ṹ�Ǽ򵥵�,�䱾�ʺ�dfaû̫������
/// �������ʱ,���ǻ������ǰ��������
Token Lexer::_ScanPunctuation() {
    auto tmp = m_peek;
    Token tok;
    m_peek = _Readch();
    switch ( tmp ) {
    case '[': {
        tok = genToken(TokenId::kw_l_square);
    }break;
    case ']': {
        tok = genToken(TokenId::kw_r_square);
    }break;
    case '(': {
        tok = genToken(TokenId::kw_l_paren);
    }break;
    case ')': {
        tok = genToken(TokenId::kw_r_paren);
    }break;
    case '{': {
        tok = genToken(TokenId::kw_l_brace);
    }break;
    case '}': {
        tok = genToken(TokenId::kw_r_brace);
    }break;
    case '.': {
        tok = genToken(TokenId::kw_period);
    }break;

    case '&': {
        if ('&' == m_peek) {
            tok = genToken(TokenId::kw_ampamp);
            m_peek = _Readch();
        }
        else {
            tok = genToken(TokenId::kw_amp);
        }
    }break;
    case '*': {
        if ('*' == m_peek) {
            tok = genToken(TokenId::kw_starstar);
            m_peek = _Readch();
        }
        else if ('=' == m_peek) {
            tok = genToken(TokenId::kw_starequal);
            m_peek = _Readch();
        }
        else {
            tok = genToken(TokenId::kw_star);
        }
    }break;
    case '+': {
        if ('+' == m_peek) {
            tok = genToken(TokenId::kw_plusplus);
            m_peek = _Readch();
        }
        else if ('=' == m_peek) {
            tok = genToken(TokenId::kw_plusequal);
            m_peek = _Readch();
        }
        else {
            tok = genToken(TokenId::kw_plus);
        }
    }break;
    case '-': {
        if ('>' == m_peek) {
            m_peek = _Readch();
            tok = genToken(TokenId::kw_arrow);
        }
        else if ('-' == m_peek) {
            m_peek = _Readch();
            tok = genToken(TokenId::kw_minusminus);
        }
        else if ('=' == m_peek) {
            m_peek = _Readch();
            tok = genToken(TokenId::kw_minusequal);
        }
        else {
            tok = genToken(TokenId::kw_minus);
        }
    }break;
    case '~': {
        tok = genToken(TokenId::kw_tilde);
    }break;
    case '!': {
        if ('=' == m_peek) {
            m_peek = _Readch();
            tok = genToken(TokenId::kw_exclaimequal);
        }
        else {
            tok = genToken(TokenId::kw_exclaim);
        }
    }break;
    case '/': { ///  ���ﻹ��Ҫ����ע��
        if ('=' == m_peek) {
            m_peek = _Readch();
            tok = genToken(TokenId::kw_slashequal);
        }
        else {
            tok = genToken(TokenId::kw_slash);
        }
    }break;
    case '%': {
        if ('=' == m_peek) {
            m_peek = _Readch();
            tok = genToken(TokenId::kw_percentequal);
        }
        else {
            tok = genToken(TokenId::kw_percent);
        }
    }break;
    case '<': {
        if ('<' == m_peek) {
            m_peek = _Readch();
            if ('=' == m_peek) {
                m_peek = _Readch();
                tok = genToken(TokenId::kw_lessless);
            }
            else {
                tok = genToken(TokenId::kw_lessless);
            }
        }
        else if ('=' == m_peek) {
            m_peek = _Readch();
            if ('>' == m_peek) {
                m_peek = _Readch();
                tok = genToken(TokenId::kw_spaceship);
            }
            else {
                tok = genToken(TokenId::kw_lessequal);
            }

        }
        else {
            tok = genToken(TokenId::kw_less);
        }
    }break;
    case '>': {
        if ('>' == m_peek) {
            m_peek = _Readch();
            if ('=' == m_peek) {
                m_peek = _Readch();
                tok = genToken(TokenId::kw_greatergreaterequal);
            }
            else {
                tok = genToken(TokenId::kw_greatergreater);
            }
        }
        else if ('=' == m_peek) {
            m_peek = _Readch();
            tok = genToken(TokenId::kw_greaterequal);
        }
        else {
            tok = genToken(TokenId::kw_greater);
        }
    }break;
    case '^': {
        if ('=' == m_peek) {
            m_peek = _Readch();
            tok = genToken(TokenId::kw_caretequal);
        }
        else {
            tok = genToken(TokenId::kw_caret);
        }
    }break;
    case '|':{
        if ('|' == m_peek) {
            m_peek = _Readch();
            tok = genToken(TokenId::kw_pipepipe);
        }
        else if ('=' == m_peek) {
            m_peek = _Readch();
            tok = genToken(TokenId::kw_pipeequal);
        }
        else {
            tok = genToken(TokenId::kw_pipe);
        }
    }break;
    case '?': {
        tok = genToken(TokenId::kw_question);
    }break;
    case ':': {
        if (':' == m_peek) {
            m_peek = _Readch();
            tok = genToken(TokenId::kw_coloncolon);
        }
        else {
            tok = genToken(TokenId::kw_colon);
        }
    }break;
    case ';': {
        tok = genToken(TokenId::kw_semi);
    }break;
    case '=': {
        if ('=' == m_peek) {
            m_peek = _Readch();
            tok = genToken(TokenId::kw_equalequal);
        }
        else {
            tok = genToken(TokenId::kw_equal);
        }
    }break;
    case ',': {
        tok = genToken(TokenId::kw_comma);
    }break;
    case '#': {
        if ('#' == m_peek) {
            m_peek = _Readch();
            tok = genToken(TokenId::kw_hashhash);
        }
        else if('@' == m_peek){
            m_peek = _Readch();
            tok = genToken(TokenId::kw_hashat);
        }
        else {
            tok = genToken(TokenId::kw_hash);
        }
    }break;
    default: {
        tok = genToken(TokenId::kw_Unknown);
    }break;
    }
    return tok;
}

