#include "TestRuleOnCode.h"
#include "rules/custom2/PatternAOrAExpressionIsExecessiveRule.cpp"

TEST(PatternAOrAExpressionIsExecessiveRuleTest, PropertyTest)
{
    PatternAOrAExpressionIsExecessiveRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("pattern a or a expression is execessive", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(PatternAOrAExpressionIsExecessiveRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new PatternAOrAExpressionIsExecessiveRule(), 
            "void m(){int a,b,c;if(a||(b&&c)){}}");
}

TEST(PatternAOrAExpressionIsExecessiveRuleTest, Test1)
{
         
    testRuleOnCXXCode(new PatternAOrAExpressionIsExecessiveRule(), 
            "void m(){\n"
            "int a,b;\nif(a||(b&&a)){}}", 0, 3, 4, 3, 12, "A pattern was detected: A || (A && ...). The expression is excessive or contains a logical error.");
}

TEST(PatternAOrAExpressionIsExecessiveRuleTest, Test2)
{
         
    testRuleOnCXXCode(new PatternAOrAExpressionIsExecessiveRule(), 
            "void m(){\n"
            "bool tipsel, rootsel;\nif ((tipsel && rootsel) || rootsel) {}}"
            ,0, 3, 5, 3, 28, "A pattern was detected: A || (A && ...). The expression is excessive or contains a logical error.");
}
TEST(PatternAOrAExpressionIsExecessiveRuleTest, Test3)
{
         
    testRuleOnCXXCode(new PatternAOrAExpressionIsExecessiveRule(), 
            "void m(){\n"
            "bool tm_mday, cfg_start_day, before;\nif (tm_mday < cfg_start_day ||(tm_mday < cfg_start_day && before)) {}}",0, 3, 5, 3, 65, "A pattern was detected: A || (A && ...). The expression is excessive or contains a logical error.");
}
