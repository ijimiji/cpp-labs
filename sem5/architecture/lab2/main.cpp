#include <cstdlib>
#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/times.h>
#include <time.h>

#define MAXN 2000

double realtime() {
    struct timeb tp;
    ftime(&tp);
    return ((double)(tp.time) * 1000 + (double)(tp.millitm));
}

double A[MAXN][MAXN], map[MAXN], b[MAXN], c[MAXN], x[MAXN], sum = 0.0;

int main(int argc, char **argv) {
    MPI_Status status;
    MPI_Init(&argc, &argv);
    double t1, t2, range = 1.0;
    int n = 1000, rank, nprocs;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if (rank == 0) {
        for (auto i = 0; i < n; i++) {
            for (auto j = 0; j < n; j++) {
                if (i == j) {
                    A[i][j] = 1.0;
                } else {
                    A[i][j] = 0.0;
                }
            }
            // b[i] = range * (1.0 - 2.0 * (double)rand() / RAND_MAX);
            b[i] = 1.0;
        }

        std::cout << "Matrix" << "\n";
        for (auto i = 0; i < n; i++) {
            for (auto j = 0; j < n; j++) {
                std::cout << A[i][j] << "\t";
            }
            std::cout << "|\t" << b[i] << "\n";
        }
    }

    t1 = realtime();

    MPI_Bcast(&A[0][0], MAXN * MAXN, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(b, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (auto i = 0; i < n; i++) {
        map[i] = i % nprocs;
    }

    for (auto k = 0; k < n; k++) {
        MPI_Bcast(&A[k][k], n - k, MPI_DOUBLE, map[k], MPI_COMM_WORLD);
        MPI_Bcast(&b[k], 1, MPI_DOUBLE, map[k], MPI_COMM_WORLD);
        for (auto i = k + 1; i < n; i++) {
            if (map[i] == rank) {
                c[i] = A[i][k] / A[k][k];
            }
        }
        for (auto i = k + 1; i < n; i++) {
            if (map[i] == rank) {
                for (auto j = 0; j < n; j++) {
                    A[i][j] = A[i][j] - (c[i] * A[k][j]);
                }
                b[i] = b[i] - (c[i] * b[k]);
            }
        }
    }
    if (rank == 0) {
        x[n - 1] = b[n - 1] / A[n - 1][n - 1];
        for (auto i = n - 2; i >= 0; i--) {
            sum = 0;

            for (auto j = i + 1; j < n; j++) {
                sum = sum + A[i][j] * x[j];
            }
            x[i] = (b[i] - sum) / A[i][i];
        }

        t2 = realtime();
    }

    if (rank == 0) {
        std::cout << "Answer:" << "\n";
        for (auto i = 0; i < n; i++) {
            std::cout << x[i] << "\n";
        }
        std::cout << "Finished in " << t2 - t1 << "ms\n";
    }
    MPI_Finalize();
    return (0);
}