#include "TestRuleOnCode.h"
#include "rules/custom2/ImplicitlyCastFromIntegerToRealTypeRule.cpp"

TEST(ImplicitlyCastFromIntegerToRealTypeRuleTest, PropertyTest)
{
    ImplicitlyCastFromIntegerToRealTypeRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("implicitly cast from integer to real type", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(ImplicitlyCastFromIntegerToRealTypeRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new ImplicitlyCastFromIntegerToRealTypeRule(), 
            "void m(){double a,b;a=b*2;}");
    testRuleOnCXXCode(new ImplicitlyCastFromIntegerToRealTypeRule(), 
            "void m(){int a,b;a=a*b;}");
}

TEST(ImplicitlyCastFromIntegerToRealTypeRuleTest, Test1)
{
         
    testRuleOnCXXCode(new ImplicitlyCastFromIntegerToRealTypeRule(), 
            "void m(){\n"
            "int a,b;double d=\na/b;}",0, 3, 1, 3, 3, "The 'a/b' expression was implicitly cast from 'int' type to 'double' type. Consider utilizing an explicit type cast to avoid the loss of a fractional part. An example: double A = (double)(X) / Y;");
}

TEST(ImplicitlyCastFromIntegerToRealTypeRuleTest, Test2)
{
         
    testRuleOnCXXCode(new ImplicitlyCastFromIntegerToRealTypeRule(), 
            "void m(){\n"
            "int a,b;double c;c=\n(a/b);}",0, 3, 1, 3, 5, "The 'a/b' expression was implicitly cast from 'int' type to 'double' type. Consider utilizing an explicit type cast to avoid the loss of a fractional part. An example: double A = (double)(X) / Y;");
}
