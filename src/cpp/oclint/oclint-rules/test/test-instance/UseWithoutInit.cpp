//            未赋值先使用
//基本数据类型： T：char, int, float, double,bool, void, wchar_t
//修饰       ：signed, unsigned, short, long

//exmaple 1:
T foo1(){return T;}
void foo2(T t){T a=t,b;b=t;}
void foo3(T& t){t = Instance(T);T a=t;}

void main()
{
    T a, b, c;
    T d = a or Instance(T) or foo1() or 混合;
    a=b=c=d or Instance(T) or foo1() or 混合;
    
    foo2(a);//未传引用，赋值或使用
    foo3(b);//传引用， 赋值或被赋值
}


