#include "TestRuleOnCode.h"
#include "rules/custom/ClassAsStringArgumentRule.cpp"

TEST(ClassAsStringArgumentRuleTest, PropertyTest)
{
    ClassAsStringArgumentRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("class as string argument", rule.name());
    EXPECT_EQ("custom", rule.category());
}
