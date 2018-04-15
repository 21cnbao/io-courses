#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <sys/stat.h>

static void call_epoll(void)
{
	int epfd, fifofd, pipefd;
	struct epoll_event ev, events[2];
	int ret;

	epfd = epoll_create(2);
	if (epfd < 0) {
		perror("epoll_create()");
		return;
	}

	ev.events = EPOLLIN|EPOLLET;

	fifofd = open("/dev/globalfifo", O_RDONLY, S_IRUSR);
	printf("fifo fd:%d\n", fifofd);
	ev.data.fd = fifofd;
	ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fifofd, &ev);

	pipefd = open("pipe", O_RDONLY|O_NONBLOCK, S_IRUSR);
	printf("pipe fd:%d\n", pipefd);
	ev.data.fd = pipefd;
	ret = epoll_ctl(epfd, EPOLL_CTL_ADD, pipefd, &ev);

	while(1) {
		ret = epoll_wait(epfd, events, 2, 50000);
		if (ret < 0) {
			perror("epoll_wait()");
		} else if (ret == 0) {
			printf("No data within 50 seconds.\n");
		} else {
			int i;
			for(i=0;i<ret;i++) {
				char buf[100];
				read(events[i].data.fd, buf, 100);
				printf("%s is available now:, %s\n",
						events[i].data.fd==fifofd? "fifo":"pipe", buf);
			}
		}
	}
_out:
	close(epfd);
}

int main()
{
	call_epoll();
	return 0;
}
