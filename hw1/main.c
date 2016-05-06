#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define USEC_PER_SEC (1000*1000)
#define EXPECTED_SLOT_USEC (100*1000)

extern void random_length_task();

int get_us_elapsed_from(struct timeval start_time) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	int d_sec = tv.tv_sec - start_time.tv_sec;
	int d_usec = tv.tv_usec - start_time.tv_usec;

	return d_usec + d_sec*USEC_PER_SEC;
}

int main(int argc, char ** argv) {
	srand(time(0) ^ getpid());
	int n = atoi(argv[1]);

	struct timeval start_time;
	gettimeofday(&start_time, NULL);

	while(n--) {
		int usec = get_us_elapsed_from(start_time);
		usec %= EXPECTED_SLOT_USEC;

		usleep(EXPECTED_SLOT_USEC - usec);
		random_length_task();
	}

	return 0;
}

