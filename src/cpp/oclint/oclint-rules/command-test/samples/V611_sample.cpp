class Teacher{
public:
    int age;
    void setAge(int age){}
};

int main()
{
    int a=0, b=1;
    int* ptr = new int;
    ptr = new int;
    int* myarray = new int[10];
    myarray = new int[10];

    Teacher* teachers = new Teacher[10];

    delete ptr;
    delete []myarray;
    delete []teachers;

    delete myarray;
    delete teachers;
    
    return 0;
}
