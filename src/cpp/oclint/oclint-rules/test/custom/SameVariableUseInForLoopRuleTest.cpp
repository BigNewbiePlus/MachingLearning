#include "TestRuleOnCode.h"
#include "rules/custom/SameVariableUseInForLoopRule.cpp"

TEST(SameVariableUseInForLoopRuleTest, PropertyTest)
{
    SameVariableUseInForLoopRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("same variable use in for loop", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(SameVariableUseInForLoopRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new SameVariableUseInForLoopRule(), "void m(){for(int i=0;i<10;i++)for(int j=0;i<10;i++){}}");
}

TEST(SameVariableUseInForLoopRuleTest, Test1)
{
         
    testRuleOnCode(new SameVariableUseInForLoopRule(),                     
                      "void m(){for(int i=0;i<10;i++)for(\ni=0;i<10;\ni++){}}",
            0, 2, 1, 2, 3, "The variable 'i' is being used for this loop and for the outer loop.");
}
