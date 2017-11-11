#include<sys/ptrace.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/reg.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
int main()
{
    int val;
    pid_t pid;
    int flag=0;
    long syscallID;
    long returnValue;

    switch(pid=fork()){
        case -1:
            return -1;
        case 0:
            printf("child:\n");
            ptrace(PTRACE_TRACEME, 0, NULL,NULL);
            sleep(10);
            execl("./HelloWorld", "HelloWorld", NULL);
            sleep(10);
            printf("child end\n");
            break;
        default:
            printf("parent:\n");
            wait(&val);
            if(WIFEXITED(val))
                return 0;
            syscallID = ptrace(PTRACE_PEEKUSER, pid, ORIG_RAX*8, NULL);
            printf("Process executed system call ID=%ld\n", syscallID);
            ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
            while(1)
            {
                wait(&val);
                if(WIFEXITED(val))
                    return 0;
                if(flag==0){
                    syscallID = ptrace(PTRACE_PEEKUSER, pid, ORIG_RAX*8, NULL);
                    printf("Process execute system call ID=%ld ", syscallID);
                    flag=1;
                }else{
                    returnValue = ptrace(PTRACE_PEEKUSER, pid, RAX*8, NULL);
                    printf("with reture value:%ld\n", returnValue);
                    flag=0;
                }
                ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
            }
            printf("parent end!\n");
    }
    return 0;
}
