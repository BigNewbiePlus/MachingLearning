#include "TestRuleOnCode.h"
#include "rules/custom2/UnsignedValueComparedToNegativeNumberRule.cpp"

TEST(UnsignedValueComparedToNegativeNumberRuleTest, PropertyTest)
{
    UnsignedValueComparedToNegativeNumberRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("unsigned value compared to negative number", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(UnsignedValueComparedToNegativeNumberRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new UnsignedValueComparedToNegativeNumberRule(), 
            "void m(){int a;if(a!=-1){}}");
    testRuleOnCXXCode(new UnsignedValueComparedToNegativeNumberRule(), 
            "void m(){unsigned int a;if(a!=10){}}");
}

TEST(UnsignedValueComparedToNegativeNumberRuleTest, Test1)
{
         
    testRuleOnCXXCode(new UnsignedValueComparedToNegativeNumberRule(), 
            "void m(){\n"
            "unsigned int a;\nif(a!=-1){}}",0, 3, 4, 3, 8, "Consider verifying the expression: a!=-1. An unsigned value is compared to the negative number.");
}

TEST(UnsignedValueComparedToNegativeNumberRuleTest, Test2)
{
         
    testRuleOnCXXCode(new UnsignedValueComparedToNegativeNumberRule(), 
            "void m(){\n"
            "unsigned char abc;\nif(abc==-10){}}",0, 3, 4, 3, 10, "Consider verifying the expression: abc==-10. An unsigned value is compared to the negative number.");
}

