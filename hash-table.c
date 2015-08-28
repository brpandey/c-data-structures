#include "hash-table.h"

#define HT_ERROR  -1
#define HT_LOAD_FACTOR  5 
/* e.g. count 50 nodes / size 10 buckets */

struct hash_entry {
  char *key;
  int keysize;
  char *value;
  struct hash_entry *next;
};

struct hash_table {
  int size;  /* number of buckets*/
  int count; /* active number of elements */
  struct hash_entry **table;
};


hashtable* ht_create(int size)
{
  hashtable *ht = NULL;
  int i;

  if(size < 1) return NULL;

  /* allocate memory for the hashtable */
  ht = (hashtable*) malloc( sizeof( hashtable ) );

  if(ht == NULL) 
    {
      printf("fatal error");
      return NULL;
    }

  /* allocate an array of entry pointers */
  ht->table = (entry **) malloc( sizeof( entry *) * size );

  if(ht->table == NULL)
    {
      printf("fatal error");
      return NULL;
    }


  /* initialize array of entry pointers to NULL*/
  for(i=0; i<size; i++)
    {
      ht->table[i] = NULL;
    }

  ht->count = 0;
  ht->size = size;

  return ht;
}

int ht_hash(hashtable *ht, char *key)
{
  int i, length, hash_index = -1;
  unsigned int hash_value = 0;

  length = strlen(key);

  if(ht == NULL || key == NULL)
    {
      printf("fatal error");
      return HT_ERROR;
    }

  /* 
   * For each character, we multiply the hash by 257 (prime) 
   * and add the current character back to the hash.
   * Shifting a number left is equivalent to 
   * multiplying it by 2 raised to the number of places shifted.
   * Shifting and addition are much more 
   * efficient operations than multiplication.
   */

  for(i=0; i < length; i++)
    {
      hash_value = ((int) key[i]) + (hash_value << 8) + hash_value;
    }

  /* return the hash value mod the table size so it will fit the appropriate range*/

  hash_index = hash_value % ht->size;

  return hash_index;
}


char* ht_lookup(hashtable *ht, char *key)
{
  int hash_index, length;
  entry *current = NULL;

  /* null checks */
  if(ht == NULL || key == NULL) 
    {
      printf("fatal error");
      return NULL;
    }

  length = strlen(key);

  /* hash key value */
  hash_index = ht_hash(ht, key);

  /*
    printf("ht_lookup: hash index for key %s, is %d\n", key, hash_index);
  */

  /* retrieve head of the chain of unvisited entries */
  current = ht->table[hash_index];

  for(; current != NULL; current = current->next)
    {
      printf("ht_lookup: current node keysize %d, key %s, value %s\n",
	     current->keysize, current->key, current->value);

      /* using a check on keysize speeds up our search */
      if(current->keysize == length && 
	 memcmp(current->key, key, length) == 0)
	{
	  return current->value;
	}
    }

  return NULL;
}

bool ht_insert(hashtable *ht, char *key, char *value)
{
  int hash_index = 0, load_factor = 0;
  entry *insert = NULL;

  /* null checks */
  if(ht == NULL || key == NULL || value == NULL || ht->table == NULL)
    {
      printf("fatal error");
      return false;
    }

  /* check if the key/value already exists */
  if(ht_lookup(ht, key) != NULL)
    {
      printf("key already exists, insert aborted");
      return false;
    }

  /* create the new insert entry node */
  insert = (entry *) malloc( sizeof(entry) );

  if(insert == NULL)
    {
      printf("fatal error");
      return false;
    }

  /* populate the new insert node's fields */
  insert->key = strdup(key);
  insert->value = strdup(value);
  insert->keysize = strlen(key);
  insert->next = NULL;

  hash_index = ht_hash(ht, key);

  /* put insert at the front of the chain*/
  insert->next = ht->table[hash_index];
  ht->table[hash_index] = insert;

  printf("ht_insert: inserted node at index (%d), key is (%s), \
value is (%s), keysize is (%d)\n", \
	 hash_index, insert->key, insert->value, insert->keysize);

  ht->count++;

  ht_checkload(ht);

  return true;
}

bool ht_checkload(hashtable *ht)
{
  int load_factor;

  if(ht == NULL)
    {
      printf("fatal");
      return false;
    }

  load_factor = ht->count / ht->size;

  if(load_factor > HT_LOAD_FACTOR)
    {
      printf("(Need to rehash, %d / %d)\n", ht->count, ht->size);
      ht_rehash(ht);
      return true;
    }

  return false;
}

void ht_rehash(hashtable *ht)
{
  int i, old_size, old_count, hash_index;
  entry **old_table = NULL;
  entry *previous = NULL, *current = NULL;

  /* null checks */
  if(ht == NULL)
    {
      printf("fatal error");
      return;
    }

  old_size = ht->size;
  old_table = ht->table;

  /* the ht->count will be the same */

  ht->size = ht->size*2;
  
  /* create new table structure */
  ht->table = (entry **) malloc(ht->size * sizeof(entry *));

  if(ht->table == NULL)
    {
      printf("fatal error");
      return;
    }

  printf("ht_rehash: REHASHING! old size: %d, new size: %d \n", old_size, ht->size);

  /* rehash existing elements given new table size */
  for(i = 0; i < old_size; i++)
    {
      previous = old_table[i];
      
      /* for each element in the chain, rehash and put in new table */
      while(previous != NULL)
	{
	  current = previous->next;
	  
	  hash_index = ht_hash(ht, previous->key);

	  /* put in new hashtable */
	  previous->next = ht->table[hash_index];
	  ht->table[hash_index] = previous;

	  previous = current;
	}
    }

  free(old_table);
}

bool ht_entrydelete(hashtable *ht, char *key)
{
  int hash_index = -1, length = 0;
  entry *previous = NULL, *current = NULL, *head = NULL;

  /* null checks */
  if(ht == NULL || key == NULL)
    {
      printf("fatal error");
      return false;
    }

  /*
    if(ht_lookup(ht, key) == NULL) return false;
  */

  hash_index = ht_hash(ht, key);
  head = (entry*) ht->table[hash_index];
  length = strlen(key);
  
  if(head == NULL) 
    {
      return false;
    }

  if(head != NULL && 
     head->keysize == length && 
     (memcmp(head->key, key, length) == 0))
    {
      ht->table[hash_index] = NULL;
      free(head->key);
      free(head->value);
      free(head);
      ht->count--;
      return true;
    }

  previous = head;
  current = head->next;

  while(current != NULL)
    {
      if(current->keysize == length && 
     (memcmp(current->key, key, length) == 0))
	{
	  previous->next = current->next;

	  free(current->key);
	  free(current->value);
	  free(current);

	  ht->count--;
	  return true;
	}

      previous = current;
      current = current->next;
    }
  
  return false;
}

void ht_delete(hashtable *ht)
{
  int i;
  entry *current = NULL, *previous = NULL;

  /* for each bucket, walk through the chain deleting */
  if(ht == NULL)
    {
      printf("fatal error");
      return;
    }

  for(i = 0; i < ht->size; i++)
    {
      previous = ht->table[i];

      /* don't bother about the dangling refs from the ht->table
         we will free the table soon
      */

      /* walk through the list, deleting, using prev and curr */
      while(previous != NULL)
	{
	  current = previous->next;
	  free(previous->key);
	  free(previous->value);
	  free(previous);
	  previous = current;
	}
    }

  /* free the structure representing the hash table */
  free(ht->table);
  free(ht);
}

int main(int argc, char *argv[])
{
  hashtable *ht = NULL;

  ht = (hashtable*) ht_create(7);

  printf("\n\nStatus: Inserting key \"blue\"\n");
  ht_insert(ht, "blue", "wallet");

  printf("\n");
  printf("Query: What is the value of the blue key in the ht? %s\n", 
	 ht_lookup(ht, "blue"));

  printf("\n\nStatus: Inserting key \"brown\"\n");
  ht_insert(ht, "brown", "magazine");

  
  /* let's see if the rehash works and other things :) */

  printf("\n\nStatus: Inserting a bunch of keys....\n");
  ht_insert(ht, "magenta", "polygon");
  ht_insert(ht, "black", "crow");
  ht_insert(ht, "turqoise", "iguana");
  ht_insert(ht, "red", "pizza");
  ht_insert(ht, "margherita", "pizza");
  ht_insert(ht, "navy-blue", "shirt");
  ht_insert(ht, "rimmed-purple", "hat");
  ht_insert(ht, "lime", "book cover");
  ht_insert(ht, "fluorescent", "headlights");
  ht_insert(ht, "walkie talkie", "black");
  ht_insert(ht, "green yellow", "palm trees");
  ht_insert(ht, "honda", "coupe");
  ht_insert(ht, "toyota", "camry");
  ht_insert(ht, "acid washed", "jeans");
  ht_insert(ht, "relaxing", "day spa");
  ht_insert(ht, "delicious", "pizza");
  ht_insert(ht, "slice", "pizza");
  ht_insert(ht, "white checkered", "shorts");
  ht_insert(ht, "black1", "crow-a");
  ht_insert(ht, "black2", "crow-b");
  ht_insert(ht, "black3", "crow-c");
  ht_insert(ht, "black4", "crow-d");
  ht_insert(ht, "black5", "crow-e");
  ht_insert(ht, "black6", "crow-f");
  ht_insert(ht, "black7", "crow-g");
  ht_insert(ht, "black8", "crow-h");
  ht_insert(ht, "black9", "crow-i");
  ht_insert(ht, "black10", "crow-j");
  ht_insert(ht, "black11", "crow-k");
  ht_insert(ht, "black12", "crow-l");
  ht_insert(ht, "black13", "crow-m");
  ht_insert(ht, "black14", "crow-n");
  ht_insert(ht, "black15", "crow-o");
  ht_insert(ht, "black16", "crow-p");
  ht_insert(ht, "black17", "crow-q");
  ht_insert(ht, "black18", "crow-r");
  ht_insert(ht, "black19", "crow-s");
  ht_insert(ht, "black20", "crow-t");
  ht_insert(ht, "black21", "crow-u");
  ht_insert(ht, "black22", "crow-v");
  ht_insert(ht, "black23", "crow-w");
  ht_insert(ht, "black24", "crow-x");
  ht_insert(ht, "black25", "crow-y");
  ht_insert(ht, "black26", "crow-z");
  ht_insert(ht, "job", "happy");



  printf("\n\nStatus: Inserting key \"white\"\n");
  ht_insert(ht, "white", "mouse");

  printf("\n");
  printf("Query: What is the value of the yellow key in the ht? %p\n", 
	 ht_lookup(ht, "yellow"));

  printf("\n\nStatus: Inserting key \"yellow\"\n");
  ht_insert(ht, "yellow", "light");

  printf("\n");
  printf("Query: What is the value of the yellow key in the ht? %p\n", 
	 ht_lookup(ht, "yellow"));

  printf("\n\nStatus: Deleting key \"yellow\"\n");
  ht_entrydelete(ht, "yellow");

  printf("\n");
  printf("Query: What is the value of the yellow key in the ht? %p\n", 
	 ht_lookup(ht, "yellow"));

  printf("\n");
  printf("Query: What is the value of the red key in the ht? %s\n", 
	 ht_lookup(ht, "red"));

  printf("\n\nStatus: Inserting key \"grey\"\n");
  ht_insert(ht, "grey", "carpet");

  printf("\n\nStatus: Inserting key \"red\"\n");
  ht_insert(ht, "red", "adventure novel");

  printf("\n");
  printf("Query: What is the value of the red key in the ht? %s\n", 
	  ht_lookup(ht, "red"));

  printf("\n\nStatus: Inserting key \"purple\"\n");
  ht_insert(ht, "purple", "Danielle Steele");

  printf("\n");
  printf("Query: What is the value of the brown key in the ht? %s\n", 
	 ht_lookup(ht, "brown"));


  ht_delete(ht);
}
