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

void mergesort(int *arr, int n, int *mrg)
{
   if (n < 2) return;

   mergesort(arr, (int)n/2, mrg);
   
  
   mergesort(arr+(n/2), n-(int)(n/2), mrg);
   merge(arr, n, mrg);
}




int main (int argc, char* argv[]) {


  if (argc < 2) {
    std::cerr<<"Usage: "<<argv[0]<<" <n>"<<std::endl;
    return -1;
  }


  int n = atoi(argv[1]);
  
  int * arr = new int [n];
  int *mrg=(int*)malloc(n * sizeof(int));

  generateMergeSortData (arr, n);
  
  //for(int i = 0;i<n;i++)
  //std::cout<<arr[i]<<" ";
  //std::cout<<std::endl;
  //std::cout<<std::endl;
  
  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
  
      mergesort(arr, n, mrg);
   
  //write code here
  std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::cerr<<elapsed_seconds.count()<<std::endl;

   //for(int i = 0;i<n;i++)
   //std::cout<<arr[i]<<" ";
  
  checkMergeSortResult (arr, n);
  
  delete[] arr;
  free(mrg);

  return 0;
}
