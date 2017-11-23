#include "TestRuleOnCode.h"
#include "rules/custom2/VariableInitializedThroughItselfRule.cpp"

TEST(VariableInitializedThroughItselfRuleTest, PropertyTest)
{
    VariableInitializedThroughItselfRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("variable initialized through itself", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(VariableInitializedThroughItselfRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new VariableInitializedThroughItselfRule(), 
            "void m(){int a,b;int c=a=b;}");
}

TEST(VariableInitializedThroughItselfRuleTest, Test1)
{
         
    testRuleOnCXXCode(new VariableInitializedThroughItselfRule(), 
            "void m(){\n"
            "int a,b;\nint c=c=a;}",0, 3, 1, 3, 9, "Consider inspecting the 'T foo = foo = x;' expression. It is odd that variable is initialized through itself.");
}

TEST(VariableInitializedThroughItselfRuleTest, Test2)
{
         
    testRuleOnCXXCode(new VariableInitializedThroughItselfRule(), 
            "class Person{};"
            "void m(){\n"
            "Person tom;\nPerson lily=lily=tom;}",0, 3, 1, 3, 18, "Consider inspecting the 'T foo = foo = x;' expression. It is odd that variable is initialized through itself.");
}
TEST(VariableInitializedThroughItselfRuleTest, Test3)
{
         
    testRuleOnCXXCode(new VariableInitializedThroughItselfRule(), 
            "typedef struct person{}Person;"
            "void m(){\n"
            "Person tom;\nPerson lily=lily=tom;}",0, 3, 1, 3, 18, "Consider inspecting the 'T foo = foo = x;' expression. It is odd that variable is initialized through itself.");
}
