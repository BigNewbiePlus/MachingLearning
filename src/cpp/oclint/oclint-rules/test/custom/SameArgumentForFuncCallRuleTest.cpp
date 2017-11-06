#include "TestRuleOnCode.h"
#include "rules/custom/SameArgumentForFuncCallRule.cpp"

TEST(SameArgumentForFuncCallRuleTest, PropertyTest)
{
    SameArgumentForFuncCallRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("same argument for func call", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(SameArgumentForFuncCallRuleTest, NoViolationInstance)    
{
    testRuleOnCode(new SameArgumentForFuncCallRule(), "void m(char* a, char* b){}void test(){char*a;char* b;m(a,b);}");
}

TEST(SameArgumentForFuncCallRuleTest, Test1)
{       
    testRuleOnCode(new SameArgumentForFuncCallRule(),                     
                      "void m(char* a, char* b){}void test(){char*a;char* b;\nm(a,a);}",
            0, 2, 1, 2, 6, "The first argument of 'm' function is equal to the second argument.");
}

TEST(SameArgumentForFuncCallRuleTest, Test2)
{       
    testRuleOnCode(new SameArgumentForFuncCallRule(),                     
                      "void m(char* a, char* b){}void test(){char*aa;char* b;\nm( aa,aa );}",
            0, 2, 1, 2, 10, "The first argument of 'm' function is equal to the second argument.");
}
