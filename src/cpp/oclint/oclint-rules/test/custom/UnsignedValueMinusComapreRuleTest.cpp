#include "TestRuleOnCode.h"
#include "rules/custom/UnsignedValueMinusComapreRule.cpp"

TEST(UnsignedValueMinusComapreRuleTest, PropertyTest)
{
    UnsignedValueMinusComapreRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("unsigned value minus comapre", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(UnsignedValueMinusComapreRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new UnsignedValueMinusComapreRule(), "void m(){int a,b; if(a-b>0){}}");
}

TEST(UnsignedValueMinusComapreRuleTest, Test1)
{
         
    testRuleOnCode(new UnsignedValueMinusComapreRule(),                     
                      "void m(){unsigned a[10]; if(\na[0]-10>0){}}",
            0, 2, 1, 2, 9, "The expression 'a[0]-10>0' will work as 'a[0] != 10'.");
}

TEST(UnsignedValueMinusComapreRuleTest, Test2)
{
         
    testRuleOnCode(new UnsignedValueMinusComapreRule(),                     
                      "void m(){unsigned a[10],b; if(\na[0]-b>0){}}",
            0, 2, 1, 2, 8, "The expression 'a[0]-b>0' will work as 'a[0] != b'.");
}
