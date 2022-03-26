#include <stdio.h>
#include <iostream>
#include <stack>
#include "gtest/gtest.h"
#include "Backend/IRReader/Lexer.h"
#include "Backend/IRReader/Parser.h"


TEST(test_ir_reader_lexer, ir_reader_lexer) {
    const char* strSRC =    "define @fun(i32 %0, i32 %1, i32 %2) #0{\n"
                            "          %add = add i32 %0, i32 %1;this is a commnet\r"
                            "}";

    IR::IRReaderLexer lexer(strSRC);

    IR::IRReaderLexer::Token tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ( tok.getTokenId(), IR::IRReaderLexer::TokenId::kKeyWord );
    tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kGrobalId);
 
    tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kLeft_paren );
 
    tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kKeyWord );
    
    tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kLocalId);
    
    tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kComma);

    tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kKeyWord);

    tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kLocalId);


    tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kComma);

    tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kKeyWord);

    tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kLocalId );
 
    tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kRight_paren );

    tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kAttribute );


    tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kLeft_brace );

    tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kLocalId);


    tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kEqual );

    tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kKeyWord);

     tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kKeyWord);

     tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kLocalId);

    
     tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kComma);


     tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kKeyWord);

    
     tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kLocalId);

     tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kRight_brace);

     tok = lexer.scan();
    std::cout << tok.to_string() << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kEof);

    


}



TEST(test_ir_reader_lexer_link, ir_reader_lexer) {
    const char* strSRC = "\r\ndefine  @fun@123(i32%0,i32%1,i32%2)#0{\n"
        "%add = add i32%0@123,i32%1;this is a commnet\r"
        "\"hello world\"\r"
        "}";

    IR::IRReaderLexer lexer(strSRC);

    IR::IRReaderLexer::Token tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kKeyWord);
    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kGrobalId);

    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kLeft_paren);

    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kKeyWord);

    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kLocalId);

    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kComma);

    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kKeyWord);

    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kLocalId);


    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kComma);

    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kKeyWord);

    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kLocalId);

    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kRight_paren);

    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kAttribute);


    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kLeft_brace);

    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kLocalId);


    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kEqual);

    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kKeyWord);

    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kKeyWord);

    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kLocalId);


    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kComma);


    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kKeyWord);


    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kLocalId);

   
    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kString );
 
    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kRight_brace);
    

    tok = lexer.scan();
    std::cout << tok.to_string() <<"\t ["<< tok.get_location().first <<", "<< tok.get_location().second<<" ]" << std::endl;
    EXPECT_EQ(tok.getTokenId(), IR::IRReaderLexer::TokenId::kEof);




}

TEST(test_ir_reader_parser, ir_reader_lexer) {
    const char* strSRC = "\r\ndefine i32 @fun@123(i32%0,i32%1,i32%2)#0{\n"
        "%add = add i32%0@123,i32%1;this is a commnet\r"
        "\"hello world\"\r"
        "}";

    std::shared_ptr<IR::IRReaderLexer> lexer = std::make_shared<IR::IRReaderLexer>(strSRC);

    IR::IRReaderParser parser( lexer);
    parser.praseFunction();

}



int main( int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS( );
	
}
