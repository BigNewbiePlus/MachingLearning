#include "TestRuleOnCode.h"
#include "rules/custom2/OperationLogicNotCorrespondWithItsFormatRule.cpp"

TEST(OperationLogicNotCorrespondWithItsFormatRuleTest, PropertyTest)
{
    OperationLogicNotCorrespondWithItsFormatRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("operation logic not correspond with its format", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(OperationLogicNotCorrespondWithItsFormatRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new OperationLogicNotCorrespondWithItsFormatRule(), 
            "void m(){int a,b;"
            "   if(a)a=1;\n"
            "   b=2;"
            "}");
}

TEST(OperationLogicNotCorrespondWithItsFormatRuleTest, Test1)
{
         
    testRuleOnCXXCode(new OperationLogicNotCorrespondWithItsFormatRule(), 
            "void m(){\n"
            "   int a,b;\n"
            "   if(a>0)\n"
            "       a=1;b=2;\n"
            "\n}",0, 3, 4, 4, 10, "The code's operational logic does not correspond with its formatting. The statement is indented to the right, but it is always executed. It is possible that curly brackets are missing.");
}
TEST(OperationLogicNotCorrespondWithItsFormatRuleTest, Test2)
{
         
    testRuleOnCXXCode(new OperationLogicNotCorrespondWithItsFormatRule(), 
            "void m(){\n"
            "   int a,b;\n"
            "   if(a>0)\n"
            "       a=1;\n"
            "       b=2;\n"
            "\n}",0, 3, 4, 4, 10, "The code's operational logic does not correspond with its formatting. The statement is indented to the right, but it is always executed. It is possible that curly brackets are missing.");
}
TEST(OperationLogicNotCorrespondWithItsFormatRuleTest, Test3)
{
         
    testRuleOnCXXCode(new OperationLogicNotCorrespondWithItsFormatRule(), 
            "void m(){\n"
            "   int a,b;\n"
            "while(a>0){\n"
            "   if(a>0)\n"
            "       a=1;break;\n"
            "}"
            "\n}",0, 4, 4, 5, 10, "The code's operational logic does not correspond with its formatting. The statement is indented to the right, but it is always executed. It is possible that curly brackets are missing.");
}
