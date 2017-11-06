#include "TestRuleOnCode.h"
#include "rules/custom/DifferentEnumComparisonRule.cpp"

TEST(DifferentEnumComparisonRuleTest, PropertyTest)
{
    DifferentEnumComparisonRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("different enum comparison", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(DifferentEnumComparisonRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new DifferentEnumComparisonRule(),
                   "enum EHAlign { Left, Middle , Right  };"
                   "enum EVAlign { Top, Center , Bottom };"
                   "void m(){EHAlign enuHAlign;if(\nenuHAlign == Left){}}");
    
    testRuleOnCXXCode(new DifferentEnumComparisonRule(),
                   "enum EHAlign { Left, Middle , Right  };"
                   "enum EVAlign { Top, Center , Bottom };"
                   "void m(){EHAlign enuHAlign; switch(enuHAlign){case Middle:{ int a=0;}break;case Left:{int b=0;}break;default:break;}}");
}

TEST(DifferentEnumComparisonRuleTest, Test1)
{
         
    testRuleOnCXXCode(new DifferentEnumComparisonRule(),                     
                      "enum EHAlign { Left, Middle , Right  };"
                   "enum EVAlign { Top, Center , Bottom };"
                   "void m(){EHAlign enuHAlign;if(\nenuHAlign != Center){}}",
            0, 2, 1, 2, 14, "The values of different enum types are compared: enuHAlign != Center.");
}

TEST(DifferentEnumComparisonRuleTest, Test2)
{
         
    testRuleOnCXXCode(new DifferentEnumComparisonRule(),                     
                      "enum EHAlign { Left, Middle , Right  };"
                   "enum EVAlign { Top, Center , Bottom };"
                   "void m(){EHAlign enuHAlign; switch(enuHAlign){\ncase Center:{ int a=0;}break;case Left:{int b=0;}break;default:break;}}",
            0, 2, 1, 2, 23, "The values of different enum types are compared: switch(ENUM_TYPE_A) { case ENUM_TYPE_B: ... }.");
}
