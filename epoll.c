#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <time.h>
#include <sys/types.h>
#include <sys/epoll.h>

static void call_epoll(void)
{
	int epfd;
	struct epoll_event ev_stdin;
	int err;

	epfd = epoll_create(1);
	if (epfd < 0) {
		perror("epoll_create()");
		return;
	}

	bzero(&ev_stdin, sizeof(struct epoll_event));
	ev_stdin.events =
	    //  available for read operations
	    EPOLLIN | EPOLLPRI
	    // available for write operations
	    // | EPOLLOUT
	    // Error condition && Hang up happened
	    | EPOLLERR | EPOLLHUP
	    // Sets the Edge Triggered behaviour
	    | EPOLLET
	    // Sets the one-shot behaviour.
	    // must call epoll_ctl with EPOLL_CTL_MOD to re-enable
	    | EPOLLONESHOT;

	err = epoll_ctl(epfd, EPOLL_CTL_ADD, 1, &ev_stdin);
	if (err < 0) {
		perror("epoll_ctl()");
		goto _out;
	}
	err = epoll_wait(epfd, &ev_stdin, 1, 5000);
	if (err < 0) {
		perror("epoll_wait()");
	} else if (err == 0) {
		printf("No data within five seconds.\n");
	} else {
		printf("Data is available now.\n");
	}
	err = epoll_ctl(epfd, EPOLL_CTL_DEL, 1, &ev_stdin);
	if (err < 0) {
		perror("epoll_ctl()");
	}
 _out:
	close(epfd);
}

int main()
{
	call_epoll();
	return 0;
}
