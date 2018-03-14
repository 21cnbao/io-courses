/*
 *how to run: http://mp.weixin.qq.com/s/Xp4-r-a2iWpDx_yntGIGOQ
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <event.h>

static void cmd_event(int fd, short events, void *arg)
{
	char msg[1024];

	int ret = read(fd, msg, sizeof(msg));
	if (ret <= 0) {
		perror("read fail ");
		exit(1);
	}
	msg[ret]='\0';
	printf("%s", msg);
}

int main(int argc, char **argv)
{
	struct event ev_cmd;
	
	event_init();
	
	event_set(&ev_cmd, STDIN_FILENO,
		  EV_READ | EV_PERSIST, cmd_event, NULL);
	event_add(&ev_cmd, NULL);

	event_dispatch();

	return 0;
}                                                                                  


