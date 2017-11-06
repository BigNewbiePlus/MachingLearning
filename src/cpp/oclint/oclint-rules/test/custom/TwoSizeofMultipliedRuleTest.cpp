#include "TestRuleOnCode.h"
#include "rules/custom/TwoSizeofMultipliedRule.cpp"

TEST(TwoSizeofMultipliedRuleTest, PropertyTest)
{
    TwoSizeofMultipliedRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("two sizeof multiplied", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(TwoSizeofMultipliedRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new TwoSizeofMultipliedRule(), "void m(){char szTmp[256];int result = sizeof(szTmp)*2;}");
    testRuleOnCode(new TwoSizeofMultipliedRule(), "void m(){char szTmp[256];int result = sizeof(szTmp)/sizeof(char);}");
}

TEST(TwoSizeofMultipliedRuleTest, Test1)
{
         
    testRuleOnCode(new TwoSizeofMultipliedRule(),                                          
                      "void m(){char szTmp[256];int result = \nsizeof(szTmp)*sizeof(char);}",
            0, 2, 1, 2, 26, "It is odd that a sizeof() operator is multiplied by sizeof().");
}