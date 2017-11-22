#include "TestRuleOnCode.h"
#include "rules/custom2/NoSenseTestPointerAgainstNullAsMemAlloUseNewRule.cpp"

TEST(NoSenseTestPointerAgainstNullAsMemAlloUseNewRuleTest, PropertyTest)
{
    NoSenseTestPointerAgainstNullAsMemAlloUseNewRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("no sense test pointer against null as mem allo use new", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(NoSenseTestPointerAgainstNullAsMemAlloUseNewRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new NoSenseTestPointerAgainstNullAsMemAlloUseNewRule(), 
            "#include<iostream>\nusing namespace std;"
            "void m(){int *a;if(a==NULL){}}");
}

TEST(NoSenseTestPointerAgainstNullAsMemAlloUseNewRuleTest, Test1)
{
         
    testRuleOnCXXCode(new NoSenseTestPointerAgainstNullAsMemAlloUseNewRule(), 
            "#include<iostream>\nusing namespace std;"
            "void m(){\n"
            "int *a=new int[10];\nif(a){}}",0, 4, 1, 4, 7, "There is no sense in testing the 'a' pointer against null, as the memory was allocated using the 'new' operator. The exception will be generated in the case of memory allocation error.");
}

TEST(NoSenseTestPointerAgainstNullAsMemAlloUseNewRuleTest, Test2)
{
         
    testRuleOnCXXCode(new NoSenseTestPointerAgainstNullAsMemAlloUseNewRule(), 
            "#include<iostream>\nusing namespace std;"
            "void m(){\n"
            "int *a; a=new int[10];\nif(a){}}",0, 4, 1, 4, 7, "There is no sense in testing the 'a' pointer against null, as the memory was allocated using the 'new' operator. The exception will be generated in the case of memory allocation error.");
}
TEST(NoSenseTestPointerAgainstNullAsMemAlloUseNewRuleTest, Test3)
{
         
    testRuleOnCXXCode(new NoSenseTestPointerAgainstNullAsMemAlloUseNewRule(), 
            "#include<iostream>\nusing namespace std;"
            "class person{};"
            "void m(){\n"
            "person* lily = new person();\nif(person!=NULL){}}",0, 4, 1, 4, 15,"There is no sense in testing the 'lily' pointer against null, as the memory was allocated using the 'new' operator. The exception will be generated in the case of memory allocation error.");
}
