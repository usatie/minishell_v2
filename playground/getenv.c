#include <stdlib.h>
#include <stdio.h>

int main()
{
	char *path;

	path = getenv("PATH");
	printf("%s\n", path);
}
