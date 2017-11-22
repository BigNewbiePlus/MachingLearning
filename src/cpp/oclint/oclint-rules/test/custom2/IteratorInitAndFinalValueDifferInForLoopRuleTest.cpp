#include "TestRuleOnCode.h"
#include "rules/custom2/IteratorInitAndFinalValueDifferInForLoopRule.cpp"

TEST(IteratorInitAndFinalValueDifferInForLoopRuleTest, PropertyTest)
{
    IteratorInitAndFinalValueDifferInForLoopRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("iterator init and final value differ in for loop", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(IteratorInitAndFinalValueDifferInForLoopRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new IteratorInitAndFinalValueDifferInForLoopRule(), 
            "#include<vector>\n"
            "using namespace std;"
            "void m(){vector<int> a;for(vector<int>::iterator it=a.begin();it!=a.end();it++){}}");
}

TEST(IteratorInitAndFinalValueDifferInForLoopRuleTest, Test1)
{
         
    testRuleOnCXXCode(new IteratorInitAndFinalValueDifferInForLoopRule(), 
            "#include<vector>\n"
            "using namespace std;"
            "void m(){\n"
            "vector<int> a,b;\nfor(vector<int>::iterator it=a.begin();it!=b.end();it++){}}",0, 4, 1, 4, 58, "Consider inspecting the loop expression. Different containers are utilized for setting up initial and final values of the iterator.");
}

TEST(IteratorInitAndFinalValueDifferInForLoopRuleTest, Test2)
{
         
    testRuleOnCXXCode(new IteratorInitAndFinalValueDifferInForLoopRule(), 
            "#include<vector>\n"
            "using namespace std;"
            "void m(){\n"
            "vector<int> a,b;vector<int>::iterator it;\nfor(it=a.begin();it!=b.end();it++){}}",0, 4, 1, 4, 36, "Consider inspecting the loop expression. Different containers are utilized for setting up initial and final values of the iterator.");
}

