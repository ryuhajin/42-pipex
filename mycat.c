#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	char buff[1000001];
	while (1)
	{
		if (fgets(buff, 100000, stdin) == NULL)
			break;
		printf("meow: %s", buff);
	}
	return (0);
}