#include<stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<time.h>

struct msgbuf{
long msgtype;
int mbits[10];
};

int main(){
	struct msgbuf buf;
	int msqid;
	int len;
	char ch;
	key_t key;
	key = ftok("crcshmfile",65);
	msqid = msgget(key,0644|IPC_CREAT);
	buf.msgtype = 1;
	printf("Enter a character: ");
	scanf("%s",&ch);
	int asc = ch;
	printf("%d \n",asc);
	int i;
	int temp = 1;
	int tembuf[10];
	for(i=6;i>=0;i--){
			if(asc&temp){
				buf.mbits[i]=1;
				tembuf[i]=1;
			}
			else{
				buf.mbits[i]=0;
				tembuf[i]=0;
			}
			temp = temp<<1;
		}
	int ptr = 0;
	tembuf[7]=0;
	tembuf[8]=0;
	tembuf[9]=0;
	while(ptr<7){
		if(tembuf[ptr]==0){ptr=ptr+1;continue;}
		tembuf[ptr]=tembuf[ptr]^1;
		tembuf[ptr+1]=tembuf[ptr+1]^1;
		tembuf[ptr+2]=tembuf[ptr+2]^0;
		tembuf[ptr+3]=tembuf[ptr+3]^1;
		ptr = ptr+1;
	}
	for(int j=7;j<10;j++){
		buf.mbits[j]=tembuf[j];
	}

//printing actual binary of character......

	for(i=0;i<10;i++){
		printf("%d ",buf.mbits[i]);
	}
//flipping a random bit.......
srand(time(0));
        int randomize = rand()%2;
        int flip = rand()%6;
        if(randomize==1){
        if(buf.mbits[flip])
                buf.mbits[flip]=0;
        else
                buf.mbits[flip]=1;
        }
//sending message..........

	msgsnd(msqid,&buf,10*sizeof(int),0);
	printf("\ncharacter sent to reciever....\n");
	return 0;
}

