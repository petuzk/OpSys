#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

/* This structure is used to pass arguments to and
 *   get result from the thrread function.
 * When passed as an argument, num_points contains
 *   a maximum number of points to test and num_inside
 *   has no meaning.
 * When interpreted as a return value, num_points
 *   contains a number of tested points (which will be
 *   less than the requested if the thread was cancelled)
 *   and a number of those points which fall inside
 *   the quarter of a circle (see `thread_calc_pi`)
 */
typedef struct {
	size_t num_points;
	size_t num_inside;
} threadio_t;

/* This structure holds global state. It has choosen
 *   to be global to make use of interrupts.
 */
typedef struct {
	char* progname;

	size_t num_threads;
	size_t num_points;

	threadio_t* tios;
	pthread_t* threads;
} globstate_t;

volatile globstate_t globstate = { NULL, 4, 1000, NULL, NULL };

/* This function generates random points in a 1x1 square
 * and tests whether a point falls inside a quarter of a circle
 * of a radius 1, i.e. whether the distance from origin is less
 * than 1. See `threadio_t` above which describes the data flow.
 */
void* thread_calc_pi(void* vptr_tio) {
	threadio_t* tio = (threadio_t*) vptr_tio;

	double x, y, d;
	size_t max_num_points = tio->num_points;
	tio->num_points = 0;
	tio->num_inside = 0;

	while (tio->num_points < max_num_points) {
		x = drand48();
		y = drand48();
		d = sqrt(x*x + y*y);

		if (d < 1) {
			tio->num_inside++;
		}

		tio->num_points++;
		pthread_testcancel();
	}

	return NULL;
}

/* Handles interrupt (^C) by cancelling threads.
 */
void int_handler(int sig) {
	puts("");
	for (size_t i = 0; i < globstate.num_threads; i++) {
		pthread_cancel(globstate.threads[i]);
	}
}

void parse_args(int argc, char* argv[]) {
	char c;

	while ((c = getopt(argc, argv, "t:n:h")) != -1) {
		switch (c) {
			case 't':
				globstate.num_threads = strtol(optarg, NULL, 0);
				break;
			case 'n':
				globstate.num_points = strtol(optarg, NULL, 0);
				break;
			case 'h':
				fprintf(stderr,
					"usage: %s [ -t num_threads ] [ -n num_points_per_thread ]\n", globstate.progname);
				exit(0);
		}
	}

	if (globstate.num_threads == 0) {
		fprintf(stderr, "%s: bad value for threads count\n", globstate.progname);
		exit(1);
	}

	if (globstate.num_points == 0) {
		fprintf(stderr, "%s: bad value for points count\n", globstate.progname);
		exit(2);
	}
}

void allocate_arrays() {
	globstate.tios = malloc(globstate.num_threads * sizeof(threadio_t));
	globstate.threads = malloc(globstate.num_threads * sizeof(pthread_t));
}

void init_tios() {
	for (size_t i = 0; i < globstate.num_threads; i++) {
		globstate.tios[i].num_points = globstate.num_points;
	}
}

void start_threads() {
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for (size_t i = 0; i < globstate.num_threads; i++) {
		int err = pthread_create(
			globstate.threads + i, &attr, thread_calc_pi, (void *) (globstate.tios + i));

		if (err) {
			fprintf(stderr, "%s: pthread_create returned %d\n", globstate.progname, err);
			exit(3);
		}
	}
}

void wait_threads() {
	for (size_t i = 0; i < globstate.num_threads; i++) {
		int err = pthread_join(globstate.threads[i], NULL);
		if (err) {
			fprintf(stderr, "%s: pthread_join returned %d\n", globstate.progname, err);
			exit(4);
		}
	}
}

void print_results() {
	double total, sum_total = 0;
	double inside, sum_inside = 0;

	for (size_t i = 0; i < globstate.num_threads; i++) {
		total = globstate.tios[i].num_points;  sum_total += total;
		inside = globstate.tios[i].num_inside; sum_inside += inside;

		printf(
			"Result from thread #%lu: %f (%lu points)\n",
			i+1, 4.0*inside/total, globstate.tios[i].num_points);
	}

	printf("Average:      %f\n", 4.0*sum_inside/sum_total);
	printf("C math value: %f\n", M_PI);
}

int main(int argc, char* argv[]) {
	globstate.progname = *argv;
	parse_args(argc, argv);

	allocate_arrays();
	init_tios();
	start_threads();

	printf(
		"Calculating PI on %lu threads & %lu points/thread\n",
		globstate.num_threads, globstate.num_points);

	signal(SIGINT, int_handler);
	wait_threads();
	signal(SIGINT, SIG_DFL);

	print_results();
}
