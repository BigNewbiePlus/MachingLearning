#include "TestRuleOnCode.h"
#include "rules/custom/UseCommaInArrayIndexRule.cpp"

TEST(UseCommaInArrayIndexRuleTest, PropertyTest)
{
    UseCommaInArrayIndexRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("use comma in array index", rule.name());
    EXPECT_EQ("custom", rule.category());
}


TEST(UseCommaInArrayIndexRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new UseCommaInArrayIndexRule(),
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   "void m(){int a[10][10];printf(\"%d\",a[0][0]);}");
}

TEST(UseCommaInArrayIndexRuleTest, Test1)
{
         
    testRuleOnCode(new UseCommaInArrayIndexRule(),
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                      "void foo(){for(int i=0;i<10;i++){int aa[10][10],b;printf(\"%d\",\naa[2,2]);}}",
            0, 4, 1, 4, 7, "The comma operator ',' in array index expression 'aa[2,2]'.");
}
