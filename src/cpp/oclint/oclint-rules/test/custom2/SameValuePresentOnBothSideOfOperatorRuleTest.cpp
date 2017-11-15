#include "TestRuleOnCode.h"
#include "rules/custom2/SameValuePresentOnBothSideOfOperatorRule.cpp"

TEST(SameValuePresentOnBothSideOfOperatorRuleTest, PropertyTest)
{
    SameValuePresentOnBothSideOfOperatorRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("same value present on both side of operator", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(SameValuePresentOnBothSideOfOperatorRuleTest, FirstFailingTest)
{
    EXPECT_FALSE("Start writing a new test");
}
