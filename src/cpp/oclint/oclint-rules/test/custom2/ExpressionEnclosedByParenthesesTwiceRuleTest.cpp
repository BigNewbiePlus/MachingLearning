#include "TestRuleOnCode.h"
#include "rules/custom2/ExpressionEnclosedByParenthesesTwiceRule.cpp"

TEST(ExpressionEnclosedByParenthesesTwiceRuleTest, PropertyTest)
{
    ExpressionEnclosedByParenthesesTwiceRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("expression enclosed by parentheses twice", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(ExpressionEnclosedByParenthesesTwiceRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new ExpressionEnclosedByParenthesesTwiceRule(), 
            "void m(){int a,b;if((a>b)){}}");
}

TEST(ExpressionEnclosedByParenthesesTwiceRuleTest, Test1)
{
         
    testRuleOnCXXCode(new ExpressionEnclosedByParenthesesTwiceRule(), 
            "void m(){\n"
            "int a,b;\nif(((a>b&&a<10))){}}",0, 3, 4, 3, 16, "The expression was enclosed by parentheses twice: ((expression)). One pair of parentheses is unnecessary or misprint is present.");
}

TEST(ExpressionEnclosedByParenthesesTwiceRuleTest, Test2)
{
         
    testRuleOnCXXCode(new ExpressionEnclosedByParenthesesTwiceRule(), 
            "void m(){\n"
            "int a; \nint b=a*((10*b));}",0, 3, 9, 3, 16, "The expression was enclosed by parentheses twice: ((expression)). One pair of parentheses is unnecessary or misprint is present.");
}

