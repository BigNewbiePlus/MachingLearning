#include "TestRuleOnCode.h"
#include "rules/custom2/StringOfTwoPartsUsedForArrayInitializationRule.cpp"

TEST(StringOfTwoPartsUsedForArrayInitializationRuleTest, PropertyTest)
{
    StringOfTwoPartsUsedForArrayInitializationRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("string of two parts used for array initialization", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(StringOfTwoPartsUsedForArrayInitializationRuleTest, FirstFailingTest)
{
    EXPECT_FALSE("Start writing a new test");
}
