/***************************************************************
* TO BE EXECUTED FIRST
***************************************************************/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MSGSZ  1024
struct message_buf 
{
    long    mtype;
    char s[MSGSZ];
};

int main()
{
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    struct message_buf sbuf;
    size_t buf_length;
    key = 2929;
    
    if((msqid = msgget(key, msgflg )) < 0)
    {
        perror("msgget");
        exit(1);
    } 
    printf("msgget: msgget succeeded: msqid = %d\n", msqid);  
    char c;
    
    printf("Press Any key\n");
    scanf("%c",&c);

    printf("Enter Message : \n");
    scanf("%s",sbuf.s);
    
    sbuf.mtype = 1;
    buf_length = strlen(sbuf.s) + 1;   

    if(msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0)
    {
        perror("msgsnd");
        exit(1);
    } 
    printf("Message:  Sent\n");
}

