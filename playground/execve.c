#include <unistd.h>

int main()
{
	char *argv[] = {"ls", "-la", NULL};

	execve("/bin/ls", argv, NULL);
}
