#include "TestRuleOnCode.h"
#include "rules/custom2/MisprintsCommaForSemicolonRule.cpp"

TEST(MisprintsCommaForSemicolonRuleTest, PropertyTest)
{
    MisprintsCommaForSemicolonRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("misprints comma for semicolon", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(MisprintsCommaForSemicolonRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new MisprintsCommaForSemicolonRule(), 
            "void m(){int a,b;if(a!=0)a=1,b=2;}");
    testRuleOnCXXCode(new MisprintsCommaForSemicolonRule(), 
            "void m(){int a, b;if(a!=b){}else a=1, "
            "                                 b=2;}");
}

TEST(MisprintsCommaForSemicolonRuleTest, Test1)
{
         
    testRuleOnCXXCode(new MisprintsCommaForSemicolonRule(), 
            "void m(){\n"
            "int a;\nif(a!=0)\n"
            "            a=1,\n"
            "         a=2;}",0, 4, 13, 5, 12, "Consider checking for misprints. It's possible that ',' should be replaced by ';'.");
}

TEST(MisprintsCommaForSemicolonRuleTest, Test2)
{
         
    testRuleOnCXXCode(new MisprintsCommaForSemicolonRule(), 
            "int m(){\n"
            "int ab;\nif(ab==0)ab=1;"
            "         else\n"
            "            return ab=1,\n"
            "         ab=2;return 0;}",0, 4, 20, 5, 13, "Consider checking for misprints. It's possible that ',' should be replaced by ';'.");
}

