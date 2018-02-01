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

  if (argc < 2) {
    std::cerr<<"Usage: "<<argv[0]<<" <n>"<<std::endl;
    return -1;
  }


  int n = atoi(argv[1]);
  
  int * arr = new int [n];

  generateMergeSortData (arr, n);
  
  
  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
  for(int i=0;i<n;i++){
	  for(int j = 0;j<n-1;j++){
		  if(arr[j]>arr[j+1])
		  {
			  int temp = arr[j];
			  arr[j]=arr[j+1];
			  arr[j+1] = temp;
		  }
		}
	}	
  //write code here
  std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::cerr<<elapsed_seconds.count()<<std::endl;

  
  checkMergeSortResult (arr, n);
  
  delete[] arr;
  //free(mrg);

  return 0;
}
