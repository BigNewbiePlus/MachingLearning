#include "TestRuleOnCode.h"
#include "rules/custom/NonSensicalPointerComparisonRule.cpp"

TEST(NonSensicalPointerComparisonRuleTest, PropertyTest)
{
    NonSensicalPointerComparisonRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("non sensical pointer comparison", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(NonSensicalPointerComparisonRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new NonSensicalPointerComparisonRule(), "void m(){int *a;if(a==0){}}");
    testRuleOnCXXCode(new NonSensicalPointerComparisonRule(), "void m(){int *a;if(a!=0){}}");
}

TEST(NonSensicalPointerComparisonRuleTest, Test1)
{
         
    testRuleOnCXXCode(new NonSensicalPointerComparisonRule(), "void m(){int *a,*b;if(a>b){}}",
            0, 1, 23, 1, 25, "NonSensicalPointerComparison!");
}

TEST(NonSensicalPointerComparisonRuleTest, Test2) 
{

    testRuleOnCXXCode(new NonSensicalPointerComparisonRule(), 
            "typedef int * INTPTR;\n"
            "void m(){INTPTR a,b;if(a>b){}}",
            0, 2, 24, 2, 26, 
                     "NonSensicalPointerComparison!");
    
}

TEST(NonSensicalPointerComparisonRuleTest, Test3) 
{

    testRuleOnCXXCode(new NonSensicalPointerComparisonRule(), 
            "void m(){int *a[10],*b;if(a[0]<=b){}}",
            0, 1, 27, 1, 33,
                     "NonSensicalPointerComparison!");
    
}
