#include "TestRuleOnCode.h"
#include "rules/custom/PartOfConditionIsConstantValueRule.cpp"

TEST(PartOfConditionIsConstantValueRuleTest, PropertyTest)
{
    PartOfConditionIsConstantValueRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("part of condition is constant value", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(PartOfConditionIsConstantValueRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new PartOfConditionIsConstantValueRule(), "void m(){int a;bool b; int c[10];if(!(a)&&b||(c[0])){}}");
}

TEST(PartOfConditionIsConstantValueRuleTest, Test1)
{
         
    testRuleOnCXXCode(new PartOfConditionIsConstantValueRule(),                     
                      "void m(){int a;bool b; int c[10];if(!(a)&&b||(c[0]&&\n0x04)){}}",
            0, 2, 1, 2, 1, "A part of conditional expression is always true: 0x04.");
}

