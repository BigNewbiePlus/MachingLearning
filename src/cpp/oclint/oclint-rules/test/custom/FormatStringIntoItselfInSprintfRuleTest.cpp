#include "TestRuleOnCode.h"
#include "rules/custom/FormatStringIntoItselfInSprintfRule.cpp"

TEST(FormatStringIntoItselfInSprintfRuleTest, PropertyTest)
{
    FormatStringIntoItselfInSprintfRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("format string into itself in sprintf", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(FormatStringIntoItselfInSprintfRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new FormatStringIntoItselfInSprintfRule(),
                   "#include<stdio.h>\n"
                   "void m(){char buffer[1024];char* str;sprintf(buffer,\"%s:%d\",str,1024);}");
}

TEST(FormatStringIntoItselfInSprintfRuleTest, Test1)
{
         
    testRuleOnCode(new FormatStringIntoItselfInSprintfRule(),                     
                      "#include<stdio.h>\n"
                   "void m(){char buffer[1024];char* str;\nsprintf(buffer,\"%s:%d\",buffer,1024);}",
            0, 3, 1, 3, 35, "It is dangerous to print the string 'buffer' into itself.");
}

TEST(FormatStringIntoItselfInSprintfRuleTest, Test2)
{
         
    testRuleOnCode(new FormatStringIntoItselfInSprintfRule(),                     
                      "#include<stdio.h>\n"
                   "void m(){char buffer[1024];char* str;\nsprintf(str,\"%s:%d\",str,1024);}",
            0, 3, 1, 3, 29, "It is dangerous to print the string 'str' into itself.");
}
