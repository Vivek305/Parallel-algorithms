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
#include <math.h>



int main (int argc, char* argv[]) {

  //forces openmp to create the threads beforehand
  
  if (argc < 3) {
    std::cerr<<"Usage:"<<argv[0]<<"<String1 length> <String 2 length>"<<std::endl;
    return -1;
  }
 
  int m = atoi(argv[1]);
  int n = atoi(argv[2]);
  char str1[m];
  char str2[n];
  for(int i =0;i<m;i++){
	  str1[i] = "abcdefghijklmnopqrstuvwxyz"[rand()%26];
  }
  for(int i =0;i<n;i++){
	  str2[i] = "abcdefghijklmnopqrstuvwxyz"[rand()%26];
  }
  
  
  int** arr = (int**)malloc((m+1) * sizeof(int*));
  
  for(int i = 0; i <= m; ++i)
  arr[i] = (int*)malloc((n+1)* sizeof(int));
  
	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

	for(int i =0;i<=n;i++)
	arr[0][i] = 0;

	for(int i=0;i<=m;i++)
	arr[i][0] = 0;
	
	for(int a=1;a<=m;a++){
		for(int b=1;b<=n;b++){
			if(str1[a-1] == str2[b-1]){
				arr[a][b] = arr[a-1][b-1]+1;
			}else{
				arr[a][b] = std::max(arr[a][b-1],arr[a-1][b]);
			}
		}
	}
	
std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
std::cout<<arr[m][n]<<std::endl;
std::chrono::duration<double> elapsed_seconds = end-start;
std::cerr<<elapsed_seconds.count()<<std::endl;

  
for(int i = 0; i <= m; ++i)
delete[] arr[i];
    
  delete[] arr;

  return 0;
}
