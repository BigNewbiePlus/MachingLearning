#include "TestRuleOnCode.h"
#include "rules/custom2/RecurringCheckRule.cpp"

TEST(RecurringCheckRuleTest, PropertyTest)
{
    RecurringCheckRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("recurring check", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(RecurringCheckRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new RecurringCheckRule(), "void m(){int a; if(a>0)if(a<10){}}");
    testRuleOnCXXCode(new RecurringCheckRule(), "void m(){int a;if(a>1){if(a<25){}}}");
}

TEST(RecurringCheckRuleTest, Test1)
{
         
    testRuleOnCXXCode(new RecurringCheckRule(), 
            "void m(){int a;\n"
            "if(a>0)if(a>0)a=10;}",0, 2, 1, 2, 17, "Recurring check. The IF Condition 'a>0' check twice.");
}

TEST(RecurringCheckRuleTest, Test2)
{
         
    testRuleOnCXXCode(new RecurringCheckRule(), 
            "void m(){unsigned char a;\n"
            "if(a>0){\n"
            "if(a<20){}\n"
            "if(a<30){}\n"
            "if(a>0){}\n"
            "}}", 0, 2, 1, 6, 1, "Recurring check. The IF Condition 'a>0' check twice.");
}

