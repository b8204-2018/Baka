#include "opz.h"
#include <gtest\gtest.h>
TEST(Parser,parse_is_working){
    string s="( 2 + 5 ) /  7";
    ExpressionParser n ;
    list<string> result=n.parse(s);
    string result2="";
    for (string x : result) {result2+=x;}
    EXPECT_EQ(result2,"25+7/");
}
TEST(Parser,parser_throw_exeptions){
    string s = "( 2 ++ 5 ) /  7";
    ExpressionParser n;
    ASSERT_THROW(n.parse(s),logic_error);
}
TEST(Calc,calc_is_working){
    string s = "( 2 + 5*2 ) /  12";
    Calculator c;
    ExpressionParser n ;
    list<string> result=n.parse(s);
    double result1=c.calc(result);
    EXPECT_EQ(result1,1);
}