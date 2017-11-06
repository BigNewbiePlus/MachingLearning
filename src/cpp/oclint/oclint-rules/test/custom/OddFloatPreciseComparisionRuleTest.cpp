#include "TestRuleOnCode.h"
#include "rules/custom/OddFloatPreciseComparisionRule.cpp"

TEST(OddFloatPreciseComparisionRuleTest, PropertyTest)
{
    OddFloatPreciseComparisionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("odd float precise comparision", rule.name());
    EXPECT_EQ("custom", rule.category());
}


TEST(OddFloatPreciseComparisionRuleTest, NoViolationInstance)    
{
    testRuleOnCode(new OddFloatPreciseComparisionRule(), "void m(){int a; if(a==1){}}");
    testRuleOnCode(new OddFloatPreciseComparisionRule(), "void m(){float a; if(a>1){}}");
}

TEST(OddFloatPreciseComparisionRuleTest, Test1)
{       
    testRuleOnCode(new OddFloatPreciseComparisionRule(),                     
                      "void m(){float a; if(\na==1){}}",
            0, 2, 1, 2, 4, 
                   "An odd precise comparison: a==1. It's probably better to use a comparison with defined precision: fabs(A - B) '<' Epsilon.");
}

TEST(OddFloatPreciseComparisionRuleTest, Test2)
{       
    testRuleOnCode(new OddFloatPreciseComparisionRule(),                     
                      "void m(){double a; if(\na != 1){}}",
            0, 2, 1, 2, 6, 
                   "An odd precise comparison: a != 1. It's probably better to use a comparison with defined precision: fabs(A - B) '<' Epsilon.");
}

TEST(OddFloatPreciseComparisionRuleTest, Test3)
{       
    testRuleOnCode(new OddFloatPreciseComparisionRule(),                     
                      "void m(){double a, b; if(\na != b){}}",
            0, 2, 1, 2, 6, 
                   "An odd precise comparison: a != b. It's probably better to use a comparison with defined precision: fabs(A - B) '<' Epsilon.");
}
