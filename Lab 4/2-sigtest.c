#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>

volatile int run = 1;
volatile unsigned long usr1_ignore_counter = 0;

void sigalrm_handler(int signum) {
	puts("SIGALRM received");
}

void sigterm_handler(int signum) {
	puts("SIGTERM received, exiting");
	run = 0;
}

void sigusr1_handler(int signum) {
	puts("SIGUSR1 received, disabling it for 1000 ticks");
	usr1_ignore_counter = 1000;
	signal(SIGUSR1, SIG_DFL);  // use default handler
}

int main(int argc, char const *argv[]) {
	// register signal handlers
	signal(SIGALRM, sigalrm_handler);
	signal(SIGTERM, sigterm_handler);
	signal(SIGUSR1, sigusr1_handler);
	signal(SIGUSR2, SIG_IGN);  // ignore

	// endlessly calculate exponentially weighted moving average of pseudo-random signal
	const float lambda = 0.6;
	float x, ewma = 0.5;

	// passed to nanosleep, 1 ms
	const struct timespec delay = { 0, 1e6 };

	while (run) {
		if (usr1_ignore_counter) {
			if (!--usr1_ignore_counter) {
				// re-register handler
				signal(SIGUSR1, sigusr1_handler);
				puts("SIGUSR1 re-enabled");
			}
		}

		x = (float) rand() / RAND_MAX;
		ewma = lambda * x + (1-lambda) * ewma;

		nanosleep(&delay, NULL);
	}

	return 0;
}
