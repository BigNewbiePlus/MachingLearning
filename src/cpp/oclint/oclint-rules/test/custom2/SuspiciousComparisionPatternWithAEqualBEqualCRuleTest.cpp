#include "TestRuleOnCode.h"
#include "rules/custom2/SuspiciousComparisionPatternWithAEqualBEqualCRule.cpp"

TEST(SuspiciousComparisionPatternWithAEqualBEqualCRuleTest, PropertyTest)
{
    SuspiciousComparisionPatternWithAEqualBEqualCRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("suspicious comparision pattern with a equal b equal c", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(SuspiciousComparisionPatternWithAEqualBEqualCRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new SuspiciousComparisionPatternWithAEqualBEqualCRule(), 
            "class person{public: int age;};void m(){int a,b,c;if(a==b && a==c){}}");
}

TEST(SuspiciousComparisionPatternWithAEqualBEqualCRuleTest, Test1)
{
         
    testRuleOnCXXCode(new SuspiciousComparisionPatternWithAEqualBEqualCRule(), 
            "class person{public: int age;};void m(){person p1,p2,p3; \n"
            "if(p1.age==p2.age==p3.age){}}",0, 2, 4, 2, 23, "Suspicious comparison found: 'a == b == c'. Remember that 'a == b == c' is not equal to 'a == b && b == c'.");
}

TEST(SuspiciousComparisionPatternWithAEqualBEqualCRuleTest, Test2)
{
         
    testRuleOnCXXCode(new SuspiciousComparisionPatternWithAEqualBEqualCRule(), 
            "typedef struct Person{int age;}person;void m(){person p1,p2,p3; \n"
            "if(p1.age==p2.age==p3.age){}}",0, 2, 4, 2, 23, "Suspicious comparison found: 'a == b == c'. Remember that 'a == b == c' is not equal to 'a == b && b == c'.");
}

TEST(SuspiciousComparisionPatternWithAEqualBEqualCRuleTest, Test3)
{
         
    testRuleOnCXXCode(new SuspiciousComparisionPatternWithAEqualBEqualCRule(), 
            "typedef struct Person{int age;}person;void m(){int p1,p2,p3; \n"
            "if(p1==p2==p3){}}",0, 2, 4, 2, 12, "Suspicious comparison found: 'a == b == c'. Remember that 'a == b == c' is not equal to 'a == b && b == c'.");
}

