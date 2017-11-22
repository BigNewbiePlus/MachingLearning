#include "TestRuleOnCode.h"
#include "rules/custom2/StringsWereConcatenatedButNotUtilizedRule.cpp"

TEST(StringsWereConcatenatedButNotUtilizedRuleTest, PropertyTest)
{
    StringsWereConcatenatedButNotUtilizedRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("strings were concatenated but not utilized", rule.name());
    EXPECT_EQ("custom2", rule.category());
}


TEST(StringsWereConcatenatedButNotUtilizedRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new StringsWereConcatenatedButNotUtilizedRule(), 
            "#include<string>\n"
            "using namespace std;"
            "void m(){string a;while(a.size()){a+=\"((\";}}");
    testRuleOnCXXCode(new StringsWereConcatenatedButNotUtilizedRule(),
            "#include<string>\n"
            "using namespace std;"
            "void m(){string a,b;a=a+\"*****\";}");
}

TEST(StringsWereConcatenatedButNotUtilizedRuleTest, test1)
{
         
    testRuleOnCXXCode(new StringsWereConcatenatedButNotUtilizedRule(), 
           "#include<string>\n"
           "using namespace std;"
            "void m(){string a;\na+\"(\";"
            "}",0, 3, 1, 3, 5, "The strings were concatenated but are not utilized. Consider inspecting the expression.");
}

TEST(StringsWereConcatenatedButNotUtilizedRuleTest, test2)
{
         
    testRuleOnCXXCode(new StringsWereConcatenatedButNotUtilizedRule(), 
            "#include<string>\n"
            "using namespace std;"
            "void m(){string a,b;\nwhile(a.size()){\na+\"12\"+b+\"2323\";}"
            "}",0, 3, 1, 3, 13, "The strings were concatenated but are not utilized. Consider inspecting the expression.");
}
