#include "TestRuleOnCode.h"
#include "rules/custom2/PointerPlusConstantConditionIsFalseRule.cpp"

TEST(PointerPlusConstantConditionIsFalseRuleTest, PropertyTest)
{
    PointerPlusConstantConditionIsFalseRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("pointer plus constant condition is false", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(PointerPlusConstantConditionIsFalseRuleTest, FirstFailingTest)
{
    EXPECT_FALSE("Start writing a new test");
}
