#include "TestRuleOnCode.h"
#include "rules/custom/ArrayIndexOutOfBoundRule.cpp"

TEST(ArrayIndexOutOfBoundRuleTest, PropertyTest)
{
    ArrayIndexOutOfBoundRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("array index out of bound", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(ArrayIndexOutOfBoundRuleTest, NoViolationInstance)    
{
    testRuleOnCode(new ArrayIndexOutOfBoundRule(), "void m(){int a[10];if(a[9]>10){}}");
    testRuleOnCode(new ArrayIndexOutOfBoundRule(), "void m(){int a;if(a>10){}}");
}

TEST(ArrayIndexOutOfBoundRuleTest, Test1)
{
         
    testRuleOnCode(new ArrayIndexOutOfBoundRule(),                     
                      "void m(){int a[10];if(\na[10]>10){}}",
            0, 2, 1, 2, 5, "Array overrun is possible. The '10' index is pointing beyond array bound.");
}
