#include "TestRuleOnCode.h"
#include "rules/custom2/TwoIfStmtWithIdenticalCondtionRule.cpp"

TEST(TwoIfStmtWithIdenticalCondtionRuleTest, PropertyTest)
{
    TwoIfStmtWithIdenticalCondtionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("two if stmt with identical condtion", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(TwoIfStmtWithIdenticalCondtionRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new TwoIfStmtWithIdenticalCondtionRule(), 
            "void m(){int a,b;if(a>0){}\nif(a<0){}}");
    testRuleOnCXXCode(new TwoIfStmtWithIdenticalCondtionRule(), 
            "void m(){int a,b;if(a>0){}\nif(a>0){}}");
}

TEST(TwoIfStmtWithIdenticalCondtionRuleTest, test1)
{
         
    testRuleOnCXXCode(new TwoIfStmtWithIdenticalCondtionRule(), 
            "int m(){int a;if(a>0)return 1;if(a<0){}\nif(a>0){}return 0;"
            "}",0, 2, 1, 2, 9, "There are two 'if' statements with identical conditional expressions. The first 'if' statement contains function return. This means that the second 'if' statement is senseless.");
}

TEST(TwoIfStmtWithIdenticalCondtionRuleTest, test2)
{
         
    testRuleOnCXXCode(new TwoIfStmtWithIdenticalCondtionRule(), 
            "int m(){int a;if(a>0){return 1;}if(a<0){}\nif(a>0){}return 0;"
            "}",0, 2, 1, 2, 9, "There are two 'if' statements with identical conditional expressions. The first 'if' statement contains function return. This means that the second 'if' statement is senseless.");
}

TEST(TwoIfStmtWithIdenticalCondtionRuleTest, test3)
{
         
    testRuleOnCXXCode(new TwoIfStmtWithIdenticalCondtionRule(), 
            "int m(){int a;if(a>0){}if(a<0){return 1;}if(a>0){}\nif(a<0){}return 0;"
            "}",0, 2, 1, 2, 9, "There are two 'if' statements with identical conditional expressions. The first 'if' statement contains function return. This means that the second 'if' statement is senseless.");
}
