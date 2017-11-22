#include "TestRuleOnCode.h"
#include "rules/custom2/VariablesInitializedThroughSameFunctionCallRule.cpp"

TEST(VariablesInitializedThroughSameFunctionCallRuleTest, PropertyTest)
{
    VariablesInitializedThroughSameFunctionCallRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("variables initialized through same function call", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(VariablesInitializedThroughSameFunctionCallRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new VariablesInitializedThroughSameFunctionCallRule(), 
            "void m(){int a,b;a=0;b=0;}");
    testRuleOnCXXCode(new VariablesInitializedThroughSameFunctionCallRule(), 
            "int f1(){return 0;}int f2(){return 1;}"
            "void m(){int a,b;a=f1();b=f2();}");
}

TEST(VariablesInitializedThroughSameFunctionCallRuleTest, Test1)
{
         
    testRuleOnCXXCode(new VariablesInitializedThroughSameFunctionCallRule(), 
            "int fun(){return 0;}"
            "void m(){\n"
            "int a=fun();int b=fun();}",0, 2, 1, 2, 12, "Variables are initialized through the call to the same function. It's probably an error or un-optimized code.");
}

TEST(VariablesInitializedThroughSameFunctionCallRuleTest, Test2)
{
         
    testRuleOnCXXCode(new VariablesInitializedThroughSameFunctionCallRule(),
            "class rectangle{public:int height(){return 0;}};"
            "void m(){\n"
            "rectangle rect;int a,b;\na=rect.height();b=rect.height();}",0, 3, 1, 3, 15, "Variables are initialized through the call to the same function. It's probably an error or un-optimized code.");
}

