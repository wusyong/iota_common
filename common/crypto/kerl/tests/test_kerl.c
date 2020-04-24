/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unity/unity.h>

#include "common/crypto/kerl/kerl.h"
#include "common/trinary/trit_tryte.h"
#include "common/trinary/trits.h"
#include "librust_kerl.h"

#define TRIT_LENGTH 243
#define TRYTE_LENGTH 81
#define BYTE_LENGTH 48
#define INT_LENGTH 12

#include <sys/time.h>
#include <sys/resource.h>

void random_trits(trit_t *array, size_t n)
{
	size_t i;
	for (i = 0; i < n; i++) 
	{
		array[i] = (rand() % 3) - 1;
	}
}

double get_current_time() {
	struct timeval t;
	gettimeofday(&t, 0);
	return t.tv_sec + t.tv_usec*1e-6;
}

void benchmark()
{
	double mean_time = 0.0; /** The time the benchmark ran. **/
	double total_time = 0.0; /** The total time. **/
	int i;

	printf("----------------------------\nStarting C benchmark...\n----------------------------\n");

	for(i = 0; i < 1000; ++i)
	{
		double start_time = 0.0; /** The time the benchmark started. **/
		double end_time = 0.0; /** The time the benchmark ended. **/
		double bench_time = 0.0; /** end_time - start_time **/

		/* Start the benchmark. */
		start_time = get_current_time();

		/* Call the function to benchmark. */
		trit_t trits[8019] = {0};
		random_trits(trits, 8019);
		Kerl kerl;
		kerl_init(&kerl);
		kerl_absorb(&kerl, trits, 8019);
		kerl_squeeze(&kerl, trits, 8019);

		/* End the benchmark. */
		end_time = get_current_time();
		bench_time = end_time - start_time;

		/* Add the benchmark time to the total time. */
		total_time += bench_time;

		/* Add the benchmark time to mean_time and if it wasn't 0, divide by 2. */
		if(mean_time)
			mean_time = (mean_time + bench_time) / 2;
		else
			mean_time = bench_time;

		/* Print the current step. */
		//printf("Completed step %d\tTime spent: %fs\n", i + 1, bench_time);
	}

	/* Gobal time spent in the benchmark. */
	printf("----------------------------\nEnded C benchmark!\n");
	printf("Total time spent: %fs\n", total_time);
	printf("Mean time spent: %fs\n----------------------------\n", mean_time);
}

void rbenchmark()
{
	double mean_time = 0.0; /** The time the benchmark ran. **/
	double total_time = 0.0; /** The total time. **/
	int i;

	printf("----------------------------\nStarting Rust benchmark...\n----------------------------\n");

	for(i = 0; i < 1000; ++i)
	{
		double start_time = 0.0; /** The time the benchmark started. **/
		double end_time = 0.0; /** The time the benchmark ended. **/
		double bench_time = 0.0; /** end_time - start_time **/

		/* Start the benchmark. */
		start_time = get_current_time();

		/* Call the function to benchmark. */
		trit_t trits[8019] = {0};
		random_trits(trits, 8019);
		rust_kerl(trits, 8019);

		/* End the benchmark. */
		end_time = get_current_time();
		bench_time = end_time - start_time;

		/* Add the benchmark time to the total time. */
		total_time += bench_time;

		/* Add the benchmark time to mean_time and if it wasn't 0, divide by 2. */
		if(mean_time)
			mean_time = (mean_time + bench_time) / 2;
		else
			mean_time = bench_time;

		/* Print the current step. */
		//printf("Completed step %d\tTime spent: %fs\n", i + 1, bench_time);
	}

	/* Gobal time spent in the benchmark. */
	printf("----------------------------\nEnded Rust benchmark!\n");
	printf("Total time spent: %fs\n", total_time);
	printf("Mean time spent: %fs\n----------------------------\n", mean_time);

}


int main(void) {
  UNITY_BEGIN();

  RUN_TEST(benchmark);
  RUN_TEST(rbenchmark);

  return UNITY_END();
}

#undef TRYTE_LENGTH
#undef TRIT_LENGTH
#undef BYTE_LENGTH
#undef INT_LENGTH
