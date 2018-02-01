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


void merge(int *arr, int n, int *mrg) {
   int i = 0;
   int j = n/2;
   int m = 0;

   while (i<n/2 && j<n) {
      if (arr[i] < arr[j]) {
         mrg[m] = arr[i];
         m++; i++;
      } else {
         mrg[m] = arr[j];
         m++; j++;
      }
   }
   while (i<n/2) { 
      mrg[m] = arr[i];
      m++; i++;
   }
      while (j<n) { 
         mrg[m] = arr[j];
         m++; j++;
   }
   std::memcpy(arr, mrg, n*sizeof(int));
   
}

void mergesort(int *arr, int n, int *mrg,int thres)
{
   if (n < 2) return;
   
   if(n>=thres){
	   #pragma omp task
	   mergesort(arr, (int)n/2, mrg,thres);
	   
	   #pragma omp taskwait 

	   #pragma omp task
	   mergesort(arr+(n/2), n-(int)(n/2), mrg,thres);
	 
	   #pragma omp taskwait
   }
   else{
	   mergesort(arr, (int)n/2, mrg,thres);
	   mergesort(arr+(n/2), n-(int)(n/2), mrg,thres);
	  }
	 
   merge(arr, n, mrg);
}




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
  
  int * arr = new int [n];
  int *mrg=(int*)malloc(n * sizeof(int));

  generateMergeSortData (arr, n);
  
  int cnk_s = n / nbthreads;
  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
  omp_set_num_threads(nbthreads);
   #pragma omp parallel
   {
      #pragma omp single
      mergesort(arr, n, mrg,cnk_s);
   }
   
  //write code here
  std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::cerr<<elapsed_seconds.count()<<std::endl;
  
  checkMergeSortResult (arr, n);
  
  delete[] arr;
  free(mrg);

  return 0;
}
