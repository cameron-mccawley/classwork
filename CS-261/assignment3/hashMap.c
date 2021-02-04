#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

void initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

void freeMap (struct hashMap * ht)
{  /*write this*/
	int index;
	hashLink * curr, * next;
	assert(ht);
	for(index = 0; index < ht->tableSize; index++){
		curr = ht->table[index];
		while(curr != 0){
			next = curr->next;
			free(curr->key);
			free(curr);
			curr = next;
		}
	}
	free(ht->table);
	ht->tableSize = 0;
	ht->count = 0;
}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  /*write this*/
	int hash, hashIndex;
	ValueType * val;
	hashLink * newLink;
	assert(ht);
	val = atMap(ht, k);
	if(val != NULL){
		(*val) = v;
		return;
	}
	if(HASHING_FUNCTION == 1){
		hash = stringHash1(k);
	}else if(HASHING_FUNCTION == 2){
		hash = stringHash2(k);
	}
	hashIndex = (int)(labs(hash) % ht->tableSize);
	newLink = (hashLink *)malloc(sizeof(hashLink));
	assert(newLink);
	newLink->value = v;
	newLink->key = k;
	newLink->next = ht->table[hashIndex];
	ht->table[hashIndex] = newLink;
	ht->count++;
}

ValueType* atMap (struct hashMap * ht, KeyType k)
{ /*write this?*/
	int hash, hashIndex;
	hashLink * curr;
	assert(ht);
	if(HASHING_FUNCTION == 1){
		hash = stringHash1(k);
	}else if(HASHING_FUNCTION == 2){
		hash = stringHash2(k);
	}
	hashIndex = (int)(labs(hash) % ht->tableSize);
	curr = ht->table[hashIndex];
	while(curr != NULL){
		if(strcmp(k, curr->key) == 0){
			return &(curr->value);
		}
		curr = curr->next;
	}
	return NULL;
}

int containsKey (struct hashMap * ht, KeyType k)
{  /*write this*/
	assert(ht);
	if(atMap(ht, k) == NULL){
		return 0;
	}
	return 1;
}

void removeKey (struct hashMap * ht, KeyType k)
{  /*write this?*/
	int hash, hashIndex;
	hashLink * curr, * last;
	assert(ht);
	if(HASHING_FUNCTION == 1)
		hash = stringHash1(k);
	if(HASHING_FUNCTION == 2)
		hash = stringHash2(k);

	hashIndex = (int)(labs(hash) % ht->tableSize);
	curr = ht->table[hashIndex];
	last = ht->table[hashIndex];

	while(curr != NULL){
		if(EQ(curr->key, k)){
			if(curr == ht->table[hashIndex]){
				ht->table[hashIndex] = curr->next;
			}
			last->next = curr->next;
			free(curr);
			ht->count--;
			return;
		}else{
			last = curr;
			curr = curr->next;
		}
	}
}

int sizeMap (struct hashMap *ht)
{  /*write this*/
	assert(ht);
	return ht->count;
}

int capacityMap(struct hashMap *ht)
{  /*write this*/
	assert(ht);
	return ht->tableSize;
}

int emptyBuckets(struct hashMap *ht)
{  /*write this*/
	int index, count;
	assert(ht);
	count = 0;
	for(index = 0; index < ht->tableSize; index++){
		if(ht->table[index] == NULL)
			count++;
	}
	return count;
}

float tableLoad(struct hashMap *ht)
{  /*write this*/
	float size, capacity;
	assert(ht);
	size = (float) ht->count;
	capacity = (float) ht->tableSize;
	return size / capacity;
}
