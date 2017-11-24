#include "TestRuleOnCode.h"
#include "rules/custom2/MacroExpansionResultIncorrectOrderRule.cpp"

TEST(MacroExpansionResultIncorrectOrderRuleTest, PropertyTest)
{
    MacroExpansionResultIncorrectOrderRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("macro expansion result incorrect order", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(MacroExpansionResultIncorrectOrderRuleTest, FirstFailingTest)
{
    EXPECT_FALSE("Start writing a new test");
}
