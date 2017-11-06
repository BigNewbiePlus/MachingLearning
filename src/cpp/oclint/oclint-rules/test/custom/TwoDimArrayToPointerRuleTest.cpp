#include "TestRuleOnCode.h"
#include "rules/custom/TwoDimArrayToPointerRule.cpp"

TEST(TwoDimArrayToPointerRuleTest, PropertyTest)
{
    TwoDimArrayToPointerRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("two dim array to pointer", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(TwoDimArrayToPointerRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new TwoDimArrayToPointerRule(), "void m(){int** a; char** p = (char**)a;}");
}

TEST(TwoDimArrayToPointerRuleTest, Test1)
{
         
    testRuleOnCode(new TwoDimArrayToPointerRule(),                     
                      "void m(){int a[10][10]; int** p = \n(int**)a;}",
            0, 2, 1, 2, 8, "Consider reviewing type casting. TYPE X[][] in not equivalent to TYPE **X.");
}
