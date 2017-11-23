#include "TestRuleOnCode.h"
#include "rules/custom2/CompareThisWithNULLShouldBeAvoidRule.cpp"

TEST(CompareThisWithNULLShouldBeAvoidRuleTest, PropertyTest)
{
    CompareThisWithNULLShouldBeAvoidRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("compare this with n u l l should be avoid", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(CompareThisWithNULLShouldBeAvoidRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new CompareThisWithNULLShouldBeAvoidRule(), 
            "class person{public: int age; void getAge(){if(this->age){}}};");
}

TEST(CompareThisWithNULLShouldBeAvoidRuleTest, Test1)
{
         
    testRuleOnCXXCode(new CompareThisWithNULLShouldBeAvoidRule(), 
            "class person{public: void getAge(){if(\n!this){}}};",0, 2, 1, 2, 2, "'!this' comparison should be avoided - this comparison is always false on newer compilers.");
}

TEST(CompareThisWithNULLShouldBeAvoidRuleTest, Test2)
{
         
    testRuleOnCXXCode(new CompareThisWithNULLShouldBeAvoidRule(), 
            "class Person{public: void getAge(){if(\nthis==0){}}};"
            ,0, 2, 1, 2, 7, "'this==0' comparison should be avoided - this comparison is always false on newer compilers.");
}
