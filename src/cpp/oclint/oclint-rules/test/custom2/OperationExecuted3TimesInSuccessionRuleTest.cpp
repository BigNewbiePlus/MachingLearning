#include "TestRuleOnCode.h"
#include "rules/custom2/OperationExecuted3TimesInSuccessionRule.cpp"

TEST(OperationExecuted3TimesInSuccessionRuleTest, PropertyTest)
{
    OperationExecuted3TimesInSuccessionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("operation executed3 times in succession", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(OperationExecuted3TimesInSuccessionRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new OperationExecuted3TimesInSuccessionRule(), 
            "void m(){int a,b;if(!a){}}");
    testRuleOnCXXCode(new OperationExecuted3TimesInSuccessionRule(), 
            "void m(){int a,b;if(!!a){}\nif(a>0){}}");
}

TEST(OperationExecuted3TimesInSuccessionRuleTest, test1)
{
         
    testRuleOnCXXCode(new OperationExecuted3TimesInSuccessionRule(), 
            "void m(){int a;\nif(!!!a){}"
            "}",0, 2, 4, 2, 7, "The '!' operation is executed 3 or more times in succession.");
}

