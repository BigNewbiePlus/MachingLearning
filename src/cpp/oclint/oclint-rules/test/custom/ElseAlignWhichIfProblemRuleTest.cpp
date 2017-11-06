#include "TestRuleOnCode.h"
#include "rules/custom/ElseAlignWhichIfProblemRule.cpp"

TEST(ElseAlignWhichIfProblemRuleTest, PropertyTest)
{
    ElseAlignWhichIfProblemRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("else align which if problem", rule.name());
    EXPECT_EQ("custom", rule.category());
}


TEST(ElseAlignWhichIfProblemRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new ElseAlignWhichIfProblemRule(),
"void foo3(){\n"
"     bool X,Y;\n"
"    int z;\n"   
"    if (X)\n"
"        if (Y)\n"
"            foo3();\n"
"        else\n"
"            z = 1;\n"
"}"
);
    
    testRuleOnCXXCode(new ElseAlignWhichIfProblemRule(),
"void foo3(){\n"
"     bool X,Y;\n"
"    int z;\n"   
"    if (X){\n"
"        if (Y)\n"
"            foo3();\n"
"        else\n"
"            z = 1;\n"
"}"
"}"
);
}

TEST(ElseAlignWhichIfProblemRuleTest, Test1)
{
         
    testRuleOnCXXCode(new ElseAlignWhichIfProblemRule(),                     
"void foo()\n"
"{\n"
"    bool X,Y;\n"
"    int z;\n"
"    if (X)\n"
"        if (Y) foo();\n"
"    else\n"
"        z = 1;\n"
"}\n",
            0, 5, 5, 8, 13, "It is possible that this 'else' branch must apply to the previous 'if' statement.");
}
