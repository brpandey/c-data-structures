#include <stdlib.h> 
#include <stdio.h> 

int max_sum(int num[], int length)
{
  int sum = 0, max = 0, i; 
  int start = 0; 
  int finish = 0; 

  for (i = 0; i < length; ++i) { 

    sum += num[i]; 

    if (sum > max) 
      { 
	finish = i; // RANGE OF MAXIMUM SUB ARRAY TILL THIS POSITION 
	max = sum; 
      } 
    else if (sum < 0) 
      { 
	start = i+1; // RANGE OF MAXIMUM SUB ARRAY STARTS FROM THIS POSITION. 
	sum = 0; 
      } 
  } 

  printf("MAX SUM: From %d to %d, max sum %d\n", start, finish, max);

  return 0; 
}


int main(int argc, char* argv[])
{
  //Array containing the integers 
  int num[]= {-2,1,-3,4,-1,2,1,-5,4,2,-17,9,-2,4,5,-4}; 
  int length = 0;

  length = sizeof(num)/sizeof(int);

  max_sum(num, length);
}
