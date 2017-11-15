#include "TestRuleOnCode.h"
#include "rules/custom2/FunctionReceivesAnOddArgumentRule.cpp"

TEST(FunctionReceivesAnOddArgumentRuleTest, PropertyTest)
{
    FunctionReceivesAnOddArgumentRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("function receives an odd argument", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(FunctionReceivesAnOddArgumentRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new FunctionReceivesAnOddArgumentRule(),
            "#include<string.h>\n"
            "typedef struct person{}Person;"
            "void m(){Person peter; memset(&peter, 0, sizeof(peter));}");
    testRuleOnCXXCode(new FunctionReceivesAnOddArgumentRule(), 
            "#include<string.h>\n"
            "void m(){int a;memset(&a, 0, sizeof(a))}");
}

TEST(FunctionReceivesAnOddArgumentRuleTest, Test1)
{
         
    testRuleOnCXXCode(new FunctionReceivesAnOddArgumentRule(), 
            "#include<string.h>\n"
            "typedef struct person{}Person;\n"
            "void m(){Person peter;\n"
            "memset(&peter, sizeof(peter),0);}",0, 4, 1, 4, 33, "The 'memset' function processes '0' elements. Inspect the third argument.");
}

TEST(FunctionReceivesAnOddArgumentRuleTest, Test2)
{
         
    testRuleOnCXXCode(new FunctionReceivesAnOddArgumentRule(), 
            "#include<string.h>\n"
            "void m(){unsigned char a;\n"
            "memset(&a, 0, sizeof(a));"
            "}", 0, 3, 1, 3, 24, "The 'memset' function processes '0' elements. Inspect the third argument.");
}

