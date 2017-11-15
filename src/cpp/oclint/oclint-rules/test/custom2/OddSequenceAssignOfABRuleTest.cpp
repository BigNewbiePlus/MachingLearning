#include "TestRuleOnCode.h"
#include "rules/custom2/OddSequenceAssignOfABRule.cpp"

TEST(OddSequenceAssignOfABRuleTest, PropertyTest)
{
    OddSequenceAssignOfABRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("odd sequence assign of a b", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(OddSequenceAssignOfABRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new OddSequenceAssignOfABRule(),
            "void m(){int a, b, c; a=b;b=c;}");
    testRuleOnCXXCode(new OddSequenceAssignOfABRule(), 
            "void m(){int a, b; a=b;a=10;b=a;}");
}

TEST(OddSequenceAssignOfABRuleTest, Test1)
{
         
    testRuleOnCXXCode(new OddSequenceAssignOfABRule(), 
            "void m(){int a,b,c;a=b;\nb=a;}"
           ,0, 2, 1, 2, 3, "An odd sequence of assignments of this kind: A = B; B = A;.");
}

