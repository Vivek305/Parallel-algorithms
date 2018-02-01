#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

void calc_2d_heat(float**, float**, unsigned long, unsigned long);
void initialize_chunk(float**, unsigned long, unsigned long, int);

int main (int argc, char* argv[]) {

  if (argc < 3) {
    std::cerr<<"usage: mpirun "<<argv[0]<<" <n> <k>"<<std::endl;
    return -1;
  }
  
  int p, P;
  
  MPI_Init(&argc, &argv);
  
  MPI_Comm_rank(MPI_COMM_WORLD, &p);
  MPI_Comm_size(MPI_COMM_WORLD, &P);
  
  unsigned long n = atoi(argv[1]);
  unsigned int k = atoi(argv[2]);
  unsigned long i, j;
  
  unsigned long rows = (p == P-1) ? (n/P) + (n%P) + 2 : (n/P) + 2;
  
  float** temp1 = new float*[rows];
  float** temp2 = new float*[rows];
  for (int i=0; i<rows; i++) {
    temp1[i] = (float*)malloc(n * sizeof(float));
    temp2[i] = (float*)malloc(n * sizeof(float));
    if (temp1[i] == NULL || temp2[i] == NULL) {
      std::cerr<<"Could not allocate required memory."<<std::endl;
      return -1;
    }
  }
  
  float** last = temp1;
  float** curr = temp2;
  MPI_Request* requests = (p == 0 || p == P-1) ? new MPI_Request[2] : new MPI_Request[4];
  MPI_Status* statuses = new MPI_Status[2];
  initialize_chunk(last, rows, n, p);
   
  MPI_Barrier(MPI_COMM_WORLD);
  auto start = std::chrono::system_clock::now();
  
  for (int K=0; K<k; K++) {
   
    if (P == 1) {
      memcpy(curr[0], last[0], n * sizeof(float));
      memcpy(curr[rows-1], last[rows-1], n * sizeof(float));
    }
    else if (p == 0) {
      MPI_Irecv(last[rows-1], n, MPI_FLOAT, p+1, 0, MPI_COMM_WORLD, &requests[0]);
      MPI_Isend(last[rows-2], n, MPI_FLOAT, p+1, 0, MPI_COMM_WORLD, &requests[1]);
      memcpy(curr[0], last[0], n * sizeof(float));
      MPI_Waitall(1, requests, statuses);
    }
    else if (p == P-1) {
      MPI_Irecv(last[0], n, MPI_FLOAT, p-1, 0, MPI_COMM_WORLD, &requests[0]);
      MPI_Isend(last[1], n, MPI_FLOAT, p-1, 0, MPI_COMM_WORLD, &requests[1]);
      memcpy(curr[rows-1], last[rows-1], n * sizeof(float));
      MPI_Waitall(1, requests, statuses);
    }
    else {
      MPI_Irecv(last[0], n, MPI_FLOAT, p-1, 0, MPI_COMM_WORLD, &requests[0]);
      MPI_Irecv(last[rows-1], n, MPI_FLOAT, p+1, 0, MPI_COMM_WORLD, &requests[1]);
      MPI_Isend(last[1], n, MPI_FLOAT, p-1, 0, MPI_COMM_WORLD, &requests[2]);
      MPI_Isend(last[rows-2], n, MPI_FLOAT, p+1, 0, MPI_COMM_WORLD, &requests[3]);
      MPI_Waitall(2, requests, statuses);
    }

    calc_2d_heat(curr, last, rows, n);

    curr = (i%2==0) ? temp1 : temp2;
    last = (i%2==0) ? temp2 : temp1;
  }
  
  
  MPI_Barrier(MPI_COMM_WORLD);
  if (p == 0) {

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end-start;
    std::cerr<<diff.count()<<std::endl;
  }
    
  MPI_Finalize();
  return 0;
}

void calc_2d_heat(float** curr, float** last, unsigned long rows, unsigned long n) {
  for (unsigned long i=1; i<rows-1; i++) {

    //calc end caps
    curr[i][0] = ((2 * last[i-1][0]) + (2 * last[i][0]) + (2 * last[i+1][0]) + last[i-1][1] + last[i][1] + last[i+1][1]) / 9;
    curr[i][n-1] = ((2 * last[i-1][n-1]) + (2 * last[i][n-1]) + (2 * last[i+1][n-1]) + last[i-1][n-2] + last[i][n-2] + last[i+1][n-2]) / 9;
    
    //fill in the rest
    for (unsigned long j=1; j<n-1; j++) {
      curr[i][j] = (last[i-1][j-1] + last[i][j-1] + last[i+1][j-1] + last[i-1][j] + last[i][j] + last[i+1][j] + last[i-1][j+1] + last[i][j+1] + last[i+1][j+1]) / 9;
    }
  }  
}

void initialize_chunk(float** arr, unsigned long rows, unsigned long n, int p) {
  srand(time(NULL));
  for (unsigned long i=1; i<rows; i++) {
    for (unsigned long j=0; j<n; j++) {
      arr[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }
  }
}
