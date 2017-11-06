#include "TestRuleOnCode.h"
#include "rules/custom/AssignZeroValueToPointerRule.cpp"

TEST(AssignZeroValueToPointerRuleTest, PropertyTest)
{
    AssignZeroValueToPointerRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("assign zero value to pointer", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(AssignZeroValueToPointerRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new AssignZeroValueToPointerRule(), "void m(){char* tag;*tag = '\\0';}");
    testRuleOnCode(new AssignZeroValueToPointerRule(), 
                   "struct A{char* tag;};\n"
                   "void m(){struct A a;*a.tag = '\\0';}");
}

TEST(AssignZeroValueToPointerRuleTest, Test1)
{
         
    testRuleOnCode(new AssignZeroValueToPointerRule(),                     
                      "void m(){char* tag;\ntag='\\0';}",
            0, 2, 1, 2, 5, "It is odd that the '\\0' value is assigned to 'char *' type pointer. Probably meant: *tag='\\0'.");
}

TEST(AssignZeroValueToPointerRuleTest, Test2)
{
         
    testRuleOnCode(new AssignZeroValueToPointerRule(),                     
                      "struct A{char* tag;};\n"
                   "void m(){struct A a;\na.tag='\\0';}",
            0, 3, 1, 3, 7, "It is odd that the '\\0' value is assigned to 'char *' type pointer. Probably meant: *a.tag='\\0'.");
}
                   
                   
