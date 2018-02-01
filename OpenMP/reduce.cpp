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


int sum(int begin,int end, int* arr,int thres,int* s)
{
	int r,l;
	if((end-begin) <= thres) //return arr[0];
	{
		int sm = 0;
		for(int i=begin;i<=end;i++)
		sm=sm+arr[i];
		return sm;
		//return r;
	}
	else{
		#pragma omp task  
		 *s+=sum(begin,end-thres,arr,thres,s);
				
		#pragma omp task
		 *s+=sum(end-thres+1,end,arr,thres,s);
		
		#pragma omp taskwait
		
		return 0;
		
	}
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
	
	generateReduceData (arr, n);
	
	int cnk_s = n / nbthreads;
	
	int s=0;
	omp_set_num_threads(nbthreads);
	
std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

#pragma omp parallel 
{
	
	#pragma omp single
	{
		sum(0,n-1,arr,cnk_s/4,&s);	
	}
}
		
std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
std::chrono::duration<double> elapsed_seconds = end-start;

std::cout<<s<<std::endl;
std::cerr<<elapsed_seconds.count()<<std::endl;

  delete[] arr;

  return 0;
}
