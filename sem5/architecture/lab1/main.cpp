#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <time.h>


double realtime() {
  struct timeb tp;
  ftime(&tp);
  return ((double)(tp.time) * 1000 + (double)(tp.millitm));
}
int *matrix1, *matrix2, *tmp, *buf, *result;

int main(int argc, char *argv[]) {
  double start, stop;
  int i, j, k, l;
  int size = 10;
  int myRank, processesNumber, line;

  MPI_Init(NULL, NULL);
  // get current process rank
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
  // get number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &processesNumber);

  // divide into blocks to perform more efficient multiplication
  line = size / processesNumber;
  // allocate memory
  matrix1 = (int *)malloc(sizeof(int) * size * size);
  matrix2 = (int *)malloc(sizeof(int) * size * size);
  tmp = (int *)malloc(sizeof(int) * size * size);

  // buffer size (allocate memory)
  buf = (int *)malloc(sizeof(int) * size * line);
  // allocate memory to store the result of block multiplication on each step
  result = (int *)malloc(sizeof(int) * size * line);

  // main process (fill matrix & send to processes)
  if (myRank == 0) {
    start = MPI_Wtime();
    for (i = 0; i < size; i++)
      for (j = 0; j < size; j++)
        matrix1[i * size + j] = rand() % 101;

    for (i = 0; i < size; i++)
      for (j = 0; j < size; j++)
        matrix2[i * size + j] = rand() % 101;

    // send matrix to other slave processes
    for (i = 1; i < processesNumber; i++) {
      MPI_Send(matrix2, size * size, MPI_INT, i, 0, MPI_COMM_WORLD);
    }

    // send each line of matrix1 to every slave process
    for (l = 1; l < processesNumber; l++) {
      MPI_Send(matrix1 + (l - 1) * line * size, size * line, MPI_INT, l, 1,
               MPI_COMM_WORLD);
    }

    // acquire result from each process
    for (k = 1; k < processesNumber; k++) {
      MPI_Recv(result, line * size, MPI_INT, k, 3, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);

      // send result to tmp
      for (i = 0; i < line; i++) {
        for (j = 0; j < size; j++) {
          tmp[((k - 1) * line + i) * size + j] = result[i * size + j];
        }
      }
    }

    // calculate the remaining data(if size/procNumber is not integer)
    for (i = (processesNumber - 1) * line; i < size; i++) {
      for (j = 0; j < size; j++) {
        int temp = 0;
        for (k = 0; k < size; k++)
          temp += matrix1[i * size + k] * matrix2[k * size + j];
        tmp[i * size + j] = temp;
      }
    }

    // write the result into file(to demonstrate)
    FILE *outputMatrix = fopen("output.txt", "w");
    for (i = 0; i < size; i++) {
      for (j = 0; j < size; j++)
        fprintf(outputMatrix, "%d ", tmp[i * size + j]);
      fputc('\n', outputMatrix);
    }
    fclose(outputMatrix);

    stop = MPI_Wtime();

    // performance (execution time)
    printf("rank:%d time:%lfs\n", myRank, stop - start);

    free(matrix1);
    free(matrix2);
    free(tmp);
    free(buf);
    free(result);
  }

  // other processes acquire data and send it to main after calcultion is
  // completed
  else {
    // get widebroadcasting data (Matrix2)
    MPI_Recv(matrix2, size * size, MPI_INT, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);

    MPI_Recv(buf, size * line, MPI_INT, 0, 1, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    // calculate product
    for (i = 0; i < line; i++) {
      for (j = 0; j < size; j++) {
        int temp = 0;
        for (k = 0; k < size; k++)
          temp += buf[i * size + k] * matrix2[k * size + j];
        result[i * size + j] = temp;
      }
    }
    // send result to main process
    MPI_Send(result, line * size, MPI_INT, 0, 3, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return 0;
}