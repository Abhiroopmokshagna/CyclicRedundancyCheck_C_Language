#include<stdio.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>

struct msgbuf{
	long msgtype;
	int mbits[10];
	};

int main(){
	struct msgbuf buf;
	int msqid;
	key_t key;
	key = ftok("crcshmfile",65);
	msqid = msgget(key,0644);
	msgrcv(msqid,&buf,10*sizeof(int),0,0);
	printf("The recieved message bits are: \n");
	int count=0;
	int i;
	int tembuf[10];
	for(i=0;i<10;i++){
		printf("%d ",buf.mbits[i]);
		tembuf[i]=buf.mbits[i];
	 }
	printf("\n\n");
	int ptr = 0;
        while(ptr<7){
                if(tembuf[ptr]==0){ptr=ptr+1;continue;}
                tembuf[ptr]=tembuf[ptr]^1;
                tembuf[ptr+1]=tembuf[ptr+1]^1;
                tembuf[ptr+2]=tembuf[ptr+2]^0;
                tembuf[ptr+3]=tembuf[ptr+3]^1;
                ptr = ptr+1;
        }
	for(int j=7;j<10;j++){
		if(tembuf[j]==0);
		else{
			printf("\nThere is something wrong in the bits!!\n");
			break;
		}
	}

	return 0;
}

