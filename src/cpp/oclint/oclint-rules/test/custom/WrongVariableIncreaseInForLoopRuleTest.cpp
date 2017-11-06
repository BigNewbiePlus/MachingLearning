#include "TestRuleOnCode.h"
#include "rules/custom/WrongVariableIncreaseInForLoopRule.cpp"

TEST(WrongVariableIncreaseInForLoopRuleTest, PropertyTest)
{
    WrongVariableIncreaseInForLoopRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("wrong variable increase in for loop", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(WrongVariableIncreaseInForLoopRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new WrongVariableIncreaseInForLoopRule(), "void m(){for(int i=0;i<10;i++)for(int j=0;j<i;j++){}}");
}

TEST(WrongVariableIncreaseInForLoopRuleTest, Test1)
{
         
    testRuleOnCode(new WrongVariableIncreaseInForLoopRule(),                     
                      "void m(){for(int i=0;i<10;i++)for(int j=0;j<i;\ni++){}}",
            0, 2, 1, 2, 2, "It is likely that a wrong variable is being incremented inside the 'for' operator. Consider reviewing 'i'.");
}
