#include "TestRuleOnCode.h"
#include "rules/custom2/CommaMissingInIntArrayInitRule.cpp"

TEST(CommaMissingInIntArrayInitRuleTest, PropertyTest)
{
    CommaMissingInIntArrayInitRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("comma missing in int array init", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(CommaMissingInIntArrayInitRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new CommaMissingInIntArrayInitRule(), 
            "void m(){int a[3]={1,2,3};}");
}

TEST(CommaMissingInIntArrayInitRuleTest, Test1)
{
         
    testRuleOnCXXCode(new CommaMissingInIntArrayInitRule(), 
            "void m(){\n"
            "int a[3]={1,2 -3};}",0, 2, 1, 2, 17, "It is possible that ',' comma is missing at the end of the string.");
}
