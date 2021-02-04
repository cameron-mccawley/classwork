#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashMap.h"

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers seperated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file); /* prototype */

/****************************************/

int main (int argc, const char * argv[]) {
    /*Write this function*/
    char * word;
    const char * file;
    int index, tableSize;
    hashMap map;
    FILE * filePtr;
    tableSize = 100;
    if(argc != 2){
        printf("Error, no filename provided");
        return -1;
    }
    file = argv[1];
    filePtr = fopen(file, "r");
    assert(filePtr);
    initMap(&map, tableSize);
    while(1){
        word = getWord(filePtr);
        if(word == NULL)
            break;
        if(containsKey(&map, word) == 0){
            insertMap(&map, word, 1);
        }else{
            (*atMap(&map, word))++;
        }
    }
    
    for(index = 0; index < map.tableSize; index++){
        if(map.table[index] != NULL){
            printf("%s: %d\n", map.table[index]->key, map.table[index]->value);
        }
    }

    freeMap(&map);
    fclose(filePtr);
    return 0;
}

char* getWord(FILE *file)
{
	
	int length = 0;
	int maxLength = 16;
	char character;
    
	char* word = (char*)malloc(sizeof(char) * maxLength);
	assert(word != NULL);
    
	while( (character = fgetc(file)) != EOF)
	{
		if((length+1) > maxLength)
		{
			maxLength *= 2;
			word = (char*)realloc(word, maxLength);
		}
		if((character >= '0' && character <= '9') || /*is a number*/
		   (character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
		   (character >= 'a' && character <= 'z') || /*or a lowercase letter*/
		   character == 39) /*or is an apostrophy*/
		{
			word[length] = character;
			length++;
		}
		else if(length > 0)
			break;
	}
    
	if(length == 0)
	{
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}