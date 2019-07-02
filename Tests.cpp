#include "opz.h"
#include "gtest/gtest.h"

TEST(Parser, parse_is_working) {
string s = "( 2 + 4 ) /  6";
ExpressionParser n;
list<string> result = n.parse(s);
string result2 = "";
for (string x : result) { result2 += x; }
EXPECT_EQ(result2, "24+6/");
}

TEST(Parser, parser_throw_exeptions) {
string s = "( 3 ~~ 6 ) /  8";
ExpressionParser n;
ASSERT_THROW(n.parse(s), logic_error);
}

TEST(Parser, parser_throw_exeptions_minus) {
string s = "( 1 +- 3 ) /  8";
ExpressionParser n;
ASSERT_THROW(n.parse(s), logic_error);
}

TEST(Parser, parser_mismatched_brackets) {
string s = "( 9 ~ 3 /  6";
ExpressionParser n;
ASSERT_THROW(n.parse(s), logic_error);
}

TEST(Parser, parser_back_mismatched_brackets) {
string s = "1 + 3 ) /  8";
ExpressionParser n;
ASSERT_THROW(n.parse(s), logic_error);
}

TEST(Calc, calc_is_working) {
string s = "( 2 + 2 ) /  4";
Calculator c;
ExpressionParser n;
list<string> result = n.parse(s);
double result1 = 0;
result1 = c.calc(result);
EXPECT_EQ(result1, 1.0);
}