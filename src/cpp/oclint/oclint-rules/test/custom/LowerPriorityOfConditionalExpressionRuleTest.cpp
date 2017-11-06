#include "TestRuleOnCode.h"
#include "rules/custom/LowerPriorityOfConditionalExpressionRule.cpp"

TEST(LowerPriorityOfConditionalExpressionRuleTest, PropertyTest)
{
    LowerPriorityOfConditionalExpressionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("lower priority of conditional expression", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(LowerPriorityOfConditionalExpressionRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new LowerPriorityOfConditionalExpressionRule(), "void m(){int a,b,c;a=a?a:b;}");
    testRuleOnCXXCode(new LowerPriorityOfConditionalExpressionRule(), "void m(){int a=0,b,c;a=(a-b)?a:b;}");
}

TEST(LowerPriorityOfConditionalExpressionRuleTest, Test1)
{
         
    testRuleOnCXXCode(new LowerPriorityOfConditionalExpressionRule(), "void m(){int a,b;a=a-b?a:b;}",
            0, 1, 20, 1, 26, 
                      "Perhaps the '?:' operator works in a different way than it was expected.The '?:' operator has a lower priority than the '-' operator.");
}

TEST(LowerPriorityOfConditionalExpressionRuleTest, Test2) 
{

    testRuleOnCXXCode(new LowerPriorityOfConditionalExpressionRule(), 
            "void m(){int a,b,c;a=a|b?a:b;}",
            0, 1, 22, 1, 28, 
                     "Perhaps the '?:' operator works in a different way than it was expected.The '?:' operator has a lower priority than the '|' operator.");
    
}

TEST(LowerPriorityOfConditionalExpressionRuleTest, Test3) 
{

    testRuleOnCXXCode(new LowerPriorityOfConditionalExpressionRule(), 
            "void m(){int a,b;a=a&&b?a:b;}",
            0, 1, 20, 1, 27,
                     "Perhaps the '?:' operator works in a different way than it was expected.The '?:' operator has a lower priority than the '&&' operator.");
    
}

TEST(LowerPriorityOfConditionalExpressionRuleTest, Test4) 
{

    testRuleOnCXXCode(new LowerPriorityOfConditionalExpressionRule(), 
            "void foo(){int a,b,c;a>=b?a:b;}",
            0, 1, 22, 1, 29,
                     "Perhaps the '?:' operator works in a different way than it was expected.The '?:' operator has a lower priority than the '>=' operator.");
    
}
