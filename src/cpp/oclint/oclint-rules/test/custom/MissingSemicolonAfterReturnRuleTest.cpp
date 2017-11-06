#include "TestRuleOnCode.h"
#include "rules/custom/MissingSemicolonAfterReturnRule.cpp"

TEST(MissingSemicolonAfterReturnRuleTest, PropertyTest)
{
    MissingSemicolonAfterReturnRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("missing semicolon after return", rule.name());
    EXPECT_EQ("custom", rule.category());
}


TEST(MissingSemicolonAfterReturnRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new MissingSemicolonAfterReturnRule(), "void m(){int a;if(a==0){return \n;}}");
    testRuleOnCXXCode(new MissingSemicolonAfterReturnRule(), "void m(){int a;if(a!=0)return;}");
    testRuleOnCXXCode(new MissingSemicolonAfterReturnRule(), "void m(){int a;return;}");
}

TEST(MissingSemicolonAfterReturnRuleTest, Test1)
{
         
    testRuleOnCXXCode(new MissingSemicolonAfterReturnRule(), "int m(){int a;if(a>0)return\na;}",
            0, 1, 22, 2, 1, "It is highly probable that the semicolon ';' is missing after 'return' keyword.");
}