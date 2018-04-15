#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

static void sig_handler(int signum)
{
	printf("int handler %d\n", signum);
}

int main(int argc, char **argv)
{
	char buf[100];
	ssize_t ret;
	struct sigaction oldact;
	struct sigaction act;

	act.sa_handler = sig_handler;
	act.sa_flags = 0;
	//  act.sa_flags |= SA_RESTART;
	sigemptyset(&act.sa_mask);
	if (-1 == sigaction(SIGUSR1, &act, &oldact)) {
		printf("sigaction failed!/n");
		return -1;
	}

	bzero(buf, 100);
	do {
		ret = read(STDIN_FILENO, buf, 10);
		if ((ret == -1) && (errno == EINTR))
			printf("retry after eintr\n");
	} while((ret == -1) && (errno == EINTR));

	if (ret > 0)
		printf("read %d bytes, content is %s\n", ret, buf);
	return 0;
}
