#include "TestRuleOnCode.h"
#include "rules/custom2/CreateSameLocalVariableAsControlVariableWithinLoopRule.cpp"

TEST(CreateSameLocalVariableAsControlVariableWithinLoopRuleTest, PropertyTest)
{
    CreateSameLocalVariableAsControlVariableWithinLoopRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("create same local variable as control variable within loop", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(CreateSameLocalVariableAsControlVariableWithinLoopRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new CreateSameLocalVariableAsControlVariableWithinLoopRule(), 
            "void m(){int a,b,c;while(a>0){a++;}{}}");
}

TEST(CreateSameLocalVariableAsControlVariableWithinLoopRuleTest, Test1)
{
         
    testRuleOnCXXCode(new CreateSameLocalVariableAsControlVariableWithinLoopRule(), 
            "void m(){int a,b; \nwhile(a>0){int a;}}",0, 2, 1, 2, 18, "It is dangerous to create a local variable within a loop with a same name as a variable controlling this loop.");
}
