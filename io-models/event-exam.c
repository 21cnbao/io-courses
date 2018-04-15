/*
 *how to run: http://mp.weixin.qq.com/s/Xp4-r-a2iWpDx_yntGIGOQ
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <event.h>

int fifofd;

static void fifo_event(int fd, short events, void *arg)
{
	char msg[1024];

	int ret = read(fd, msg, sizeof(msg));
	if (ret <= 0) {
		perror("read fail ");
		exit(1);
	}
	printf("fifo:%s\n", msg);
}

static void std_event(int fd, short events, void *arg)
{
	char msg[1024];

	int ret = read(fd, msg, sizeof(msg));
	if (ret <= 0) {
		perror("read fail ");
		exit(1);
	}
	printf("stdin:%s\n", msg);
}

int main(int argc, char **argv)
{
	struct event std, fifo;
	int fifofd;
	fifofd = open("/dev/globalfifo", O_RDONLY, S_IRUSR);
	printf("fifo fd:%d\n", fifofd);

	event_init();
	
	event_set(&std, STDIN_FILENO,
		  EV_READ | EV_PERSIST, std_event, NULL);
	event_set(&fifo, fifofd,
		EV_READ | EV_PERSIST, fifo_event, NULL);

	event_add(&std, NULL);
	event_add(&fifo, NULL);

	event_dispatch();

	return 0;
}                                                                                  

