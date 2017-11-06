#include "TestRuleOnCode.h"
#include "rules/custom/EmptyExceptionHandlerRule.cpp"

TEST(EmptyExceptionHandlerRuleTest, PropertyTest)
{
    EmptyExceptionHandlerRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("empty exception handler", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(EmptyExceptionHandlerRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new EmptyExceptionHandlerRule(), 
                  "#include<iostream>\n"
                   "#include<exception>\n"
                   "using namespace std;\n"    
                   "void foo(){try{}catch(std::exception &e){cout<<\"hello world\";}}");
}

TEST(EmptyExceptionHandlerRuleTest, Test1)
{
         
    testRuleOnCXXCode(new EmptyExceptionHandlerRule(),                     
                      "#include<iostream>\n"
                   "#include<exception>\n"
                   "using namespace std;\n"    
                   "void foo(){try{}\ncatch(std::exception &e){}}",
            0, 5, 1, 5, 26, "An empty exception handler. Silent suppression of exceptions can hide the presence of bugs in source code during testing.");
}
