#include "TestRuleOnCode.h"
#include "rules/custom/InvalidPointToLocalArrayRule.cpp"

TEST(InvalidPointToLocalArrayRuleTest, PropertyTest)
{
    InvalidPointToLocalArrayRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("invalid point to local array", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(InvalidPointToLocalArrayRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new InvalidPointToLocalArrayRule(), "void m(){int a[10];if(a[0]==0){int* b; b=a;}}");
    testRuleOnCXXCode(new InvalidPointToLocalArrayRule(), "void m(){int a[10];{a[0]=0;};}");
    testRuleOnCXXCode(new InvalidPointToLocalArrayRule(), "void m(){int a[10];{int b; a[0]=b;};}");
}

TEST(InvalidPointToLocalArrayRuleTest, Test1)
{
         
    testRuleOnCXXCode(new InvalidPointToLocalArrayRule(), "int m(){int* a;if(a!=0){int b[10];\na=b;}}",
            0, 2, 1, 2, 3, "Pointer to local array 'b' is stored outside the scope of this array. Such a pointer will become invalid.");
}
