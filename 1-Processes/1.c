#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t pid;
	int c = 1;

	for(int i = 0; i < 2; i++) {
		c++;
		pid = fork();
	}

	printf("PID %d\n", pid);

	if(pid != 0) {
		wait(NULL);
		printf("c=%d\n", c);
	}

	return 0;
}
