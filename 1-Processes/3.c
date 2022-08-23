#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t pid;
	int n;

	scanf("%d", &n);
	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}

	else if (pid == 0) {
		while(n > 1) {
			printf("%d ", n);
			if(n%2) {
				n = 3*n + 1;
			}
			else {
				n = n/2;
			}
		}
		printf("%d\n", n);
	}

	else {
		wait(NULL);
	}

	return 0;
}
