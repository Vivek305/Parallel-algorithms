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


#ifdef __cplusplus
extern "C" {
#endif

  void generateMergeSortData (int* arr, size_t n);
  void checkMergeSortResult (int* arr, size_t n);

  
#ifdef __cplusplus
}
#endif


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
  
  if (argc < 3) {
    std::cerr<<"Usage: "<<argv[0]<<" <n> <nbthreads>"<<std::endl;
    return -1;
  }


  int n = atoi(argv[1]);
  int nbthreads = atoi(argv[2]);
  
  int *arr = new int [n];

  generateMergeSortData (arr, n);
  
  omp_set_num_threads(nbthreads);
  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
  
   for(int d=0;d<n;d++)
   {
	   if(d%2 == 0){
		   #pragma omp parallel for
		   for(int j = 0;j<n;j+=2)
		   {
			   if(arr[j]>arr[j+1]){
				   int temp = arr[j];
				   arr[j] = arr[j+1];
				   arr[j+1] = temp;
				}
			}
		   
	   }
	   else{
		   #pragma omp parallel for
		   for(int j=1;j<n-1;j+=2)
		   {
				if(arr[j]>arr[j+1]){
				   int temp = arr[j];
				   arr[j] = arr[j+1];
				   arr[j+1] = temp;
				}		   	   	   
			}
		}
  
	}
	 
  //write code here
  std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::cerr<<elapsed_seconds.count()<<std::endl;
  
  checkMergeSortResult (arr, n);
  
  delete[] arr;
  //free(bubble);

  return 0;
}
