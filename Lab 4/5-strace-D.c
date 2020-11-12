#include <stdlib.h>
#include <unistd.h>  // getppid, readlink
#include <stdio.h>
#include <time.h>

/* This app shows parent process name to demonstrate strace's -D option:
 * $ ./test
 * /bin/bash
 * $ strace ./test 2>/dev/null
 * /usr/bin/strace
 * $ strace -D ./test 2>/dev/null
 * /bin/bash
 */

int main(int argc, char const *argv[]) {
	char path[256], exe[256];
	snprintf(path, 256, "/proc/%d/exe", getppid());
	// readlink does not append null byte, but returns string length
	exe[readlink(path, exe, 256)] = 0;
	puts(exe);

	return 0;
}
