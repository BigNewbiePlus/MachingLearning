#include "TestRuleOnCode.h"
#include "rules/custom/WithoutUseReturnValueOfFunctionRule.cpp"

TEST(WithoutUseReturnValueOfFunctionRuleTest, PropertyTest)
{
    WithoutUseReturnValueOfFunctionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("without use return value of function", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(WithoutUseReturnValueOfFunctionRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new WithoutUseReturnValueOfFunctionRule(), "void m(){} void foo(){m();}");
}

TEST(WithoutUseReturnValueOfFunctionRuleTest, Test1)
{
         
    testRuleOnCode(new WithoutUseReturnValueOfFunctionRule(),
                   "int num(){return 1;}\n"
                      "void foo(){\nnum();}",
            0, 3, 1, 3, 5, "The return value of function 'num' is required to be utilized.");
}

TEST(WithoutUseReturnValueOfFunctionRuleTest, Test2)
{
         
    testRuleOnCXXCode(new WithoutUseReturnValueOfFunctionRule(),
                   "#include<string>\n"
                   "using namespace std;\n"
                      "void foo(){string str;\nstr.empty();}",
            0, 4, 1, 4, 11, "The return value of function 'empty' is required to be utilized.");
}

