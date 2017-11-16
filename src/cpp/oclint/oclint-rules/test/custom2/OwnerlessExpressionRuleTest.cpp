#include "TestRuleOnCode.h"
#include "rules/custom2/OwnerlessExpressionRule.cpp"

TEST(OwnerlessExpressionRuleTest, PropertyTest)
{
    OwnerlessExpressionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("ownerless expression", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(OwnerlessExpressionRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new OwnerlessExpressionRule(), 
            "void m(){int a; a=10;}");
    testRuleOnCXXCode(new OwnerlessExpressionRule(),
            "class person{public:void setAge(){}};\n"
            "void m(){person lily;lily.setAge();}");
}

TEST(OwnerlessExpressionRuleTest, Test1)
{
         
    testRuleOnCXXCode(new OwnerlessExpressionRule(),
            "class person{public:int age;};"
            "void m(){\n"
            "person lily;\nlily.age;}",0, 3, 1, 3, 6, "Ownerless expression 'lily.age'.");
}

TEST(OwnerlessExpressionRuleTest, Test2)
{
         
    testRuleOnCXXCode(new OwnerlessExpressionRule(),
            "class person{public:int age;};"
            "void m(){\n"
            "person* lily;\nlily->age;}",0, 3, 1, 3, 7, "Ownerless expression 'lily->age'.");
}

TEST(OwnerlessExpressionRuleTest, Test3)
{
         
    testRuleOnCXXCode(new OwnerlessExpressionRule(),
            "class person{public:int age;};"
            "void m(){\n"
            "person* lily;\n*lily;}",0, 3, 1, 3, 2, "Ownerless expression '*lily'.");
}
