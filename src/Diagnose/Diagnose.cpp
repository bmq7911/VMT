#include "Diagnose/Diagnose.h"
#include <iostream>
void Diagnose::expectBut( TokenId expect, Token but){
	std::cout << "at["<< but.getLocation().row()<<"," << but.getLocation().col()<<"] expect "
		       << toTokenIdString(expect) <<" but give \""<<  but.toStringView()<<"\"" << std::endl;
}

void Diagnose::expectBut( TokenId expect, TokenId but){

	std::cout << "expect "
		       << toTokenIdString(expect) <<" but give "<< toTokenIdString(but) << std::endl;

}
void Diagnose::errorMsg(const char* msg) {
	std::cout << msg <<std::endl;
}
void Diagnose::errorMsg(const char* msg, const char* expect) {
	std::cout << msg << " " << expect << std::endl;
}

void Diagnose::errorMsg(const char* msg, std::string_view const& expect) {
	std::cout << msg << " " << expect << std::endl;
}
