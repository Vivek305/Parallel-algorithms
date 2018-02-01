#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>
#include <chrono>
#include <cstring>
#include <cstdint>
#include <string.h>


int main (int argc, char* argv[]) {

  //forces openmp to create the threads beforehand
#pragma omp parallel
  {
    int fd = open (argv[0], O_RDONLY);
    if (fd != -1) {
      close (fd);
    }
    else {
      std::cerr<<"something is amiss"<<std::endl;
    }
  }
  
  if (argc < 4) {
    std::cerr<<"Usage: "<<argv[0]<<"<str1_len> <str2_len> <nbthreads>"<<std::endl;
    return -1;
  }


  int m = atoi(argv[1]);
  int n = atoi(argv[2]);
  int nbthreads = atoi(argv[3]);
  char str1[m];
  char str2[n];
  for(int i =0;i<m;i++){
	  str1[i] = "abcdefghijklmnopqrstuvwxyz"[rand()%26];
  }
  for(int i =0;i<n;i++){
	  str2[i] = "abcdefghijklmnopqrstuvwxyz"[rand()%26];
  }
 
  int l1 = m;
  int l2 = n;
  
  
  int** arr = (int**)malloc((l1+1) * sizeof(int*));
  
  for(int i = 0; i <= l1; ++i)
  arr[i] = (int*)malloc((l2+1)* sizeof(int));



m = l1+1;
n=  l2+1;
omp_set_num_threads(nbthreads);
std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

	#pragma omp parallel for
	for(int i =0;i<n;i++)
	arr[0][i] = 0;

	#pragma omp parallel for
	for(int i=0;i<m;i++)
	arr[i][0] = 0;
	

	for (int slice = 2; slice < m + n - 1; ++slice) {
        int z1 = slice < n ? 1 : slice - n + 1;
        int z2 = slice < m ? 1 : slice - m + 1;
        int z3 = slice - z2;
        #pragma omp parallel for
        for (int j = z3; j >= z1; --j) {
			//std::cout<<omp_get_num_threads();
				if (str1[j-1] == str2[slice - j -1])
				{
					arr[j][slice - j] = arr[j-1][slice-j-1] + 1;
				}
				else {
					arr[j][slice - j] = std::max(arr[j][slice-j-1] , arr[j-1][slice-j]);
				}
			}
        }
 
std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
std::cout<<arr[l1][l2]<<std::endl;
std::chrono::duration<double> elapsed_seconds = end-start;
std::cerr<<elapsed_seconds.count()<<std::endl;

  
for(int i = 0; i < m; ++i)
free(arr[i]);
    
  free(arr);

  return 0;
}
