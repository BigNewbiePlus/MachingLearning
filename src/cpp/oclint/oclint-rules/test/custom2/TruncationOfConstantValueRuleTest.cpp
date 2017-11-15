#include "TestRuleOnCode.h"
#include "rules/custom2/TruncationOfConstantValueRule.cpp"

TEST(TruncationOfConstantValueRuleTest, PropertyTest)
{
    TruncationOfConstantValueRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("truncation of constant value", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(TruncationOfConstantValueRuleTest, NoViolationInstance)
{
    testRuleOnCode(new TruncationOfConstantValueRule(), "void m(){int a; a=-10;}");
    testRuleOnCode(new TruncationOfConstantValueRule(), "void m(){unsigned char a; a=10;}");
}


TEST(TruncationOfConstantValueRuleTest, Test1)
{
         
    testRuleOnCode(new TruncationOfConstantValueRule(), "void m(){unsigned char a;\na=-10;}",0, 2, 1, 2, 4, "Truncation of constant value -10. The value range of unsigned char type: [0, 255].");
}

TEST(TruncationOfConstantValueRuleTest, Test2)
{
         
    testRuleOnCode(new TruncationOfConstantValueRule(), "void m(){unsigned char a;\na=257;}", 0, 2, 1, 2, 3, "Truncation of constant value 257. The value range of unsigned char type: [0, 255].");
}

