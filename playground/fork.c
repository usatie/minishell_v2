#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t	pid;

	pid = fork();
	printf("[ %d, from %d ]\n", pid, getpid()); //1
	pid = fork();
	printf("[%d, from %d]\n", pid, getpid()); //2
}

/*
55
|  \
55  56
| \  \  \
55 58 56 57
*/