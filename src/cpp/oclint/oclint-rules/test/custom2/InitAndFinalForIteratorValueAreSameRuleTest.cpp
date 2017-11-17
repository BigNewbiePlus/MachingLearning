#include "TestRuleOnCode.h"
#include "rules/custom2/InitAndFinalForIteratorValueAreSameRule.cpp"

TEST(InitAndFinalForIteratorValueAreSameRuleTest, PropertyTest)
{
    InitAndFinalForIteratorValueAreSameRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("init and final for iterator value are same", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(InitAndFinalForIteratorValueAreSameRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new InitAndFinalForIteratorValueAreSameRule(),
            "void m(){for(int i=0;i<10;i++){}}");
    testRuleOnCXXCode(new InitAndFinalForIteratorValueAreSameRule(),
            "void m(){int a=2;for(a=0;a<10;a++){}}");
}


TEST(InitAndFinalForIteratorValueAreSameRuleTest, Test1)
{
         
    testRuleOnCXXCode(new InitAndFinalForIteratorValueAreSameRule(), 
            "void m(){"
            "int a; \nfor(int i=0;i<0;i++){}}",0, 2, 1, 2, 22, "Consider inspecting the 'for' operator. Initial and final values of the iterator are the same.");
}

TEST(InitAndFinalForIteratorValueAreSameRuleTest, Test2)
{
         
    testRuleOnCXXCode(new InitAndFinalForIteratorValueAreSameRule(), 
            "class person{public:int age;};\n"
            "void m(){"
            "person lily; \nfor(int i=lily.age;i< lily.age;i++){}}",0, 3, 1, 3, 37, "Consider inspecting the 'for' operator. Initial and final values of the iterator are the same.");
}

TEST(InitAndFinalForIteratorValueAreSameRuleTest, Test3)
{
         
    testRuleOnCXXCode(new InitAndFinalForIteratorValueAreSameRule(), 
            "class person{public:int age;};\n"
            "void m(){"
            "person lily;int i;\nfor(i=lily.age;i< lily.age;i++){}}",0, 3, 1, 3, 33, "Consider inspecting the 'for' operator. Initial and final values of the iterator are the same.");
}

TEST(InitAndFinalForIteratorValueAreSameRuleTest, Test4)
{
         
    testRuleOnCXXCode(new InitAndFinalForIteratorValueAreSameRule(), 
            "#include<vector>\n"
            "using namespace std;"
            "void m(){"
            "vector<int> a; \nfor(vector<int>::iterator it=a.begin();it!=a.begin();it++){}}",0, 3, 1, 3, 60, "Consider inspecting the 'for' operator. Initial and final values of the iterator are the same.");
}
