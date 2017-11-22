#include "TestRuleOnCode.h"
#include "rules/custom2/ElseKeywordMissedAccodingToItsFormatRule.cpp"

TEST(ElseKeywordMissedAccodingToItsFormatRuleTest, PropertyTest)
{
    ElseKeywordMissedAccodingToItsFormatRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("else keyword missed accoding to its format", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(ElseKeywordMissedAccodingToItsFormatRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new ElseKeywordMissedAccodingToItsFormatRule(), 
            "void m(){int a,b;if(a>0){}\nif(a<0){}}");
}

TEST(ElseKeywordMissedAccodingToItsFormatRuleTest, Test1)
{
         
    testRuleOnCXXCode(new ElseKeywordMissedAccodingToItsFormatRule(), 
            "void m(){\n"
            "   int a;\n"
            "   if(a>0){\n"
            "   }if(a<0){\n"
            "   }"
            "}",0, 4, 5, 5, 4, "Consider inspecting the application's logic. It's possible that 'else' keyword is missing.");
}

