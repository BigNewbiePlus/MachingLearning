#include "TestRuleOnCode.h"
#include "rules/custom2/ArrayPointerAlwaysNotEqualNULLRule.cpp"

TEST(ArrayPointerAlwaysNotEqualNULLRuleTest, PropertyTest)
{
    ArrayPointerAlwaysNotEqualNULLRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("array pointer always not equal n u l l", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(ArrayPointerAlwaysNotEqualNULLRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new ArrayPointerAlwaysNotEqualNULLRule(), 
            "void m(){int a,b;if(a!=0){}}");
    testRuleOnCXXCode(new ArrayPointerAlwaysNotEqualNULLRule(), 
            "void m(){int a[10], b[10];if(a!=b){}}");
}

TEST(ArrayPointerAlwaysNotEqualNULLRuleTest, Test1)
{
         
    testRuleOnCXXCode(new ArrayPointerAlwaysNotEqualNULLRule(), 
            "void m(){\n"
            "int a[10];\nif(a!=0){}}",0, 3, 4, 3, 7, "Consider inspecting the condition. The 'a' pointer is always not equal to NULL.");
}

TEST(ArrayPointerAlwaysNotEqualNULLRuleTest, Test2)
{
         
    testRuleOnCXXCode(new ArrayPointerAlwaysNotEqualNULLRule(), 
            "void m(){\n"
            "char ab[10];\nif(ab==0){}}",0, 3, 4, 3, 8, "Consider inspecting the condition. The 'ab' pointer is always not equal to NULL.");
}

