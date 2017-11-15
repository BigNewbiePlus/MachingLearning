#include "TestRuleOnCode.h"
#include "rules/custom2/OddOperatorOfEqualPlusRule.cpp"

TEST(OddOperatorOfEqualPlusRuleTest, PropertyTest)
{
    OddOperatorOfEqualPlusRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("odd operator of equal plus", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(OddOperatorOfEqualPlusRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new OddOperatorOfEqualPlusRule(),
            "void m(){int a, b, c; a+=b;b=c;}");
    testRuleOnCXXCode(new OddOperatorOfEqualPlusRule(), 
            "void m(){int a, b; a=-b;a=10;b*=a;}");
}

TEST(OddOperatorOfEqualPlusRuleTest, Test1)
{
         
    testRuleOnCXXCode(new OddOperatorOfEqualPlusRule(), 
            "void m(){int a,b,c;a=b;\nb=+a;}"
           ,0, 2, 1, 2, 4, "The expression of the 'A =+ B' kind is utilized. Consider reviewing it, as it is possible that 'A += B' was meant.");
}

