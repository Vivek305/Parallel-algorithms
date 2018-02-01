#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>
#include <string.h>
#include <omp.h>

#ifdef __cplusplus
extern "C" {
#endif

  void generateReduceData (int* arr, size_t n);
  
#ifdef __cplusplus
}
#endif


int sum(int begin , int end , int* arr)
{
	int sum=0;
	for(int i = begin;i<end;i++)
	sum += arr[i];
	
	return sum;
}


int main (int argc, char* argv[]) {

  if (argc < 2) {
    std::cerr<<"Usage: "<<argv[0]<<" <n>"<<std::endl;
    return -1;
  }
	
	int n = atoi(argv[1]);
	int * arr = new int [n];
	
	generateReduceData (arr, n);
	 		
	int s=0;
	
std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

s = sum(0 , n , arr);

std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
std::chrono::duration<double> elapsed_seconds = end-start;

std::cout<<s<<std::endl;
std::cerr<<elapsed_seconds.count()<<std::endl;

  //write code here  
  delete[] arr;

  return 0;
}

