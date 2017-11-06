#include "TestRuleOnCode.h"
#include "rules/custom/AssignInConditionRule.cpp"

TEST(AssignInConditionRuleTest, PropertyTest)
{
    AssignInConditionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("assign in condition", rule.name());
    EXPECT_EQ("custom", rule.category());
}


TEST(AssignInConditionRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new AssignInConditionRule(), "void m(){int a;if((a=0)>10){}}");
}

TEST(AssignInConditionRuleTest, Test1)
{        
    testRuleOnCode(new AssignInConditionRule(),                     
                      "typedef struct a{int domain;int code;}A;"
                   "void foo(){A* error;  if (!(\nerror->domain = 10 && error->code == 100)){ }}",
            0, 2, 1, 2, 38, "Suspicious assignment inside the condition expression of 'if' operator: error->domain = 10 && error->code == 100.");
}
