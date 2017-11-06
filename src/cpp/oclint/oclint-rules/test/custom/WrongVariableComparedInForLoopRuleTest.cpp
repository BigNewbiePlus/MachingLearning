#include "TestRuleOnCode.h"
#include "rules/custom/WrongVariableComparedInForLoopRule.cpp"

TEST(WrongVariableComparedInForLoopRuleTest, PropertyTest)
{
    WrongVariableComparedInForLoopRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("wrong variable compared in for loop", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(WrongVariableComparedInForLoopRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new WrongVariableComparedInForLoopRule(), "void m(){for(int i=0;i<10;i++)for(int j=0;j<i;j++){}}");
}

TEST(WrongVariableComparedInForLoopRuleTest, Test1)
{     
    testRuleOnCode(new WrongVariableComparedInForLoopRule(),                     
                      "void m(){for(int i=0;i<10;i++)for(int j=0;\ni<10;i++){}}",
            0, 2, 1, 2, 3, "It is likely that a wrong variable is being compared inside the 'for' operator. Consider reviewing 'i'.");
}
