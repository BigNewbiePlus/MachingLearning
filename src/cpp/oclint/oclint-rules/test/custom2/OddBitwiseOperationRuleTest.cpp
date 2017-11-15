#include "TestRuleOnCode.h"
#include "rules/custom2/OddBitwiseOperationRule.cpp"

TEST(OddBitwiseOperationRuleTest, PropertyTest)
{
    OddBitwiseOperationRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("odd bitwise operation", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(OddBitwiseOperationRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new OddBitwiseOperationRule(), 
            "void m(){int a,b;int c=a|b;}");
}

TEST(OddBitwiseOperationRuleTest, Test1)
{
         
    testRuleOnCXXCode(new OddBitwiseOperationRule(), 
            "void m(){\n"
            "int a; \nint b=a|a;}",0, 3, 7, 3, 9, "An odd bitwise operation detected: a|a. Consider verifying it.");
}

TEST(OddBitwiseOperationRuleTest, Test2)
{
         
    testRuleOnCXXCode(new OddBitwiseOperationRule(), 
            "void m(){\n"
            "int a; \nint b=a&a;}",0, 3, 7, 3, 9, "An odd bitwise operation detected: a&a. Consider verifying it.");
}

