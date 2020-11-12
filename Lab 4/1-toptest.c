#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[]) {
	if (argc > 2 || (argc == 2 && strcmp(argv[1], "-d"))) {
		fprintf(stderr, "usage: %s [-d]\n", argv[0]);
		return 1;
	}

	// endlessly calculate exponentially weighted moving average of pseudo-random signal
	const float lambda = 0.6;
	float x, ewma = 0.5;

	// passed to nanosleep if -d is given, 1 ms
	const struct timespec delay = { 0, 1e6 };

	while (1) {
		x = (float) rand() / RAND_MAX;
		ewma = lambda * x + (1-lambda) * ewma;

		if (argc == 2) {
			nanosleep(&delay, NULL);
		}
	}

	return 0;
}
