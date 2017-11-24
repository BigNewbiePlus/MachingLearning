#include "TestRuleOnCode.h"
#include "rules/custom2/UnaryMinusCanntModifyBoolValueRule.cpp"

TEST(UnaryMinusCanntModifyBoolValueRuleTest, PropertyTest)
{
    UnaryMinusCanntModifyBoolValueRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("unary minus cannt modify bool value", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(UnaryMinusCanntModifyBoolValueRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new UnaryMinusCanntModifyBoolValueRule(), 
            "void m(){bool a,b;a=b;}");
}

TEST(UnaryMinusCanntModifyBoolValueRuleTest, Test1)
{
         
    testRuleOnCXXCode(new UnaryMinusCanntModifyBoolValueRule(), 
            "void m(){\n"
            "bool a,b;\na=-b;}",0, 3, 1, 3, 4, "Unary minus operator does not modify a bool type variable. Consider using the '!' operator.");
}
