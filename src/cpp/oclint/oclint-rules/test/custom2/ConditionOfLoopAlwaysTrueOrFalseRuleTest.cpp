#include "TestRuleOnCode.h"
#include "rules/custom2/ConditionOfLoopAlwaysTrueOrFalseRule.cpp"

TEST(ConditionOfLoopAlwaysTrueOrFalseRuleTest, PropertyTest)
{
    ConditionOfLoopAlwaysTrueOrFalseRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("condition of loop always true or false", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(ConditionOfLoopAlwaysTrueOrFalseRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new ConditionOfLoopAlwaysTrueOrFalseRule(), 
            "void m(){int a,b;while(a>0){a++;}}");
    testRuleOnCXXCode(new ConditionOfLoopAlwaysTrueOrFalseRule(), 
            "void m(){int a,b;while(a!=b){a+=1;}\nif(a>0){}}");
}

TEST(ConditionOfLoopAlwaysTrueOrFalseRuleTest, test1)
{
         
    testRuleOnCXXCode(new ConditionOfLoopAlwaysTrueOrFalseRule(), 
            "void m(){int a;\nwhile(a>0){}"
            "}",0, 2, 1, 2, 12, "The condition of loop is always true.");
}

TEST(ConditionOfLoopAlwaysTrueOrFalseRuleTest, test2)
{
         
    testRuleOnCXXCode(new ConditionOfLoopAlwaysTrueOrFalseRule(), 
            "void m(){int a;\nwhile(a!=0){}"
            "}",0, 2, 1, 2, 13, "The condition of loop is always true.");
}
