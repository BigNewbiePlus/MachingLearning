#include "TestRuleOnCode.h"
#include "rules/custom/StrlenConstantValueInMallocRule.cpp"

TEST(StrlenConstantValueInMallocRuleTest, PropertyTest)
{
    StrlenConstantValueInMallocRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("strlen constant value in malloc", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(StrlenConstantValueInMallocRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new StrlenConstantValueInMallocRule(), 
                   "#include<stdlib.h>\n"
                   "#include<string.h>\n"
                   "void m(){char* src, *p; p = (char *)malloc(strlen(src) + 1);}");
}

TEST(StrlenConstantValueInMallocRuleTest, Test1)
{
         
    testRuleOnCode(new StrlenConstantValueInMallocRule(),                     
                   "#include<stdlib.h>\n"
                   "#include<string.h>\n"
                   "void foo(){char* src, *p;\n"
                   "p=(char *)malloc(strlen(src+1));}",
            0, 4, 18, 4, 30, "The 'malloc' function allocates strange amount of memory calculated by 'strlen(src+1)'.");
}

TEST(StrlenConstantValueInMallocRuleTest, Test2)
{
         
    testRuleOnCode(new StrlenConstantValueInMallocRule(),                     
                   "#include<stdlib.h>\n"
                   "#include<string.h>\n"
                   "void foo(){char* src, *p;\n"
                   "p=(char *)realloc(p,strlen(src+1));}",
            0, 4, 21, 4, 33, "The 'realloc' function allocates strange amount of memory calculated by 'strlen(src+1)'.");
}