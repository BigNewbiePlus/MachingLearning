#include "TestRuleOnCode.h"
#include "rules/custom2/RangeIntersectionAreWithinConditionExpressionRule.cpp"

TEST(RangeIntersectionAreWithinConditionExpressionRuleTest, PropertyTest)
{
    RangeIntersectionAreWithinConditionExpressionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("range intersection are within condition expression", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(RangeIntersectionAreWithinConditionExpressionRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new RangeIntersectionAreWithinConditionExpressionRule(), 
            "void m(){int a;if(a>0){}else if(a<-1){};}");
}

TEST(RangeIntersectionAreWithinConditionExpressionRuleTest, Test1)
{
         
    testRuleOnCXXCode(new RangeIntersectionAreWithinConditionExpressionRule(), 
            "void m(){\n"
            "int a;\nif(a>2){}else if(a>5){}}",0, 3, 1, 3, 23, "Range intersections are possible within conditional expressions. Example: if (A < 5) { ... } else if (A < 2) { ... }.");
}
TEST(RangeIntersectionAreWithinConditionExpressionRuleTest, Test2)
{
         
    testRuleOnCXXCode(new RangeIntersectionAreWithinConditionExpressionRule(), 
            "void m(){\n"
            "int a;\nif(a<=5){}else if(a<=2){}}",0, 3, 1, 3, 25, "Range intersections are possible within conditional expressions. Example: if (A < 5) { ... } else if (A < 2) { ... }.");
}
