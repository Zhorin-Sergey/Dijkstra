#include "mpi.h"
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

void lineika(int s, int e, int* data, int rank) {
  MPI_Status status;
  if (s < e) {
    if (rank == s)
      MPI_Send(data, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    if (rank == e)
      MPI_Recv(data, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
    if (rank > s && rank < e) {
      MPI_Recv(data, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
      MPI_Send(data, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }
  }
  if (s > e) {
    if (rank == s)
      MPI_Send(data, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
    if (rank == e)
      MPI_Recv(data, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &status);
    if (rank < s && rank > e) {
      MPI_Recv(data, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &status);
      MPI_Send(data, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
    }
  }
}

int main(int argc, char* argv[])
{
  int p_s, p_e;

  p_s = atoi(argv[1]);
  p_e = atoi(argv[2]);

  double Stime, Etime, time;
  int buff = 0;

  int ProcNum, ProcRank;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  if (ProcRank == p_s)
    buff = atoi(argv[3]);
  Stime = MPI_Wtime();
 /* if (p_s < p_e) {
    for (int i = p_s; i < p_e; i++) {
      if (i == ProcRank)
        MPI_Send(&buff, 1, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
      if (ProcRank == (i + 1))
        MPI_Recv(&buff, 1, MPI_INT, ProcRank - 1, 0, MPI_COMM_WORLD, &status);
    }
  }
  if (p_s > p_e) {
    for (int i = p_s; i > p_e; i--) {
      if (i == ProcRank)
        MPI_Send(&buff, 1, MPI_INT, i - 1, 0, MPI_COMM_WORLD);
      if (ProcRank == (i - 1))
        MPI_Recv(&buff, 1, MPI_INT, ProcRank + 1, 0, MPI_COMM_WORLD, &status);
    }
  }*/
  lineika(p_s, p_e, &buff, ProcRank);
  printf("%i      %i \n", buff, ProcRank);
  Etime = MPI_Wtime();
  if (ProcRank == p_e) {
    time = Etime - Stime;
    printf("\n Time: %1.10f", time);
  }

  MPI_Finalize();

  return 0;
}
