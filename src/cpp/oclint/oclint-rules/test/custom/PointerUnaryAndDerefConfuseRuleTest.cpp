#include "TestRuleOnCode.h"
#include "rules/custom/PointerUnaryAndDerefConfuseRule.cpp"

TEST(PointerUnaryAndDerefConfuseRuleTest, PropertyTest)
{
    PointerUnaryAndDerefConfuseRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("pointer unary and deref confuse", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(PointerUnaryAndDerefConfuseRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new PointerUnaryAndDerefConfuseRule(), "void m(){int* a;if(a){*(a++);}}");
    testRuleOnCode(new PointerUnaryAndDerefConfuseRule(), "void m(){int* a;if(a){(*a)++;}}");
}

TEST(PointerUnaryAndDerefConfuseRuleTest, Test1)
{
         
    testRuleOnCode(new PointerUnaryAndDerefConfuseRule(),                     
                       "void m(){int* a;if(a){\n*a++;}}",
            0, 2, 2, 2, 3, "Consider inspecting the statement of '*pointer++' pattern. Probably meant: '(*pointer)++'.");
}

TEST(PointerUnaryAndDerefConfuseRuleTest, Test2)
{
         
    testRuleOnCode(new PointerUnaryAndDerefConfuseRule(),                     
                       "void m(){int* a;if(a){\n*a--;}}",
            0, 2, 2, 2, 3, "Consider inspecting the statement of '*pointer++' pattern. Probably meant: '(*pointer)++'.");
}
