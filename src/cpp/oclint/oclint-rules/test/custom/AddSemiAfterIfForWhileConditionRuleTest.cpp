#include "TestRuleOnCode.h"
#include "rules/custom/AddSemiAfterIfForWhileConditionRule.cpp"

TEST(AddSemiAfterIfForWhileConditionRuleTest, PropertyTest)
{
    AddSemiAfterIfForWhileConditionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("add semi after if for while condition", rule.name());
    EXPECT_EQ("custom", rule.category());
}


TEST(AddSemiAfterIfForWhileConditionRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new AddSemiAfterIfForWhileConditionRule(), "void m(){for(int i=0;i<10;i++){}}");
    testRuleOnCode(new AddSemiAfterIfForWhileConditionRule(), "void m(){int a;if(a>0){}}");
    testRuleOnCode(new AddSemiAfterIfForWhileConditionRule(), "void m(){int a;while(a<0){}}");
}

TEST(AddSemiAfterIfForWhileConditionRuleTest, Test1)
{
         
    testRuleOnCode(new AddSemiAfterIfForWhileConditionRule(),                     
                      "void foo(){\nfor(int i=0;i<10;i++);{}}",
            0, 2, 1, 2, 22, "Odd semicolon ';' after 'for' operator.");
}

TEST(AddSemiAfterIfForWhileConditionRuleTest, Test2)
{
         
    testRuleOnCode(new AddSemiAfterIfForWhileConditionRule(),                     
                      "void foo(){int a;\nif(a<0);{}}",
            0, 2, 1, 2,8, "Odd semicolon ';' after 'if' operator.");
}

TEST(AddSemiAfterIfForWhileConditionRuleTest, Test3)
{
         
    testRuleOnCode(new AddSemiAfterIfForWhileConditionRule(),                     
                      "void foo(){int a;\nwhile(a<0);{}}",
            0, 2, 1, 2,11, "Odd semicolon ';' after 'while' operator.");
}
