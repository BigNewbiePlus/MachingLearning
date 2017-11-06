#include "TestRuleOnCode.h"
#include "rules/custom/MemFunCallLeadOverOrUnderFlowWithSizeofRule.cpp"

TEST(MemFunCallLeadOverOrUnderFlowWithSizeofRuleTest, PropertyTest)
{
    MemFunCallLeadOverOrUnderFlowWithSizeofRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("mem fun call lead over or under flow with sizeof", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(MemFunCallLeadOverOrUnderFlowWithSizeofRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new MemFunCallLeadOverOrUnderFlowWithSizeofRule(), 
                     "#include<string.h>\n"
                      "struct unit1{};\n"
                      "void foo1(){\n"
                      "int buffer1[256];\n"
                      "memset(buffer1,0,sizeof(buffer1)); //true\n" 
                      "}");
    testRuleOnCXXCode(new MemFunCallLeadOverOrUnderFlowWithSizeofRule(), 
                     "#include<string.h>\n"
                      "struct unit1{};\n"
                      "void foo1(){\n"
                      "unit1 buffer2[256];\n"
                      "memset(buffer2,0,sizeof(buffer2)); //true\n" 
                      "}");

    testRuleOnCXXCode(new MemFunCallLeadOverOrUnderFlowWithSizeofRule(), 
                     "#include<string.h>\n"
                      "struct unit1{};\n"
                      "void foo1(){\n"
                      "int buffer1[256];\n"
                      "memset(buffer1,0,256*sizeof(int)); //true\n" 
                      "}");
    testRuleOnCXXCode(new MemFunCallLeadOverOrUnderFlowWithSizeofRule(), 
                     "#include<string.h>\n"
                      "struct unit1{};\n"
                      "void foo1(){\n"
                      "unit1* unit;\n"    
                      "memset(unit, 0, sizeof(*unit)); //true\n" 
                      "}");
    testRuleOnCXXCode(new MemFunCallLeadOverOrUnderFlowWithSizeofRule(), 
                     "#include<string.h>\n"
                      "struct unit1{};\n"
                      "void foo1(){\n"
                      "int buffer1[256];\n"
                      "int buffer3[256];\n"
                      "memcpy(buffer1,buffer3, 256*sizeof(int));//true\n " 
                      "}");  
}

TEST(MemFunCallLeadOverOrUnderFlowWithSizeofRuleTest, Test1)
{      
    
    testRuleOnCXXCode(new MemFunCallLeadOverOrUnderFlowWithSizeofRule(), 
                     "#include<string.h>\n"
                      "struct unit1{};\n"
                      "void foo1(){\n"
                      "int buffer1[256];\n"
                      "memset(buffer1,0,sizeof(*buffer1)); //wrong\n" 
                      "}", 0,5,1,5,34, "A call of the 'memset' function will lead to a buffer overflow or underflow.");
}

TEST(MemFunCallLeadOverOrUnderFlowWithSizeofRuleTest, Test2)
{      
    testRuleOnCXXCode(new MemFunCallLeadOverOrUnderFlowWithSizeofRule(), 
                     "#include<string.h>\n"
                      "struct unit1{};\n"
                      "void foo1(){\n"
                      "unit1 buffer2[256];\n"
                      "memset(buffer2,0,sizeof(*buffer2)); //wrong\n" 
                      "}", 0,5,1,5,34, "A call of the 'memset' function will lead to a buffer overflow or underflow.");
}

TEST(MemFunCallLeadOverOrUnderFlowWithSizeofRuleTest, Test3)
{      
    testRuleOnCXXCode(new MemFunCallLeadOverOrUnderFlowWithSizeofRule(), 
                     "#include<string.h>\n"
                      "struct unit1{};\n"
                      "void foo1(){\n"
                      "int buffer1[256];\n"
                      "memset(buffer1,0,256); //wrong\n" 
                      "}", 0,5,1,5,21, "A call of the 'memset' function will lead to a buffer overflow or underflow.");
}

TEST(MemFunCallLeadOverOrUnderFlowWithSizeofRuleTest, Test4)
{      
    testRuleOnCXXCode(new MemFunCallLeadOverOrUnderFlowWithSizeofRule(), 
                     "#include<string.h>\n"
                      "struct unit1{};\n"
                      "void foo1(){\n"
                      "unit1* unit;\n"    
                      "memset(unit, 0, sizeof(unit)); //wrong\n" 
                      "}", 0,5,1,5,29, "A call of the 'memset' function will lead to a buffer overflow or underflow.");
}

    
TEST(MemFunCallLeadOverOrUnderFlowWithSizeofRuleTest, Test5)
{      
        testRuleOnCXXCode(new MemFunCallLeadOverOrUnderFlowWithSizeofRule(), 
                     "#include<string.h>\n"
                      "struct unit1{};\n"
                      "void foo1(){\n"
                      "int buffer1[256];\n"
                      "int buffer3[256];\n"
                      "memcpy(buffer1,buffer3, 256);//wrong\n " 
                      "}", 0,6,1,6,28, "A call of the 'memcpy' function will lead to a buffer overflow or underflow.");


}
