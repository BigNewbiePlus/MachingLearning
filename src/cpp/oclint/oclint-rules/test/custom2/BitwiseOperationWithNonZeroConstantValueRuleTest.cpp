#include "TestRuleOnCode.h"
#include "rules/custom2/BitwiseOperationWithNonZeroConstantValueRule.cpp"

TEST(BitwiseOperationWithNonZeroConstantValueRuleTest, PropertyTest)
{
    BitwiseOperationWithNonZeroConstantValueRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("bitwise operation with non zero constant value", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(BitwiseOperationWithNonZeroConstantValueRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new BitwiseOperationWithNonZeroConstantValueRule(),
            "#define MONKEY 0x0000\n"
            "void m(){int a=2;if(a|MONKEY){}}");
    testRuleOnCXXCode(new BitwiseOperationWithNonZeroConstantValueRule(),
            "enum Day{Monday,Tuesday};"
            "void m(){int a=2;if(a&Tuesday){}}");
}


TEST(BitwiseOperationWithNonZeroConstantValueRuleTest, Test1)
{
         
    testRuleOnCXXCode(new BitwiseOperationWithNonZeroConstantValueRule(), 
            "#define MONKEY 0x0012\n"
            "void m(){"
            "int a; \nif(a|MONKEY){}}",0, 3, 4, 3, 6, "Consider inspecting the condition. The 'MONKEY' argument of the '|' bitwise operation contains a non-zero value.");
}

TEST(BitwiseOperationWithNonZeroConstantValueRuleTest, Test2)
{
         
    testRuleOnCXXCode(new BitwiseOperationWithNonZeroConstantValueRule(), 
            "#define MONKEY 0x0002\n"
            "void m(){"
            "int a; \nint b=a|MONKEY;}",0, 3, 7, 3, 9, "Consider inspecting the condition. The 'MONKEY' argument of the '|' bitwise operation contains a non-zero value.");
}

