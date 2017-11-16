typedef struct person{
    int age;
}Person;

class Teacher{
public:
    int age;
    void setAge(int age){}
};

int main()
{
    int* a;
    Person* lily, tom;
    Teacher* lu, fang;
    lily->age;
    tom.age;
    lu->age;
    fang.age;
    
    *a;
    *lily;
    *lu;

    int age;
    age = tom.age;
    fang.setAge(10);
    return 0;
}
