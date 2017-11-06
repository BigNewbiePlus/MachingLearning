#include "TestRuleOnCode.h"
#include "rules/custom/ThenAndElseBodyEquivalentRule.cpp"

TEST(ThenAndElseBodyEquivalentRuleTest, PropertyTest)
{
    ThenAndElseBodyEquivalentRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("then and else body equivalent", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(ThenAndElseBodyEquivalentRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new ThenAndElseBodyEquivalentRule(), "void m(){int a,b,c; int flag; if(flag){a=b+c;}}");
    testRuleOnCode(new ThenAndElseBodyEquivalentRule(), "void m(){int a,b,c; int flag; if(flag){a=b+c;}else{a=b-c;}}");
}

TEST(ThenAndElseBodyEquivalentRuleTest, Test1)
{
         
    testRuleOnCode(new ThenAndElseBodyEquivalentRule(),                     
                      
                      "void m(){int a,b,c; int flag; \nif(flag){a=b+c;}else{a=b+c;}}",
            0, 2, 1, 2, 28, "The 'then' statement is equivalent to the 'else' statement.");
}
