#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef int bool;
#define true 1
#define false 0

bool is_anagram(char* str1, char* str2)
{
	int table_size = 26;
	int lookup[table_size], tmp[table_size];
	char *first, *second;
	char key;

	memset(lookup, 0, table_size*sizeof(int));
	memset(tmp, 0, table_size*sizeof(int));

	if(str1 == NULL || str2 == NULL)
	{
		printf("Error");
		return false;
	}

	for(first = str1; *first != '\0'; first++)
	{
		key = (int) toupper(*first);
		//printf("str1: char %c, int %d \n", key, key);
		
		if (isupper(key) == true) lookup[key]++;
	}

	for(second = str2; *second != '\0'; second++)
	{
		key = (int) toupper(*second);
		//printf("str1: char %c, int %d \n", key, key);

		if (isupper(key) == true) lookup[key]--;
	}

	//check that the lookup int array only contains 0s
	if(0 == memcmp(lookup, tmp, table_size*sizeof(int)))
	{
		return true;
	}

	return false;
}

int main()
{
	bool case1, case2;

	case1 = is_anagram("Add","Dad");
	case2 = is_anagram("Doctor Who", "Torchwood");

	printf("Anagram, Case1: %d Case2: %d\n", case1, case2);
}
