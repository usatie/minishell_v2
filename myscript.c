#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	printf("argc:%d\n", argc);
	while (*argv)
	{
		printf("argv:%s\n", *argv);
		*argv++;
	}
	write(1, "hello\n", 6);
	write(2, "error\n", 6);
}
