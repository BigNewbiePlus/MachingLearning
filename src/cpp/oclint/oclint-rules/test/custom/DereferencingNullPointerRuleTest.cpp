#include "TestRuleOnCode.h"
#include "rules/custom/DereferencingNullPointerRule.cpp"

TEST(DereferencingNullPointerRuleTest, PropertyTest)
{
    DereferencingNullPointerRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("dereferencing null pointer", rule.name());
    EXPECT_EQ("custom", rule.category());
}


TEST(DereferencingNullPointerRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new DereferencingNullPointerRule(),
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   "#define bool int\n"
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "Pointer* pointer;\n"
                   "if (pointer != 0 && pointer->m_a) {}"
                   "}");
    testRuleOnCXXCode(new DereferencingNullPointerRule(),
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "Pointer* pointer;\n"
                   "if (pointer == 0 || pointer->m_a) {}"
                   "}");
    testRuleOnCXXCode(new DereferencingNullPointerRule(),
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "Pointer* pointer;\n"
                   "if (!pointer || pointer->m_a) {}"
                   "}");
    testRuleOnCXXCode(new DereferencingNullPointerRule(),
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "int array[10];\n"
                   "if (array != 0 && array[3]) {}"
                   "}");
    testRuleOnCXXCode(new DereferencingNullPointerRule(),
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "int* a;\n"
                   "if (a != 0 && *a) {}"
                   "}");
    testRuleOnCXXCode(new DereferencingNullPointerRule(),
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "int* DI;\n"
                   "if (DI) {printf(\"%d\",*DI);}"
                   "}");
    testRuleOnCXXCode(new DereferencingNullPointerRule(),
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "int* DI;\n"
                   "if (!DI) {}else printf(\"%d\",*DI);"
                   "}");
}

TEST(DereferencingNullPointerRuleTest, Test1)
{
         
    testRuleOnCXXCode(new DereferencingNullPointerRule(),                     
                      "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "struct Pointer* pointer;\n"
                   "if(pointer != 0 || pointer->m_a) {}"
                   "}",
            0, 9, 4, 9, 29, "Dereferencing of the null pointer 'pointer' might take place. Check the logical condition.");
}

TEST(DereferencingNullPointerRuleTest, Test2)
{
         
    testRuleOnCXXCode(new DereferencingNullPointerRule(),                     
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "struct Pointer* pointer;\n"
                   "if(pointer == 0 && pointer->m_a) {}"
                   "}",
            0, 9, 4, 9, 29, "Dereferencing of the null pointer 'pointer' might take place. Check the logical condition.");
}

TEST(DereferencingNullPointerRuleTest, Test3)
{
         
    testRuleOnCXXCode(new DereferencingNullPointerRule(),                     
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "struct Pointer* pointer;\n"
                   "if(!pointer && pointer->m_a) {}"
                   "}",
            0, 9, 4, 9, 25, "Dereferencing of the null pointer 'pointer' might take place. Check the logical condition.");
}

TEST(DereferencingNullPointerRuleTest, Test4)
{
         
    testRuleOnCXXCode(new DereferencingNullPointerRule(),                     
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "int array[10];\n"
                   "if(array == 0 && array[3]) {}"
                   "}",
            0, 9, 4, 9, 25, "Dereferencing of the null pointer 'array' might take place. Check the logical condition.");
}

TEST(DereferencingNullPointerRuleTest, Test5)
{
         
    testRuleOnCXXCode(new DereferencingNullPointerRule(),                     
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                  
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "int* a;\n"
                   "if(a == 0 && *a) {}"
                   "}",
            0, 9, 4, 9, 15, "Dereferencing of the null pointer 'a' might take place. Check the logical condition.");
}


TEST(DereferencingNullPointerRuleTest, Test6)
{
         
    testRuleOnCXXCode(new DereferencingNullPointerRule(),                     
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                      
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "int* DI;\n"
                   "if (DI==0) {printf(\"%d\",\n*DI);}"
                   "}",
            0, 10, 2, 10, 2, "Dereferencing of the null pointer 'DI' might take place. Check the logical condition.");
}


TEST(DereferencingNullPointerRuleTest, Test7)
{
         
    testRuleOnCXXCode(new DereferencingNullPointerRule(),                     
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "int* DI;\n"
                   "if (DI) {}else printf(\"%d\",\n*DI);"
                   "}",
            0, 10, 2, 10, 2, "Dereferencing of the null pointer 'DI' might take place. Check the logical condition.");
}

