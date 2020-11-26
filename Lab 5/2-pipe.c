#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void continue_as_child(int fd) {
	dup2(fd, 0);
	execlp("xxd", "xxd", NULL);
}

void continue_as_parent(int fd) {
	const char* message = "Hello, world!";
	write(fd, message, strlen(message) + 1);

	printf("Data sent to pipe, waiting for 1 second before closing it...\n");
	sleep(1);

	printf("Closing pipe\n");
	close(fd);
}

int main(int argc, char const *argv[]) {
	int fd[2];

	if (pipe(fd) < 0) {
		fprintf(stderr, "%s: pipe() failed\n", *argv);
	}

	pid_t pid = fork();

	if (pid < 0) {
		close(fd[0]);
		close(fd[1]);
		fprintf(stderr, "%s: fork() failed\n", *argv);
	}
	else if (pid == 0) {
		close(fd[1]);
		continue_as_child(fd[0]);

		fprintf(stderr, "%s: exec() failed\n", *argv);
		return 1;
	}
	else {
		close(fd[0]);
		continue_as_parent(fd[1]);

		wait(NULL);

		return 0;
	}
}
