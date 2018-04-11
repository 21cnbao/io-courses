#include <unistd.h>
#include <fcntl.h>

main()
{
	int fd;
	char buf[4096];
	
	sleep(30); //run ./funtion.sh to trace this process
	fd = open("file", O_RDONLY);
	read(fd, buf, 4096);
	read(fd, buf, 4096);
}
