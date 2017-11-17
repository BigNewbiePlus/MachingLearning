#include "TestRuleOnCode.h"
#include "rules/custom2/BitwiseOperationWithZeroConstantValueRule.cpp"

TEST(BitwiseOperationWithZeroConstantValueRuleTest, PropertyTest)
{
    BitwiseOperationWithZeroConstantValueRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("bitwise operation with zero constant value", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(BitwiseOperationWithZeroConstantValueRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new BitwiseOperationWithZeroConstantValueRule(),
            "enum Day{Monday=1};"
            "void m(){int a=2;if(a&Monday){}}");
    testRuleOnCXXCode(new BitwiseOperationWithZeroConstantValueRule(),
            "enum Day{Monday,Tuesday};"
            "void m(){int a=2;if(a&Tuesday){}}");
}


TEST(BitwiseOperationWithZeroConstantValueRuleTest, Test1)
{
         
    testRuleOnCXXCode(new BitwiseOperationWithZeroConstantValueRule(), 
            "enum Day{Monday=0,};"
            "void m(){\n"
            "int a; \nif(a&Monday){}}",0, 3, 4, 3, 6, " The 'Monday' named constant with the value of 0 is used in the bitwise operation.");
}

TEST(BitwiseOperationWithZeroConstantValueRuleTest, Test2)
{
         
    testRuleOnCXXCode(new BitwiseOperationWithZeroConstantValueRule(), 
            "enum Day{Monday,Tuesday};"
            "void m(){\n"
            "int a; \nint b=a&Monday;}",0, 3, 7, 3, 9, " The 'Monday' named constant with the value of 0 is used in the bitwise operation.");
}

