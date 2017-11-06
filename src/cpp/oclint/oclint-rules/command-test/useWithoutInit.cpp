int foo(int& p1, int p2, int p3)
{
 
    (a1+a2)*a3+foo(p1,p2,12)*12; //binary expr
    
    int a1, a2 = expr, a3; //decl
    a1=a2=a3=expr; //assign binary expr
    a+=c,b+=c,a++,b--; //binary operator=compoundAssign + unaryOperator

    if(a1>(a2+foo(a3)))//compare binary operator
    {
        block;
    }
    while(compare expr){
        block;
    }
    do{
        block;   
    }
    while(compare expr);
    for(decl or assign binary expr;compare expr;){
        block;   
    }
    return 1;
}

int main(){
    int a,b;
    foo(a,b,12);
}
