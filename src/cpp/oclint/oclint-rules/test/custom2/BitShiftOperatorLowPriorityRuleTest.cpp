#include "TestRuleOnCode.h"
#include "rules/custom2/BitShiftOperatorLowPriorityRule.cpp"

TEST(BitShiftOperatorLowPriorityRuleTest, PropertyTest)
{
    BitShiftOperatorLowPriorityRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("bit shift operator low priority", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(BitShiftOperatorLowPriorityRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new BitShiftOperatorLowPriorityRule(), 
            "void m(){int a,b;a=(1<<b)*2;}");
    testRuleOnCXXCode(new BitShiftOperatorLowPriorityRule(), 
            "void m(){int a,b;a=b+(1<<b);}");
}

TEST(BitShiftOperatorLowPriorityRuleTest, Test1)
{
         
    testRuleOnCXXCode(new BitShiftOperatorLowPriorityRule(), 
            "void m(){\n"
            "int a,b;a=\n1<<b*2;}",0, 3, 1, 3, 6, "The priority of the '*' operation is higher than that of the '<<' operation. It's possible that parentheses should be used in the expression.");
}

TEST(BitShiftOperatorLowPriorityRuleTest, Test2)
{
         
    testRuleOnCXXCode(new BitShiftOperatorLowPriorityRule(), 
            "void m(){\n"
            "int a,b;a=\n2+1>>b;}",0, 3, 1, 3, 6, "The priority of the '+' operation is higher than that of the '>>' operation. It's possible that parentheses should be used in the expression.");
}
