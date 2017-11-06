#include "TestRuleOnCode.h"
#include "rules/custom/UseUnSenseCommaInExpressionRule.cpp"

TEST(UseUnSenseCommaInExpressionRuleTest, PropertyTest)
{
    UseUnSenseCommaInExpressionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("use un sense comma in expression", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(UseUnSenseCommaInExpressionRuleTest, NoViolationInstance)    
{
    testRuleOnCode(new UseUnSenseCommaInExpressionRule(), "void m(){int a,b,c;a=1;b=2;c=3;}");
    testRuleOnCode(new UseUnSenseCommaInExpressionRule(), "void m(){int a,b,c;a=1,b=2,c=3;}");
    testRuleOnCode(new UseUnSenseCommaInExpressionRule(), "void m(){int a;int b;int c;a++,--b,c++,b++;}");
    testRuleOnCode(new UseUnSenseCommaInExpressionRule(), "void m(){int a,b,c;a+=1,b-=2,c*=3,b/=2;}");
}

/*TEST(UseUnSenseCommaInExpressionRuleTest, Test1)
{        
    testRuleOnCode(new UseUnSenseCommaInExpressionRule(),                     
                      "void foo(){int bleedx, bleedy;\nbleedx=0,bleedy;}",
            0, 2, 10, 2, 10, "Such expressions using the ',' operator are dangerous. Make sure the expression is correct.");
}

TEST(UseUnSenseCommaInExpressionRuleTest, Test2)
{        
    testRuleOnCode(new UseUnSenseCommaInExpressionRule(),                     
                      "void foo(){for(int i = 0,j = 0;\ni<5,j<i;i++,j++){}}",
            0, 2, 1, 2, 3, "Such expressions using the ',' operator are dangerous. Make sure the expression is correct.");
}*/