#include "TestRuleOnCode.h"
#include "rules/custom/ComparePointerWithZeroValueRule.cpp"

TEST(ComparePointerWithZeroValueRuleTest, PropertyTest)
{
    ComparePointerWithZeroValueRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("compare pointer with zero value", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(ComparePointerWithZeroValueRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new ComparePointerWithZeroValueRule(), "void m(){char* tag;if(*tag == '\\0'){}}");
    testRuleOnCode(new ComparePointerWithZeroValueRule(), 
                   "struct A{char* tag;};\n"
                   "void m(){struct A a;if(*a.tag = '\\0'){};}");
}

TEST(ComparePointerWithZeroValueRuleTest, Test1)
{
         
    testRuleOnCode(new ComparePointerWithZeroValueRule(),                     
                      "void m(){char* tag;\nif(tag!='\\0'){}}",
            0, 2, 4, 2, 9, "It is odd that pointer to 'char *' type is compared with the '\\0' value. Probably meant: *tag!='\\0'.");
}

TEST(ComparePointerWithZeroValueRuleTest, Test2)
{
         
    testRuleOnCode(new ComparePointerWithZeroValueRule(),                     
                      "struct A{char* tag;};\n"
                   "void m(){struct A a;\nif(a.tag=='\\0'){};}",
            0, 3, 4, 3, 11, "It is odd that pointer to 'char *' type is compared with the '\\0' value. Probably meant: *a.tag=='\\0'.");
}
