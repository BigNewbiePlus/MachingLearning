#include "TestRuleOnCode.h"
#include "rules/custom/AssignWithUninitVariableRuleRule.cpp"

TEST(AssignWithUninitVariableRuleRuleTest, PropertyTest)
{
    AssignWithUninitVariableRuleRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("assign with uninit variable rule", rule.name());
    EXPECT_EQ("custom", rule.category());
}


TEST(AssignWithUninitVariableRuleRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new AssignWithUninitVariableRuleRule(), "void m(){int b=0;}");
    testRuleOnCXXCode(new AssignWithUninitVariableRuleRule(), "void m(){int a=0;int b=a; }");
    testRuleOnCXXCode(new AssignWithUninitVariableRuleRule(), "void m(){int a=0;int b;b=a;}");
    testRuleOnCXXCode(new AssignWithUninitVariableRuleRule(), "void foo(int& a){a=0;} int main(){int a;foo(a);int c=a;}");
              
}

TEST(AssignWithUninitVariableRuleRuleTest, InitUse)
{
         
    testRuleOnCXXCode(new AssignWithUninitVariableRuleRule(), "void m(){int a;int b=a;}",
            0, 1, 16, 1, 22, "'int b=a' The local variable 'a' is uninitialized!");
}

TEST(AssignWithUninitVariableRuleRuleTest, CallExprUse) 
{

    testRuleOnCXXCode(new AssignWithUninitVariableRuleRule(), 
            "void foo(int a){int b=a;}\n"
            "int main(){int a;foo(a);}",
            0, 2, 18, 2, 23, "'foo(a)' Function call error! 'int b=a' The parameters 'a' is uninitialized!");
    
}

TEST(AssignWithUninitVariableRuleRuleTest, ComplexCallExprUse) 
{

    testRuleOnCXXCode(new AssignWithUninitVariableRuleRule(), 
            "void foo(int a){a=0;}\n"
            "void foo2(int& a){a=0;}\n"
            "int main(){int a;int b;foo(a);foo2(b);\n"
            "int c = a;\n"
            "int d = b;\n"
            "return 0;}",
            0, 4, 1, 4, 9, "'int c = a' The local variable 'a' is uninitialized!");
    
}
