#include "TestRuleOnCode.h"
#include "rules/custom/InvalidPointToLocalVariableRule.cpp"

TEST(InvalidPointToLocalVariableRuleTest, PropertyTest)
{
    InvalidPointToLocalVariableRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("invalid point to local variable", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(InvalidPointToLocalVariableRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new InvalidPointToLocalVariableRule(), "void m(){int a;if(a==0){int* b; b=&a;}}");
    testRuleOnCXXCode(new InvalidPointToLocalVariableRule(), "void m(){int a;{a=0;};}");
    testRuleOnCXXCode(new InvalidPointToLocalVariableRule(), "void m(){int a;{int b; a=b;};}");
}

TEST(InvalidPointToLocalVariableRuleTest, Test1)
{
         
    testRuleOnCXXCode(new InvalidPointToLocalVariableRule(), "int m(){int* a;if(a!=0){int b;\na=&b;}}",
            0, 2, 1, 2, 4, "Pointer to local variable 'b' is stored outside the scope of this variable. Such a pointer will become invalid.");
}

TEST(InvalidPointToLocalVariableRuleTest, Test2)
{
         
    testRuleOnCXXCode(new InvalidPointToLocalVariableRule(), "int m(){int* a;if(a!=0){int* b;\na=b;};}",
            0, 2, 1, 2, 3, "Pointer to local variable 'b' is stored outside the scope of this variable. Such a pointer will become invalid.");
}


