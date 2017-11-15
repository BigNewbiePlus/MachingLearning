enum EHAlign { Left, Middle , Right  };
enum EVAlign { Top, Center , Bottom };

void foo()
{
    EHAlign enuHAlign;
    if(enuHAlign == Center){
    }
    
    switch(enuHAlign){
        case Center:{ int a=0;}
            break;
        case Left:{int b=0;}
            break;
        default:
            break;
    }
}
int main()
{   
    return 0;
}
