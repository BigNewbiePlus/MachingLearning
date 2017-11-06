#include "TestRuleOnCode.h"
#include "rules/custom/OddTypeCastRule.cpp"

TEST(OddTypeCastRuleTest, PropertyTest)
{
    OddTypeCastRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("odd type cast", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(OddTypeCastRuleTest, NoViolationInstance)    
{
    testRuleOnCode(new OddTypeCastRule(), "void m(){char* p;if((char*)p){}}");
    testRuleOnCode(new OddTypeCastRule(), "void m(){char* p;if((void*)p){}}");
    testRuleOnCode(new OddTypeCastRule(), "void m(){char* p;if((int*)p){}}");
}

TEST(OddTypeCastRuleTest, Test1)
{
         
    testRuleOnCode(new OddTypeCastRule(),                     
                      "void m(){char* p;if(\n(char)p){}}",
                   0, 2, 1, 2, 7,"Consider inspecting an odd type cast: 'char *' to 'char'.");
}
