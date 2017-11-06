#include "TestRuleOnCode.h"
#include "rules/custom/BoolIncrementRule.cpp"

TEST(BoolIncrementRuleTest, PropertyTest)
{
    BoolIncrementRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("bool increment", rule.name());
    EXPECT_EQ("custom", rule.category());
}
TEST(BoolIncrementRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new BoolIncrementRule(), 
                      "#include<iostream>\n"
                      "void m(){bool a=false; if(a){}}");
}

TEST(BoolIncrementRuleTest, Test1)
{
         
    testRuleOnCXXCode(new BoolIncrementRule(), 
                   "#include<iostream>\n"
                      "void m(){bool a=false; if(\na++){}}",
            0, 3, 1, 3, 2, "A bool type variable is being incremented: a++. Perhaps another variable should be incremented instead.");
}
