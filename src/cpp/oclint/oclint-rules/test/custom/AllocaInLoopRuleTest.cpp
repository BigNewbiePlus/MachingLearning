#include "TestRuleOnCode.h"
#include "rules/custom/AllocaInLoopRule.cpp"

TEST(AllocaInLoopRuleTest, PropertyTest)
{
    AllocaInLoopRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("alloca in loop", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(AllocaInLoopRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new AllocaInLoopRule(), "void m(){for(int i=0;i<10;i++){}}");
}

TEST(AllocaInLoopRuleTest, Test1)
{
         
    testRuleOnCode(new AllocaInLoopRule(),                     
                      "#include<stdlib.h>\n"
                      "void foo(){for(int i=0;i<10;i++){\nint* a=(int*)alloca(10);}}",
            0, 3, 1, 3, 24, "The 'alloca' function is used inside the loop. This can quickly overflow stack.");
}

TEST(AllocaInLoopRuleTest, Test2)
{
         
    testRuleOnCode(new AllocaInLoopRule(),
                      "#include<stdlib.h>\n"
                      "void foo(){int c;int*a;while(c<10)\na=(int*)alloca(10);}",
            0, 3, 1, 3, 9, "The 'alloca' function is used inside the loop. This can quickly overflow stack.");
}

TEST(AllocaInLoopRuleTest, Test3)
{
         
    testRuleOnCode(new AllocaInLoopRule(),
                      "#include<stdlib.h>\n"
                      "#include<stdio.h>\n"
                      "void foo(){int i;do{\nint* a=(int*)alloca(10);}while(i<10);}",
            0, 4, 1, 4, 24, "The 'alloca' function is used inside the loop. This can quickly overflow stack.");
}
