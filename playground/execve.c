#include <unistd.h>

void	test1()
{
	char *argv[] = {"/bin/ls", "-la", NULL};
	execve("/bin/ls", argv, NULL);
}

void	test2()
{
	char *argv[] = {"", "", NULL};
	execve("", argv, NULL);
}

void	test3()
{
	char *argv[] = {"/bin/cat", "-n", "test.sh", NULL};
	execve("/bin/cat", argv, NULL);
}

int main()
{
	//test1();
	//test2();
	//test3();
	char *argv[] = {"./a.out", NULL};
	execve("./a.out", argv, NULL);
}
