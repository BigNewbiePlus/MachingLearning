#include "TestRuleOnCode.h"
#include "rules/custom2/UnconditionalBreakWithinALoopRule.cpp"

TEST(UnconditionalBreakWithinALoopRuleTest, PropertyTest)
{
    UnconditionalBreakWithinALoopRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("unconditional break within a loop", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(UnconditionalBreakWithinALoopRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new UnconditionalBreakWithinALoopRule(), 
            "void m(){for(int i=0;i<10;i++){if(i==0){break;}}}");
}

TEST(UnconditionalBreakWithinALoopRuleTest, Test1)
{
         
    testRuleOnCXXCode(new UnconditionalBreakWithinALoopRule(), 
            "void m(){\n"
            "for(int i=0;i<10;i++){if(i==0)return; \nbreak;}}",0, 3, 1, 3, 1, "An unconditional 'break' within a loop.");
}

TEST(UnconditionalBreakWithinALoopRuleTest, Test2)
{
         
    testRuleOnCXXCode(new UnconditionalBreakWithinALoopRule(), 
            "void m(){\n"
            "int cnt=10;while(cnt-->0){\ncontinue;}}",0, 3, 1, 3, 1, "An unconditional 'continue' within a loop.");
}

