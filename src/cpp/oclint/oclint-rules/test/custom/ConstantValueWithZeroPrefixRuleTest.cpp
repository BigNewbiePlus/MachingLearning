#include "TestRuleOnCode.h"
#include "rules/custom/ConstantValueWithZeroPrefixRule.cpp"

TEST(ConstantValueWithZeroPrefixRuleTest, PropertyTest)
{
    ConstantValueWithZeroPrefixRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("constant value with zero prefix", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(ConstantValueWithZeroPrefixRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new ConstantValueWithZeroPrefixRule(), "void m(){int a=0;}");
}

TEST(ConstantValueWithZeroPrefixRuleTest, Test1)
{
         
    testRuleOnCode(new ConstantValueWithZeroPrefixRule(),                     
                      "void foo(){for(int i=\n0123;i<10;i++){}}",
            0, 2, 1, 2, 1, "Be advised that the utilized constant value is represented by an octal form.");
}
