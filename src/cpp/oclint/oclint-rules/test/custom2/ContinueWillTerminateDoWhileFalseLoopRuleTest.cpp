#include "TestRuleOnCode.h"
#include "rules/custom2/ContinueWillTerminateDoWhileFalseLoopRule.cpp"

TEST(ContinueWillTerminateDoWhileFalseLoopRuleTest, PropertyTest)
{
    ContinueWillTerminateDoWhileFalseLoopRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("continue will terminate do while false loop", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(ContinueWillTerminateDoWhileFalseLoopRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new ContinueWillTerminateDoWhileFalseLoopRule(), 
            "void m(){int a;do{}while(true);}");
}

TEST(ContinueWillTerminateDoWhileFalseLoopRuleTest, Test1)
{
         
    testRuleOnCXXCode(new ContinueWillTerminateDoWhileFalseLoopRule(), 
            "void m(){\n"
            "int a;\ndo{}while(false);}",0, 3, 11, 3, 11, "The 'continue' operator will terminate 'do { ... } while (FALSE)' loop because the condition is always false.");
}
