#include<sys/msg.h>
#define MAXMSZ 512
#include"apue.h"
struct mymesg{
	long mtype;
	char mtext[MAXMSZ];
};

int 
main(int argc, char *argv)
{
	key_t key;
	long qid;
	size_t nbytes;
	struct mymesg m;
	if(argc != 3) {
		fprintf(stderr, "usage: sendmsg KEY mseeage\n");
		exit(1);
	}
	//key = strtol(argv[1], NULL, 0);
	key = 0;
	if((qid = msgget(key, 0)) < 0)
		err_sys("can not open queue key %s", argv[1]);
	else 
		printf("msgget ok\n");
	memset(&m, 0, sizeof(m));
	
	strncpy(m.mtext, argv[2], MAXMSZ-1);
	nbytes = strlen(m.mtext);
	m.mtype = 1;
	
	if(msgsnd(qid, &m, nbytes, 0) < 0)
		err_sys("can not send message");
	printf("send over\n");
	sleep(5);
	exit(0);
}
