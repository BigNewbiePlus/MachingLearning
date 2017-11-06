#include "TestRuleOnCode.h"
#include "rules/custom/CmpFuncUseInConditionRule.cpp"

TEST(CmpFuncUseInConditionRuleTest, PropertyTest)
{
    CmpFuncUseInConditionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("cmp func use in condition", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(CmpFuncUseInConditionRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new CmpFuncUseInConditionRule(),
                   "#include<string.h>\n"
                   "void foo(){\n" 
                   "char str[1024];\n"
                   "if(strcmp(str,\"hello\")!=0 && (strcmp(str,\"world\")==0))\n{" 
                   "}}" 
                  );
}

TEST(CmpFuncUseInConditionRuleTest, Test1)
{
         
    testRuleOnCode(new CmpFuncUseInConditionRule(),                     
                   "#include<string.h>\n"
                   "void foo(){\n" 
                   "char str[1024];\n"
                   "if((strcmp(str,\"hello\")) && (strcmp(str,\"world\")==0))\n{" 
                   "}}",
            0, 4, 5, 4, 23, "The 'strcmp' function returns 0 if corresponding strings are equal. Consider examining the condition for mistakes.");
}

TEST(CmpFuncUseInConditionRuleTest, Test2)
{
         
    testRuleOnCode(new CmpFuncUseInConditionRule(),                     
                   "#include<string.h>\n"
                   "void foo(){\n" 
                   "char *s1, *s2;\n"
                   "if(memcmp(s1,s2,3) || (strcmp(s1,\"world\")==0))\n{" 
                   "}}",
            0, 4, 4, 4, 18, "The 'memcmp' function returns 0 if corresponding strings are equal. Consider examining the condition for mistakes.");
}

