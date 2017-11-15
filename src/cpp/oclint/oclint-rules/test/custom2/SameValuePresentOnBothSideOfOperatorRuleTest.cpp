#include "TestRuleOnCode.h"
#include "rules/custom2/SameValuePresentOnBothSideOfOperatorRule.cpp"

TEST(SameValuePresentOnBothSideOfOperatorRuleTest, PropertyTest)
{
    SameValuePresentOnBothSideOfOperatorRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("same value present on both side of operator", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(SameValuePresentOnBothSideOfOperatorRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new SameValuePresentOnBothSideOfOperatorRule(),
            "void m(){int a,b,c;if(a>0){}if(a+b<c){}}");
    testRuleOnCXXCode(new SameValuePresentOnBothSideOfOperatorRule(), 
            "void m(){int a,b,c;if(a+b==c&&a<123){}if(a>0){}}");
}

TEST(SameValuePresentOnBothSideOfOperatorRuleTest, Test1)
{
         
    testRuleOnCXXCode(new SameValuePresentOnBothSideOfOperatorRule(), 
            "void m(){int a,b,c;\n"
            "if(a+1>a+b){}}",0, 2, 1, 2, 13, "The 'a' value is present on both sides of the '>' operator. The expression is incorrect or it can be simplified.");
}

TEST(SameValuePresentOnBothSideOfOperatorRuleTest, Test2)
{
         
    testRuleOnCXXCode(new SameValuePresentOnBothSideOfOperatorRule(), 
            "void m(){int a,b,c;\n"
            "if(a+b!=a+c){}\n}",0, 2, 1, 2, 14, "The 'a' value is present on both sides of the '!=' operator. The expression is incorrect or it can be simplified.");
}
