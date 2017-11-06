#include "TestRuleOnCode.h"
#include "rules/custom/IllegalThrowWithoutInTryCatchInDestructorRule.cpp"

TEST(IllegalThrowWithoutInTryCatchInDestructorRuleTest, PropertyTest)
{
    IllegalThrowWithoutInTryCatchInDestructorRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("illegal throw without in try catch in destructor", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(IllegalThrowWithoutInTryCatchInDestructorRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new IllegalThrowWithoutInTryCatchInDestructorRule(),
                      "#include<exception>\n"
                      "class A{"
                      "public:"
                      "   ~A();"
                      "};"
                      "A::~A(){"
                      "    try{"
                      "        throw \"exception\";"
                      "    }catch(char* &e){"
                      "    }"
                      "}");
    testRuleOnCXXCode(new IllegalThrowWithoutInTryCatchInDestructorRule(), 
                      "#include<exception>\n"
                      "void m(){throw \"exception\";}");
    testRuleOnCXXCode(new IllegalThrowWithoutInTryCatchInDestructorRule(), 
                      "#include<exception>\n"
                      "void m(){try{throw \"exception\";}catch(char* &e){}}");
}

TEST(IllegalThrowWithoutInTryCatchInDestructorRuleTest, Test1)
{
         
    testRuleOnCXXCode(new IllegalThrowWithoutInTryCatchInDestructorRule(), 
                      "#include<exception>\n"
                      "class A{"
                      "public:"
                      "   ~A();"
                      "};"
                      "A::~A(){\n"
                      "throw \"exception\";"
                      "}",
            0, 3, 1, 3, 7, "The 'throw' operator inside the destructor should be placed within the try..catch block. Raising exception inside the destructor is illegal.");
}
