#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct hash_entry entry;
typedef struct hash_table hashtable;

hashtable* ht_create(int size);
int ht_hash(hashtable *ht, char *key);
char* ht_lookup(hashtable *ht, char *key);
bool ht_insert(hashtable *ht, char *key, char *value);

bool ht_checkload(hashtable *ht);
void ht_rehash(hashtable *ht);

bool ht_entrydelete(hashtable *ht, char *key);
void ht_delete(hashtable *ht);



#endif
