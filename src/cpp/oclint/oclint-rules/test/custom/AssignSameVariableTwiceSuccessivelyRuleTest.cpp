#include "TestRuleOnCode.h"
#include "rules/custom/AssignSameVariableTwiceSuccessivelyRule.cpp"

TEST(AssignSameVariableTwiceSuccessivelyRuleTest, PropertyTest)
{
    AssignSameVariableTwiceSuccessivelyRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("assign same variable twice successively", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(AssignSameVariableTwiceSuccessivelyRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new AssignSameVariableTwiceSuccessivelyRule(), "void m(){int a,b,c;a=1;b=2;c=3;}");
}

TEST(AssignSameVariableTwiceSuccessivelyRuleTest, Test1)
{
         
    testRuleOnCode(new AssignSameVariableTwiceSuccessivelyRule(),                     
                      "void foo(){for(int i=0;i<10;i++){int aa,b;\naa=1;aa=2;}}",
            0, 2, 1, 2, 1, "The 'aa' object is assigned values twice successively. Perhaps this is a mistake.");
}

TEST(AssignSameVariableTwiceSuccessivelyRuleTest, Test2)
{
         
    testRuleOnCode(new AssignSameVariableTwiceSuccessivelyRule(),                     
                      "void foo(){int aa,b;\naa=1;aa=2;}",
            0, 2, 1, 2, 1, "The 'aa' object is assigned values twice successively. Perhaps this is a mistake.");
}
