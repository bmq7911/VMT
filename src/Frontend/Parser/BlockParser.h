#pragma once
#include "Frontend/Parser/ParserProxy.h"

class BlockParser : public ParserProxy {
public:
    //void block() {
    //    match(Tag::kw_l_brace);
    //    AST::Expr* expr = this->expr( );
    //    match(Tag::kw_r_brace);
    //    expr->emit(expr->gen()->toString());
    //}
    //    
    ///// ������ȷ�Ľ��ȴ�Ǵ����,����ԭ�����û����ƺý���Ե����
    //AST::Expr* expr() {
    //    AST::Expr* term = this->term( );
    //    Token tok = getToken();

    //    /// �����߼������������Ϲ����ڵ�,�����ܱ�֤��������,��֤������,ԭ���Ƿŵ��˵�ǰ�ڵ�����ӽڵ�
    //    while (tok.match(Tag::kw_plus) || tok.match(Tag::kw_minus)) {
    //        move();
    //        AST::Expr *term1 = this->term();
    //        term = new AST::Arith(tok, term,term1); /// �������ǿ���ʵ���ҽ��
    //        tok = getToken( );
    //    }
    //    return term;
    //}

    //AST::Expr* term() {
    //    AST::Expr* factor = this->factor();
    //    Token tok = getToken();
    //    while (tok.match(Tag::kw_star) || tok.match(Tag::kw_slash)) {
    //        move();
    //        AST::Expr* factor1 = this->factor();
    //        factor = new AST::Arith(tok, factor, factor1);
    //        tok = getToken();
    //    
    //    }
    //    return factor;
    //}

    //AST::Expr* factor() {
    //    Token tok = getToken();
    //    if (tok.match(Tag::kw_l_paren)) {
    //        move();
    //        AST::Expr * expr = this->expr();
    //        match(Tag::kw_r_paren);
    //        return expr;
    //    }
    //    else if( tok.match(Tag::id)){
    //        move();
    //        AST::Id* id = new AST::Id( tok, &Type::UI8, 2);
    //        return id;
    //    }
    //}

};