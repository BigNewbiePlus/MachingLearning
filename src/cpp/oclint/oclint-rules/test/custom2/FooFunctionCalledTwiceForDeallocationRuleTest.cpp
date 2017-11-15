#include "TestRuleOnCode.h"
#include "rules/custom2/FooFunctionCalledTwiceForDeallocationRule.cpp"

TEST(FooFunctionCalledTwiceForDeallocationRuleTest, PropertyTest)
{
    FooFunctionCalledTwiceForDeallocationRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("foo function called twice for deallocation", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(FooFunctionCalledTwiceForDeallocationRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new FooFunctionCalledTwiceForDeallocationRule(),
            "#include<vector>\n"
            "using namespace std;\n"
            "void m(){vector<int> a; a.clear();}");
    testRuleOnCXXCode(new FooFunctionCalledTwiceForDeallocationRule(), 
            "#include<vector>\n"
            "using namespace std;\n"
            "void m(){vector<int> a, b; a.clear();b.clear();}");
}

TEST(FooFunctionCalledTwiceForDeallocationRuleTest, Test1)
{
         
    testRuleOnCXXCode(new FooFunctionCalledTwiceForDeallocationRule(), 
            "#include<vector>\n"
            "using namespace std;\n"
            "void m(){vector<int> a, b; a.clear();\na.clear();}"
           ,0, 4, 1, 4, 9, "The 'clear' function is called twice for deallocation of the same resource.");
}

