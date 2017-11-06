#include "TestRuleOnCode.h"
#include "rules/custom/ArgumentOfSizeofIsExpressionRule.cpp"

TEST(ArgumentOfSizeofIsExpressionRuleTest, PropertyTest)
{
    ArgumentOfSizeofIsExpressionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("argument of sizeof is expression", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(ArgumentOfSizeofIsExpressionRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new ArgumentOfSizeofIsExpressionRule(), "void m(){int A;int size= sizeof(A);}");
    testRuleOnCXXCode(new ArgumentOfSizeofIsExpressionRule(), "void m(){char* buff;int result = sizeof(*buff)-1;}");
    testRuleOnCXXCode(new ArgumentOfSizeofIsExpressionRule(), 
                      "typedef struct person{}Person;"
                      "void m(){Person* person;sizeof(*person);}");
    testRuleOnCXXCode(new ArgumentOfSizeofIsExpressionRule(), 
                      "class Animal{public:int size(){return sizeof(*this);}};"
                      "void m(){Animal* animal;sizeof(*animal);}");
}

TEST(ArgumentOfSizeofIsExpressionRuleTest, Test1)
{
         
    testRuleOnCXXCode(new ArgumentOfSizeofIsExpressionRule(),                     
                      "void m(){int A;int size= \nsizeof(A++);}",
            0, 2, 1, 2, 11, "It's odd that the argument of sizeof() operator is the 'A++' expression.");
}



TEST(ArgumentOfSizeofIsExpressionRuleTest, Test2)
{
         
    testRuleOnCXXCode(new ArgumentOfSizeofIsExpressionRule(),                     
                      "void m(){char* buff;int result = \nsizeof(buff-1);}",
            0, 2, 1, 2, 14, "It's odd that the argument of sizeof() operator is the 'buff-1' expression.");
}

TEST(ArgumentOfSizeofIsExpressionRuleTest, Test3)
{
         
    testRuleOnCXXCode(new ArgumentOfSizeofIsExpressionRule(),                     
                      "typedef struct person{}Person;"
                      "void m(){Person* person;\nsizeof(person);}",
            0, 2, 1, 2, 14, "It's odd that the argument of sizeof() operator is the 'person' expression.");
}
TEST(ArgumentOfSizeofIsExpressionRuleTest, Test4)
{
         
    testRuleOnCXXCode(new ArgumentOfSizeofIsExpressionRule(),                     
                      "class Animal{public:int size(){return sizeof(*this);}};"
                      "void m(){Animal* animal;\nsizeof(animal);}",
            0, 2, 1, 2, 14, "It's odd that the argument of sizeof() operator is the 'animal' expression.");
}

TEST(ArgumentOfSizeofIsExpressionRuleTest, Test5)
{
         
    testRuleOnCXXCode(new ArgumentOfSizeofIsExpressionRule(),                     
                      "class Animal{public:int size(){return \nsizeof(this);}};"
                      "void m(){Animal* animal;\nsizeof(*animal);}",
            0, 2, 1, 2, 12, "It's odd that the argument of sizeof() operator is the 'this' expression.");
}
