#include <unistd.h>

void	test1()
{
	char *argv[] = {"/bin/ls", "-la", NULL};
	execve("/bin/ls", argv, NULL);
}

void	test1()
{
	char *argv[] = {"", "", NULL};
	execve("", argv, NULL);
}

int main()
{
	//test1();
	test2();
}
