#include "TestRuleOnCode.h"
#include "rules/custom2/SuspiciousMixOfIntegerAndRealExpressionRule.cpp"

TEST(SuspiciousMixOfIntegerAndRealExpressionRuleTest, PropertyTest)
{
    SuspiciousMixOfIntegerAndRealExpressionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("suspicious mix of integer and real expression", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(SuspiciousMixOfIntegerAndRealExpressionRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new SuspiciousMixOfIntegerAndRealExpressionRule(), 
            "void m(){int a;if(a==10){}}");
}

TEST(SuspiciousMixOfIntegerAndRealExpressionRuleTest, Test1)
{
         
    testRuleOnCXXCode(new SuspiciousMixOfIntegerAndRealExpressionRule(), 
            "void m(){\n"
            "int a=0;\nif(a>0.01){}}",0,3, 4, 3, 6, "The '0.01' literal of the 'double' type is subtracted from a variable of the 'int' type. Consider inspecting the 'a>0.01' expression.");
}
/*
TEST(SuspiciousMixOfIntegerAndRealExpressionRuleTest, Test2)
{
         
    testRuleOnCXXCode(new SuspiciousMixOfIntegerAndRealExpressionRule(), 
            "void m(){\n"
            "int a; \na=0.001;\nif(a){}}",0, 3, 1, 3, 6, "The '0.001' literal of the 'double' type is subtracted from a variable of the 'int' type. Consider inspecting the 'a=0.001' expression.");
}*/
