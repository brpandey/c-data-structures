#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* reverse(char* str_arrow)
{
  char *start_arrow, *end_arrow, temp;
  char *orig_arrow;

  int size = 0;

  if(str_arrow == NULL || *str_arrow == '\0') return NULL;

  size = strlen(str_arrow);

  if(size > 0)
    {
      end_arrow = str_arrow + size - 1;
    }
  else
    {
      end_arrow = str_arrow;
    }

  for(start_arrow = str_arrow; start_arrow < end_arrow; ++start_arrow, --end_arrow)
    {
      temp = *start_arrow;
      *start_arrow = *end_arrow;
      *end_arrow = temp;
    }

  return str_arrow;

}


int main(int argc, char* args[])
{
  char str[] = "abcdefghijklmnopqrstuvwxyz\0";
  printf("reverse: %s\n", reverse(str));
}
