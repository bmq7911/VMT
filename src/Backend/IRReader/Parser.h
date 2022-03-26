#pragma once
#include "Backend/IRReader/Lexer.h"
#include <memory>
#include <string_view>
#include <functional>

#include "Backend/IR/Module.h"
#include "Backend/IR/IRContext.h"

#include "Backend/IRReader/ErrorDiagnose.h"

namespace IR {
	/* 
	* this comment discript the IR assembly langurage format
	* file ::= source_file functions attributes
	* source_flie ::= "source_filename" "=" file_name
	* file_name ::= """ ([a-z]|[A-Z]| _){[a-z]|[A-Z]|[0-9]|_ "." postfix """
	* functions ::= "{" function "}"
	*/
	
	/// <summary>
	/// 这段代码还是自己手写的好
	/// </summary>
	class IRReaderParser {
	public:
		IRReaderParser(std::shared_ptr<IR::IRReaderLexer> lexer ) 
			: m_lexer( lexer )
		{
			m_context = std::make_shared<IR::IRContext>( );
		}
		std::shared_ptr<IR::Module> parseModule() {

		}
		/// 递归下降的过程
		std::shared_ptr<IR::Function> praseFunction() {
			auto func = _ParseFunctionTypeAndName();
			if (!func) {
				return nullptr;
			}

			_ParseInstruction( );

		}

	private:

		std::shared_ptr<IR::Function> _ParseFunctionTypeAndName( ){
			Type* func_return_type;
			std::vector<Type*> params_type;
			std::string_view   function_name;
			std::vector<std::string_view> function_params_name;

			std::shared_ptr<IR::FunctionType> func_type;
			auto tok = m_lexer->scan();
			if (tok.getTokenId() == IRReaderLexer::TokenId::kKeyWord) {
				if (tok.getStringView().compare("define")) {
					m_errorDiagnose->expectBut("define", tok.getStringView());
					return nullptr;
				}
			}
			else { ///1. 不时keyword
				/// <summary>
				m_errorDiagnose->expectBut("a key word:define", IRReaderLexer::getTokenIdString( tok.getTokenId() ));
				return nullptr;
			}
			tok = m_lexer->scan();
			if (tok.getTokenId() == IR::IRReaderLexer::TokenId::kKeyWord) {
				/// 是一个类型关键字
				func_return_type = _ParseType( tok.getStringView());
			}
			else {
				return nullptr;
			}

			tok = m_lexer->scan();
			if (tok.getTokenId() == IR::IRReaderLexer::TokenId::kGrobalId ||
				tok.getTokenId() == IR::IRReaderLexer::TokenId::kLocalId) {
				function_name = tok.getStringView( );
			}
			else {
				return nullptr;
			}
			tok = m_lexer->scan();
			if (tok.getTokenId() == IR::IRReaderLexer::TokenId::kLeft_paren) {
			
			}
			/// 开始处理参数了
			tok = m_lexer->scan();

			/// param_list ::=  empty | params
			/// params     ::= param | param, parmas 
			/// param      ::= KeyWord Local_id
			//1. 处理 param_list 为空的情况
			if (tok.getTokenId() == IR::IRReaderLexer::TokenId::kRight_paren) {
			
			}
			else {
			/// 2.处理param_list 为 params时的情况
				do {
					if (tok.getTokenId() != IR::IRReaderLexer::TokenId::kKeyWord) {
						//m_errorDiagnose->expectBut();
						return nullptr;
					}
					Type* type = _ParseType(tok.getStringView());
					if (nullptr == type) {

						return nullptr;
					}
					params_type.push_back(type);
					tok = m_lexer->scan();
					if (tok.getTokenId() != IR::IRReaderLexer::TokenId::kLocalId) {
						
						return nullptr;
					}
					function_params_name.push_back(tok.getStringView());
					tok = m_lexer->scan( );
					if (tok.getTokenId() == IR::IRReaderLexer::TokenId::kComma) {
						tok = m_lexer->scan();
					}
					else if (tok.getTokenId() == IR::IRReaderLexer::TokenId::kRight_paren) {
						break;
					}
					else {
						/// 出错

					}
				} while ( true);
			}
			/// 参数处理
			tok = m_lexer->scan( );
			if (tok.getTokenId() == IR::IRReaderLexer::kAttribute) {
				std::string_view attribute = tok.getStringView( );
				tok = m_lexer->scan();
			}

			if (tok.getTokenId() == IR::IRReaderLexer::kLeft_brace) {
			
			}
			else {
				return nullptr;
			}
			/// 
			/// 生成函数类型和函数列表

		}
		bool _ParseInstruction() {
			do {
				auto tok = m_lexer->scan();
				auto view = tok.getStringView();
				if (tok.getTokenId() == IR::IRReaderLexer::kGrobalId ||
					tok.getTokenId() == IR::IRReaderLexer::kLocalId) {
					/// 这里就有可能时赋值操作
					_ParseInstruction(tok);
				}
				/// 这里是处理指令过程,如br, store 等过程
				else if (tok.getTokenId() == IR::IRReaderLexer::kKeyWord) {
					_DispatchParseInstruction(tok);
				}
				/// 这里处理Label相关
				else if (tok.getTokenId() == IR::IRReaderLexer::kLabel) {

				}
				/// 这里处理其他就应该是错误的问题了
				else {

				}

			} while (true);
		}
	private:



	private:
		Type* _ParseType( std::string_view const& view  ) {
			auto TypeManger = m_context->getTypeManger();
			return TypeManger.getTypeFromName(view);
		}
		
		void _ParseInstrution( ) {
			
		}
		void _DispatchParseInstruction(IR::IRReaderLexer::Token& opTok) {
			auto op = IR::Instruction::getOpCode( opTok.getStringView());
			/// 1.处理错误指令
			if (op == IR::Instruction::kError) {
				
			}
			if (IR::Instruction::isBinaryOp(op)) {
				auto tok = m_lexer->scan( );
				if (IR::IRReaderLexer::kEqual != tok.getTokenId()) {
					return ;
				}
				else {
					tok = m_lexer->scan( );
					if ( IR::IRReaderLexer::kKeyWord != tok.getTokenId( ) ) {
						return;
					}
					auto type = _ParseType(tok.getStringView( ));
					if (nullptr == type) {
						return;
					}
					tok = m_lexer->scan( );
					if (IR::IRReaderLexer::kKeyWord != tok.getTokenId()) {
						return;
					}
					std::string_view v1 = tok.getStringView( );

					tok = m_lexer->scan();
					if (IR::IRReaderLexer::kComma != tok.getTokenId()) {
						return;
					}
					tok = m_lexer
				}
			}
			else if (IR::Instruction::isUnaryOp(op)) {
			
			}
			else { /// 处理复杂指令
			
			}
		}
		void _ParseInstruction(IR::IRReaderLexer::Token& tok) {
			auto view = tok.getStringView();
		}

		
	private:
		std::shared_ptr<IR::ErrorDiagnose> m_errorDiagnose;
		std::shared_ptr<IR::IRContext> m_context;
		std::shared_ptr<IRReaderLexer> m_lexer;
		std::map<std::string_view,IR::Value*>   m_variableMaps;
	};
}