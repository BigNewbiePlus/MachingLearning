#include "TestRuleOnCode.h"
#include "rules/custom/DividingSizeofAPointerByAnotherValueRule.cpp"

TEST(DividingSizeofAPointerByAnotherValueRuleTest, PropertyTest)
{
    DividingSizeofAPointerByAnotherValueRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("dividing sizeof a pointer by another value", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(DividingSizeofAPointerByAnotherValueRuleTest, NoViolationInstance)    
{
    testRuleOnCode(new DividingSizeofAPointerByAnotherValueRule(), "void m(){int a[10]; sizeof(a)/sizeof(int);}");
}

TEST(DividingSizeofAPointerByAnotherValueRuleTest, Test1)
{         
    testRuleOnCode(new DividingSizeofAPointerByAnotherValueRule(),                     
                      "void foo(){int* aa;\nsizeof(aa)/sizeof(aa[0]);}",
            0, 2, 1, 2, 10, "Dividing sizeof a pointer 'sizeof(aa)' by another value. There is a probability of logical error presence.");
}

TEST(DividingSizeofAPointerByAnotherValueRuleTest, Test2)
{        
    testRuleOnCode(new DividingSizeofAPointerByAnotherValueRule(),                     
                      "void foo(){int* aa;if(aa){\nint a=sizeof(aa)/sizeof(aa[0]);}}",
            0, 2, 7, 2, 16, "Dividing sizeof a pointer 'sizeof(aa)' by another value. There is a probability of logical error presence.");
}
