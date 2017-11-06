#include "TestRuleOnCode.h"
#include "rules/custom/CompareBoolWithIntRule.cpp"

TEST(CompareBoolWithIntRuleTest, PropertyTest)
{
    CompareBoolWithIntRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("compare bool with int", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(CompareBoolWithIntRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new CompareBoolWithIntRule(), "void m(){bool a; int b;if(a>b){}}");
}

TEST(CompareBoolWithIntRuleTest, Test1)
{
    testRuleOnCXXCode(new CompareBoolWithIntRule(),                     
                      "void m(){bool a;if(\na>10){}}",
            0, 2, 1, 2, 3, "It's odd to compare a bool type value with a value of 10: a>10.");
}

TEST(CompareBoolWithIntRuleTest, Test2)
{
    testRuleOnCXXCode(new CompareBoolWithIntRule(),                     
                      "void m(){bool a;if(\na>-1){}}",
            0, 2, 1, 2, 4, "It's odd to compare a bool type value with a value of -1: a>-1.");
}
