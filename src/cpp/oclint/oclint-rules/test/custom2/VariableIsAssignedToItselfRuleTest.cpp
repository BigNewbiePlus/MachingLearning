#include "TestRuleOnCode.h"
#include "rules/custom2/VariableIsAssignedToItselfRule.cpp"

TEST(VariableIsAssignedToItselfRuleTest, PropertyTest)
{
    VariableIsAssignedToItselfRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("variable is assigned to itself", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(VariableIsAssignedToItselfRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new VariableIsAssignedToItselfRule(), 
            "struct A{int nf;};"
            "void m(){struct A a; struct A b;a.nf=b.nf;}");
    testRuleOnCXXCode(new VariableIsAssignedToItselfRule(), "void m(){unsigned char a,b; a=b;}");
}


TEST(VariableIsAssignedToItselfRuleTest, Test1)
{
         
    testRuleOnCXXCode(new VariableIsAssignedToItselfRule(), "void m(){unsigned char a;\n a  = a;}",0, 2, 2, 2, 7, "The a variable is assigned to itself.");
}

TEST(VariableIsAssignedToItselfRuleTest, Test2)
{
         
    testRuleOnCXXCode(new VariableIsAssignedToItselfRule(), 
            "typedef struct person{int age;}Person;\n"
            "void m(){Person lily;\nlily.age=lily.age;}", 0, 3, 1, 3, 15, "The lily.age variable is assigned to itself.");
}

TEST(VariableIsAssignedToItselfRuleTest, Test3)
{
         
    testRuleOnCXXCode(new VariableIsAssignedToItselfRule(), 
            "typedef struct person{int age;}Person;\n"
            "void m(){Person* lily;\nlily->age =lily->age;}", 0, 3, 1, 3, 18, "The lily->age variable is assigned to itself.");
}
