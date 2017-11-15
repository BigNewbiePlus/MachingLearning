#include "TestRuleOnCode.h"
#include "rules/custom2/ExcessiveConditionExpressionRule.cpp"

TEST(ExcessiveConditionExpressionRuleTest, PropertyTest)
{
    ExcessiveConditionExpressionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("excessive condition expression", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(ExcessiveConditionExpressionRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new ExcessiveConditionExpressionRule(),
            "void m(){int a, b, c; if(a!=1&&a!=10){}}");
    testRuleOnCXXCode(new ExcessiveConditionExpressionRule(), 
            "void m(){int a, b; if(a==10&&b!=10){}}");
    testRuleOnCXXCode(new ExcessiveConditionExpressionRule(), 
            "void m(){int a, b; if(a==10||a!=10){}}");
}

TEST(ExcessiveConditionExpressionRuleTest, Test1)
{
         
    testRuleOnCXXCode(new ExcessiveConditionExpressionRule(), 
            "void m(){int a,b,c;a=b;\nif(a==10&&a!=5){};}"
           ,0, 2, 4, 2, 14, "Consider inspecting the 'a==10&&a!=5' expression. The expression is excessive or contains a misprint.");
}

