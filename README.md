#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
int main(int argc, char* argv[]) {
  MPI_Status status;
  int i = 0;
  int thread_count, rank;
  double *duff;
  double *uff;
  int m = atoi(argv[1]);
  int n = atoi(argv[2]);
  int seed = atoi(argv[3]);
  double *a = 0;
  int* b2 = 0;
  double* b = 0;
  MPI_Datatype anyStructType;
  MPI_Datatype anyStructType1;
  i = 0;
  int segmentSize, bufferSize;
  double starttime, endtime;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &thread_count);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  segmentSize = m / thread_count;
  bufferSize = segmentSize;
/*  int* len = new int[segmentSize];
  MPI_Aint* pos = new MPI_Aint[segmentSize];
  MPI_Datatype* typ = new MPI_Datatype[segmentSize];
  int* len1 = new int[segmentSize];
  MPI_Aint* pos1 = new MPI_Aint[segmentSize];
  MPI_Datatype* typ1 = new MPI_Datatype[segmentSize];
  int* buff = new int[n];
  while (i<segmentSize) {
    len[i] = n;
    pos[i] = i*thread_count*n*sizeof(int);
    typ[i] = MPI_INT;
    len1[i] = 1;
    pos1[i] = i*thread_count*sizeof(int);
    typ1[i] = MPI_INT;
    i++;
  }
  i = 0;
  MPI_Type_struct(segmentSize, len, pos, typ, &anyStructType);
  MPI_Type_commit(&anyStructType);
  MPI_Type_struct(segmentSize, len1, pos1, typ1, &anyStructType1);
  MPI_Type_commit(&anyStructType1);*/
  i = 0;
  if (rank == 0) {
    int k = 0;
    a = new double[n*m];
    b2 = new int[n];
    b = new double[m];
    srand(seed);
    int l = 1;
    while (k<m*n) {
      a[k] = (double)rand() / (double)RAND_MAX * (20 - -12) + -12;
      if (n*m < 1000) {
   //     printf("%lf ", a[k]);
        if (k == (n*l) - 1) {
         // printf(" \n");
          l++;
        }
      }
      k++;
    }
  //  printf(" \n");
    k = 0;
    while (k<n) {
      b2[k] = 0;
      k++;
    }
    k = 0;
    srand(seed+1);
    while (k<m) {
      b[k] = (double)rand() / (double)RAND_MAX * (20 - -12) + -12;
     // printf("%lf ", b[k]);
      k++;
    }
 //   printf("Eto b \n");
    k = 0;
    int j = 0;
    duff = new double[segmentSize*n];
    uff = new double[segmentSize];
    while (i<segmentSize*n) {

      duff[i] = 0;
      i++;
    }
    i = 0;
    while (i<segmentSize) {

      uff[i] = 0;
      i++;
    }
    i = 1;
   /* starttime = MPI_Wtime();
    while (k < n) {
      j = k;
      while (j < n*m){
        (b2[(k)]) += a[j];
        j = j + n;
      }
      k = k + 1;
    }
    endtime = MPI_Wtime();
    k = 0;
    printf("%f\n", endtime - starttime);
  }
  if (rank == 0) {

    i = 0;
    duff = new int[segmentSize*m];
    while (i<segmentSize*m) {

      duff[i] = 0;
      i++;
    }
    i = 1;
    starttime = MPI_Wtime();*/
  //  while (i < thread_count) {
   //   MPI_Send(a, 1, anyStructType, i, 0, MPI_COMM_WORLD);
      MPI_Scatter(a, segmentSize*n, MPI_DOUBLE,
        duff, segmentSize*n, MPI_DOUBLE,
        0, MPI_COMM_WORLD);
      MPI_Scatter(b, segmentSize, MPI_DOUBLE,
        uff, segmentSize, MPI_DOUBLE,
        0, MPI_COMM_WORLD);
     // MPI_Send(b + (i)*segmentSize, 1, anyStructType1, i, 0, MPI_COMM_WORLD);
   //   i++;
   // }
    i = 0;
  }
  else {
    duff = new double[segmentSize*n];
    uff = new double[segmentSize];
    i = 0;
    while (i<segmentSize*n) {
      duff[i] = 0;
      i++;
    }
    while (i<segmentSize) {
      uff[i] = 0;
      i++;
    }
    i = 0;
    MPI_Scatter(0, 0, MPI_DOUBLE,
      duff, segmentSize*n, MPI_DOUBLE,
      0, MPI_COMM_WORLD);
    MPI_Scatter(0, 0, MPI_DOUBLE,
      uff, segmentSize, MPI_DOUBLE,
      0, MPI_COMM_WORLD);
   // MPI_Recv(duff, segmentSize*n, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    //MPI_Recv(uff, segmentSize, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
  }
  i = 0;
  while (i<segmentSize*n) {
    printf("%lf ", duff[i]);
    i++;
  }
  i = 0;
  printf("      ");
  while (i<segmentSize) {
    printf("%lf ", uff[i]);
    i++;
  }
  printf(" rank %i \n", rank);
  i = 0;
  for (int p = 0; p < segmentSize; p++) {
    int ved = p + p*n + rank*segmentSize;
	double* vedel = new double[segmentSize - p];
	for (int u = 0; u < segmentSize - p; u++) {
		vedel[u] = duff[ved + (u)*n];
	}

    uff[p] /= duff[ved];
    bool flag = true;
    for (int q = ved; q < n*(rank*segmentSize + p + 1); q++) {
      duff[q] = duff[q]/vedel[0];
      if (q != ved)
        flag = false;
      for (int w = p +1; w < segmentSize; w++){
        if (flag == true)
          uff[w] -= uff[p];
        duff[w*n + q] -= duff[q] * vedel[w];
      }
    }
	delete[] vedel;
  }
  while (i<segmentSize*n) {
    printf("%lf ", duff[i]);
    i++;
  }
  i = 0;
  printf("      ");
  while (i<segmentSize) {
    printf("%lf ", uff[i]);
    i++;
  }
  printf(" rank %i \n", rank);
 // for (int p = 1, p)
  /*
  if (rank == 0) {
    int* b = new int[n];
    i = 0;
    while (i<n) {
      b[i] = 0;
      i++;
    }
    i = 0;
    while (i < segmentSize) {
      int j = i;
      while (j < m*n) {
        b[i] += a[j];
        j = j + n;
      }
      i++;
    }
    i = 0;
    for (i = 1; i < thread_count; i++) {
      MPI_Recv(buff, 2 * segmentSize, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
      for (int j = 0; j < 2 * segmentSize; j = j + 2)
        b[buff[j]] = buff[j + 1];
    }
    i = 0;
    if (thread_count*segmentSize < n){
      i = thread_count*segmentSize;
      while (i < n) {
        int j = i;
        while (j < m*n) {
          b[i] += a[j];
          j = j + n;
        }
        i++;
      }
    }
    endtime = MPI_Wtime();
    i = 0;
    int flag = 1;
    if (n*m < 25)
    while (i<n) {
      printf("%i ", b[i]);
      i++;
    }
    printf(" \n");
    i = 0;
    while (i<n) {
      if (b[i] != b2[i])
        flag = 0;
      i++;
    }
    printf("%i \n", flag);
    printf("%f\n", endtime - starttime);
  }*/
  MPI_Finalize();
  return 0;
}
