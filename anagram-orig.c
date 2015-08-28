#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0

bool is_anagram(char* str1, char* str2)
{
  int lookup[26], tmp[26];
  char *first;
  char *second;

  memset(lookup, 0, 26*sizeof(int));
  memset(tmp, 0, 26*sizeof(int);

  if(str1 == NULL || str2 == NULL)
    {
      printf("Error");
      return false;
    }

  for(first = str1; *first != ‘\0’; first++)
    {
      lookup[*first]++;
    }

  for(second = str2; *second != ‘\0’; second++)
    {
      lookup[*second]—-;
    }

  //check that the lookup int array only contains 0s
   if(memcmp(lookup, 0, 26*sizeof(int)) == 0)
    {
      return true;
    }

    return false;
}

int main()
{
  bool case1 = is_anagram(“Add”,”Dad”);
  bool case2 = is_anagram(“Doctor Who”, “Torchwood”);
}
