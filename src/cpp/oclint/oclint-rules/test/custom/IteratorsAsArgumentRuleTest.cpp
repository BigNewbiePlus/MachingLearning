#include "TestRuleOnCode.h"
#include "rules/custom/IteratorsAsArgumentRule.cpp"

TEST(IteratorsAsArgumentRuleTest, PropertyTest)
{
    IteratorsAsArgumentRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("iterators as argument", rule.name());
    EXPECT_EQ("custom", rule.category());
}


TEST(IteratorsAsArgumentRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new IteratorsAsArgumentRule(), 
                      "#include<vector>\n"
                      "using namespace std;\n"
                      "void test(int a){}\n"
                      "void foo(){vector<int> a;test(*a.begin());}\n");
}

TEST(IteratorsAsArgumentRuleTest, Test1)
{
         
    testRuleOnCXXCode(new IteratorsAsArgumentRule(),                     
                      "#include<vector>\n"
                      "using namespace std;\n"
                      "void test(vector<int>::iterator it){}\n"
                      "void foo(){vector<int> a;\ntest(a.begin());}\n",
            0, 5, 1, 5, 15, "Consider inspecting iterators which are being passed as arguments to function 'test'." );
}

TEST(IteratorsAsArgumentRuleTest, Test2)
{
         
    testRuleOnCXXCode(new IteratorsAsArgumentRule(),                     
                      "#include<vector>\n"
                      "using namespace std;\n"
                      "void test(vector<int>::iterator it){}\n"
                      "void foo(){vector<int> a;\ntest(a.begin()+1);}\n",
            0, 5, 1, 5, 17, "Consider inspecting iterators which are being passed as arguments to function 'test'." );
}

TEST(IteratorsAsArgumentRuleTest, Test3)
{
         
    testRuleOnCXXCode(new IteratorsAsArgumentRule(),                     
                      "#include<vector>\n"
                      "using namespace std;\n"
                      "void test(vector<int>::iterator it){}\n"
                      "void foo(){vector<int> a;\na.erase(a.begin()+1);}\n",
            0, 5, 1, 5, 20, "Consider inspecting iterators which are being passed as arguments to function 'erase'." );
}
