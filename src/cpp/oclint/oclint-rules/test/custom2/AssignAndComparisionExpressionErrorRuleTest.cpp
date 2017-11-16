#include "TestRuleOnCode.h"
#include "rules/custom2/AssignAndComparisionExpressionErrorRule.cpp"

TEST(AssignAndComparisionExpressionErrorRuleTest, PropertyTest)
{
    AssignAndComparisionExpressionErrorRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("assign and comparision expression error", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(AssignAndComparisionExpressionErrorRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new AssignAndComparisionExpressionErrorRule(), 
            "void m(){int a,b;if((a=b)!=0){}}");
}

TEST(AssignAndComparisionExpressionErrorRuleTest, Test1)
{
         
    testRuleOnCXXCode(new AssignAndComparisionExpressionErrorRule(), 
            "void m(){\n"
            "int a,b;\nif(a=b!=0){}}",0, 3, 4, 3, 9, "Consider reviewing the expression of the 'A = B == C' kind. The expression is calculated as following: 'A = (B == C)'.");
}

