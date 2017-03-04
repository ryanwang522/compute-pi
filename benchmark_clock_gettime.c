#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "computepi.h"

#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0

int main(int argc, char const *argv[])
{
    struct timespec start = {0, 0};
    struct timespec end = {0, 0};

    if (argc < 2) return -1;

    int N = atoi(argv[1]);
    int i, loop = 250;

    // Baseline
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_baseline(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);
    double pi_base = compute_pi_baseline(N);
    double diff = pi_base - M_PI > 0 ? pi_base - M_PI : M_PI - pi_base;
    printf("%lf,", (double) (diff / M_PI));

    // OpenMP with 2 threads
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_openmp(N, 2);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);
    double pi_omp2 = compute_pi_openmp(N, 2);
    diff = pi_omp2 - M_PI > 0 ? pi_omp2 - M_PI : M_PI - pi_omp2;
    printf("%lf,", (double) (diff / M_PI));


    // OpenMP with 4 threads
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_openmp(N, 4);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);
    double pi_omp4 = compute_pi_openmp(N, 4);
    diff = pi_omp4 - M_PI > 0 ? pi_omp4 - M_PI : M_PI - pi_omp4;
    printf("%lf,", (double) (diff / M_PI));

    // AVX SIMD
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_avx(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);
    double pi_avx = compute_pi_avx(N);
    diff = pi_avx - M_PI > 0 ? pi_avx - M_PI : M_PI - pi_avx;
    printf("%lf,", (double) (diff / M_PI));

    // AVX SIMD + Loop unrolling
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_avx_unroll(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);
    double pi_avxunroll = compute_pi_avx_unroll(N);
    diff = pi_avxunroll - M_PI > 0 ? pi_avxunroll - M_PI : M_PI - pi_avxunroll;
    printf("%lf,", (double) (diff / M_PI));

    // Leibniz baseline
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_Leibniz(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);
    double pi_Leib_base = compute_pi_Leibniz(N);
    diff = pi_Leib_base - M_PI > 0 ? pi_Leib_base - M_PI : M_PI - pi_Leib_base;
    printf("%lf,", (double) (diff / M_PI));

    // Leibniz OpenMP 4 threads
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_Leibniz_omp(N, 4);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);
    double pi_Leib_omp4 = compute_pi_Leibniz_omp(N, 4);
    diff = pi_Leib_omp4 - M_PI > 0 ? pi_Leib_omp4 - M_PI : M_PI - pi_Leib_omp4;
    printf("%lf\n", (double) (diff / M_PI));

    return 0;
}
