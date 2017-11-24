#include "TestRuleOnCode.h"
#include "rules/custom2/SuspiciousCompoundAssignmentExpressionRule.cpp"

TEST(SuspiciousCompoundAssignmentExpressionRuleTest, PropertyTest)
{
    SuspiciousCompoundAssignmentExpressionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("suspicious compound assignment expression", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(SuspiciousCompoundAssignmentExpressionRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new SuspiciousCompoundAssignmentExpressionRule(), 
            "void m(){int a;a+=10;}");
}

TEST(SuspiciousCompoundAssignmentExpressionRuleTest, Test1)
{
         
    testRuleOnCXXCode(new SuspiciousCompoundAssignmentExpressionRule(), 
            "void m(){\n"
            "int a;\na+=a+10;}",0, 3, 1, 3, 6, "A compound assignment expression 'X += X + N' is suspicious. Consider inspecting it for a possible error.");
}
