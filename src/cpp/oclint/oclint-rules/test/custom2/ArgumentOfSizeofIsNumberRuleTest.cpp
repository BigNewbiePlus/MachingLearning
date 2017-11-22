#include "TestRuleOnCode.h"
#include "rules/custom2/ArgumentOfSizeofIsNumberRule.cpp"

TEST(ArgumentOfSizeofIsNumberRuleTest, PropertyTest)
{
    ArgumentOfSizeofIsNumberRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("argument of sizeof is number", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(ArgumentOfSizeofIsNumberRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new ArgumentOfSizeofIsNumberRule(), 
            "void m(){int a,b;if(a!=0)a=sizeof(a);}");
    testRuleOnCXXCode(new ArgumentOfSizeofIsNumberRule(), 
            "void m(){int a, b;if(a!=b){}else a=sizeof b;}");
}

TEST(ArgumentOfSizeofIsNumberRuleTest, Test1)
{
         
    testRuleOnCXXCode(new ArgumentOfSizeofIsNumberRule(), 
            "void m(){\n"
            "int a;a=\nsizeof(10);}",0, 3, 1, 3, 10, "Consider inspecting the expression. The argument of sizeof() is the macro which expands to a number.");
}

TEST(ArgumentOfSizeofIsNumberRuleTest, Test2)
{
         
    testRuleOnCXXCode(new ArgumentOfSizeofIsNumberRule(), 
            "#define MAXNUM 100\n"
            "int m(){\n"
            "int a=2;a=\nsizeof MAXNUM;return 0;}",0, 4, 1, 4, 8, "Consider inspecting the expression. The argument of sizeof() is the macro which expands to a number.");
}

