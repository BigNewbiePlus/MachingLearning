#include "TestRuleOnCode.h"
#include "rules/custom2/NonVoidFunctionShouldReturnAValueRule.cpp"

TEST(NonVoidFunctionShouldReturnAValueRuleTest, PropertyTest)
{
    NonVoidFunctionShouldReturnAValueRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("non void function should return a value", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(NonVoidFunctionShouldReturnAValueRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new NonVoidFunctionShouldReturnAValueRule(),
            "void m(){}");
    testRuleOnCXXCode(new NonVoidFunctionShouldReturnAValueRule(), 
            "int m(){return 0; }");
    testRuleOnCXXCode(new NonVoidFunctionShouldReturnAValueRule(), 
            "char m(){char a; return a;}");
}

TEST(NonVoidFunctionShouldReturnAValueRuleTest, Test1)
{
         
    testRuleOnCXXCode(new NonVoidFunctionShouldReturnAValueRule(), 
            "int m(){int a,b,c;a=b;\nif(a==10&&a!=5){};\n}"
           ,0, 1, 1, 3, 1, "Non-void function should return a value.");
}

