#include "TestRuleOnCode.h"
#include "rules/custom/RepeatedIfConditionRule.cpp"

TEST(RepeatedIfConditionRuleTest, PropertyTest)
{
    RepeatedIfConditionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("repeated if condition", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(RepeatedIfConditionRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new RepeatedIfConditionRule(), "void m(){bool a,b,c,d;if(a){}else if(b){}else if(c){}}");
}

TEST(RepeatedIfConditionRuleTest, Test1)
{
         
    testRuleOnCXXCode(new RepeatedIfConditionRule(),                     
                      "void foo(){int a,b;\nif(a>b){}else if(a<b){}else if(a>b){}\n}",
            0, 2, 1, 2, 37, "The use of 'if (A) {...} else if (A) {...}' pattern was detected. There is a probability of logical error presence.");
}

TEST(RepeatedIfConditionRuleTest, Test2)
{
         
    testRuleOnCXXCode(new RepeatedIfConditionRule(),                     
                      "void foo(){bool a,b;\nif(a){}else if(b){}else if(a){}\n}",
            0, 2, 1, 2, 31, "The use of 'if (A) {...} else if (A) {...}' pattern was detected. There is a probability of logical error presence.");
}
