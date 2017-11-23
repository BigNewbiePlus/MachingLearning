#include "TestRuleOnCode.h"
#include "rules/custom2/ElseBlockWasPossibleForgottenOrCommentOutRule.cpp"

TEST(ElseBlockWasPossibleForgottenOrCommentOutRuleTest, PropertyTest)
{
    ElseBlockWasPossibleForgottenOrCommentOutRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("else block was possible forgotten or comment out", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(ElseBlockWasPossibleForgottenOrCommentOutRuleTest, FirstFailingTest)
{
    EXPECT_FALSE("Start writing a new test");
}
