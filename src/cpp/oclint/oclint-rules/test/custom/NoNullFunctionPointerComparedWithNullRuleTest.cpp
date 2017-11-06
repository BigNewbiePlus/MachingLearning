#include "TestRuleOnCode.h"
#include "rules/custom/NoNullFunctionPointerComparedWithNullRule.cpp"

TEST(NoNullFunctionPointerComparedWithNullRuleTest, PropertyTest)
{
    NoNullFunctionPointerComparedWithNullRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("no null function pointer compared with null", rule.name());
    EXPECT_EQ("custom", rule.category());
}


TEST(NoNullFunctionPointerComparedWithNullRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new NoNullFunctionPointerComparedWithNullRule(), 
                   "#include<stdio.h>\n"    
                   "int getCount(){return 1;}\n"
                   "int main(){\n"
                   "if(getCount()){}\n"
                   "return 0;"
                   "}");
}

TEST(NoNullFunctionPointerComparedWithNullRuleTest, Test1)
{
         
    testRuleOnCode(new NoNullFunctionPointerComparedWithNullRule(),                     
                   "#include<stdio.h>\n"    
                   "int getCount(){return 1;}\n"
                   "int main(){\n"
                   "if(getCount){}\n"
                   "return 0;"
                   "}",
            0, 4, 4, 4, 4, "Consider inspecting an odd expression. Non-null function pointer is compared to null: 'getCount'");
}

TEST(NoNullFunctionPointerComparedWithNullRuleTest, Test2)
{
         
    testRuleOnCode(new NoNullFunctionPointerComparedWithNullRule(),                     
                   "#include<stdio.h>\n"    
                   "int getCount(){return 1;}\n"
                   "int main(){\n"
                   "if(!getCount){}\n"
                   "return 0;"
                   "}",
            0, 4, 5, 4, 5, "Consider inspecting an odd expression. Non-null function pointer is compared to null: 'getCount'");
}

TEST(NoNullFunctionPointerComparedWithNullRuleTest, Test3)
{
         
    testRuleOnCode(new NoNullFunctionPointerComparedWithNullRule(),                     
                   "#include<stdio.h>\n"    
                   "int getCount(){return 1;}\n"
                   "int main(){\n"
                   "if(getCount==0){}\n"
                   "return 0;"
                   "}",
            0, 4, 4, 4, 14, "Consider inspecting an odd expression. Non-null function pointer is compared to null: 'getCount==0'");
}

TEST(NoNullFunctionPointerComparedWithNullRuleTest, Test4)
{
         
    testRuleOnCode(new NoNullFunctionPointerComparedWithNullRule(),                     
                   "#include<stdio.h>\n"    
                   "int getCount(){return 1;}\n"
                   "int main(){\n"
                   "if(getCount==NULL){}\n"
                   "return 0;"
                   "}",
            0, 4, 4, 4, 14, "Consider inspecting an odd expression. Non-null function pointer is compared to null: 'getCount==NULL'");
}

