#include "TestRuleOnCode.h"
#include "rules/custom2/OwnerlessTokenRule.cpp"

TEST(OwnerlessTokenRuleTest, PropertyTest)
{
    OwnerlessTokenRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("ownerless token", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(OwnerlessTokenRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new OwnerlessTokenRule(), 
            "void m(){int a,b;a;}");
    testRuleOnCXXCode(new OwnerlessTokenRule(), 
            "void m(){int a[10], b[10];if(a!=b){}}");
}

TEST(OwnerlessTokenRuleTest, Test1)
{
         
    testRuleOnCXXCode(new OwnerlessTokenRule(), 
            "void m(){\n"
            "int a[10];\nfalse;}",0, 3, 1, 3, 1, "Ownerless token 'false'.");
}

TEST(OwnerlessTokenRuleTest, Test2)
{
         
    testRuleOnCXXCode(new OwnerlessTokenRule(), 
            "void m(){\n"
            "char ab[10];\ntrue;}",0, 3, 1, 3, 1, "Ownerless token 'true'.");
}

