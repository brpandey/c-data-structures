#include <stdio.h>
#include <string.h>


/* backtracking is a method of exhaustive search
   using divide and conquer
   
   - sometimes the best alg is trying all possibilities
   - speeds exhaustive search by pruning
*/

void binary(int n, char bucket[])
{
  if(n < 1)
    {
      printf("binary: %s\n", bucket);
    }
  else
    {
      bucket[n - 1] = '0';
      binary(n - 1, bucket);

      bucket[n - 1] = '1';
      binary(n - 1, bucket);
    }
}

void kstring(int n, int k, char bucket[])
{
  int j;

  if(n < 1)
    {
      printf("k-string: %s\n", bucket);
    }
  else
    {
      for(j=0; j < k; j++)
	{
	  bucket[n-1] = j + '0';
	  kstring(n-1, k, bucket);
	}
    }
}


int main(int argc, char* argv[])
{
  int n = 2;
  char bucket[n];

  bucket[n] = '\0';

  binary(n, bucket);
  kstring(n, 3, bucket);
}
