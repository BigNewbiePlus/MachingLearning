#include "TestRuleOnCode.h"
#include "rules/custom/InvalidSizeOfArgumentArrayPointRule.cpp"

TEST(InvalidSizeOfArgumentArrayPointRuleTest, PropertyTest)
{
    InvalidSizeOfArgumentArrayPointRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("invalid size of argument array point", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(InvalidSizeOfArgumentArrayPointRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new InvalidSizeOfArgumentArrayPointRule(), "void m(){int a[10];sizeof(a);}");
}

TEST(InvalidSizeOfArgumentArrayPointRuleTest, Test1)
{
         
    testRuleOnCXXCode(new InvalidSizeOfArgumentArrayPointRule(), "int m(int aa[10]){\nsizeof(aa);}",
            0, 2, 1, 2, 10, "The sizeof() operator returns size of the pointer, and not of the array, in 'sizeof(aa)' expression.");
}
