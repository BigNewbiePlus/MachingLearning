#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ptrace.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
    int count=0;
    int val;
    pid_t child = fork();
    if(child==0){
        execl("./HelloWorld", "HelloWorld", NULL);
    }else{
        ptrace(PTRACE_ATTACH, child, NULL, NULL);
        while(1){
            wait(&val);
            if(WIFEXITED(val)){
                break;
            }
            count++;
            ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
        }
        printf("total instruct num:%d", count);
    }

}
