#include "TestRuleOnCode.h"
#include "rules/custom2/IncompatibleMemoryAllocationAndDeallocationMethodRule.cpp"

TEST(IncompatibleMemoryAllocationAndDeallocationMethodRuleTest, PropertyTest)
{
    IncompatibleMemoryAllocationAndDeallocationMethodRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("incompatible memory allocation and deallocation method", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(IncompatibleMemoryAllocationAndDeallocationMethodRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new IncompatibleMemoryAllocationAndDeallocationMethodRule(), 
            "void m(){int* a = new int; delete a;}");
    testRuleOnCXXCode(new IncompatibleMemoryAllocationAndDeallocationMethodRule(), 
            "void m(){int* a = new int[10]; delete []a;}");
    testRuleOnCXXCode(new IncompatibleMemoryAllocationAndDeallocationMethodRule(),
            "class person{public:void setAge(){}};\n"
            "void m(){person* persons = new person[10];delete []persons;}");
}
TEST(IncompatibleMemoryAllocationAndDeallocationMethodRuleTest, Test1)
{
         
    testRuleOnCXXCode(new IncompatibleMemoryAllocationAndDeallocationMethodRule(),
            "class person{public:int age;};"
            "void m(){\n"
            "int* a=new int[10];\ndelete a;}",0, 3, 1, 3, 8, "The memory was allocated using 'new T[]' operator but was released using the 'delete' operator. Consider inspecting this code. It's probably better to use 'delete []a;'.");
}

TEST(IncompatibleMemoryAllocationAndDeallocationMethodRuleTest, Test2)
{
         
    testRuleOnCXXCode(new IncompatibleMemoryAllocationAndDeallocationMethodRule(),
            "class person{public:int age;};"
            "void m(){\n"
            "person* persons = new person[10];\ndelete persons;}",0, 3, 1, 3, 8, "The memory was allocated using 'new T[]' operator but was released using the 'delete' operator. Consider inspecting this code. It's probably better to use 'delete []persons;'.");
}

TEST(IncompatibleMemoryAllocationAndDeallocationMethodRuleTest, Test3)
{
         
    testRuleOnCXXCode(new IncompatibleMemoryAllocationAndDeallocationMethodRule(),
            "class person{public:int age;};"
            "void m(){\n"
            "person* persons;persons = new person[10];\ndelete persons;}",0, 3, 1, 3, 8, "The memory was allocated using 'new T[]' operator but was released using the 'delete' operator. Consider inspecting this code. It's probably better to use 'delete []persons;'.");
}
