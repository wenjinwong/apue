#include<aio.h>
#include<stdio.h>
#include<unistd.h>

void handler(union sigval arg) {
	printf("handler()\n");
}

int
main(void)
{
	struct aiocb cb;
	cb.aio_fildes = STDOUT_FILENO;
	cb.aio_offset = 10;
	char buf[1024] = "01234567891011121314151617181920\n";
	cb.aio_nbytes = 100;
	struct sigevent sig;
	sig.sigev_notify = SIGEV_THREAD;
	sig.sigev_signo = _SC_POLL;
	//sig.sigev_signotify_function = handler;
	
	aio_write(&cb);
}
