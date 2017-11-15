#include "TestRuleOnCode.h"
#include "rules/custom2/IdenticalAlongsideIfConditionRule.cpp"

TEST(IdenticalAlongsideIfConditionRuleTest, PropertyTest)
{
    IdenticalAlongsideIfConditionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("identical alongside if condition", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(IdenticalAlongsideIfConditionRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new IdenticalAlongsideIfConditionRule(),
            "void m(){int a;if(a>0){}if(a<0){}}");
    testRuleOnCXXCode(new IdenticalAlongsideIfConditionRule(), 
            "void m(){int a;if(a>0&&a<123){}if(a>0){}}");
}

TEST(IdenticalAlongsideIfConditionRuleTest, Test1)
{
         
    testRuleOnCXXCode(new IdenticalAlongsideIfConditionRule(), 
            "void m(){int a;\n"
            "if(a>10){}\nif(a>10){};}",0, 3, 1, 3, 10, "The conditional expressions of the 'if' operators situated alongside each other are identical.");
}

TEST(IdenticalAlongsideIfConditionRuleTest, Test2)
{
         
    testRuleOnCXXCode(new IdenticalAlongsideIfConditionRule(), 
            "void m(){int a;\n"
            "if(a>10){}\nif(a < 10){}\nif(a>10){};}",0, 4, 1, 4, 10, "The conditional expressions of the 'if' operators situated alongside each other are identical.");
}
