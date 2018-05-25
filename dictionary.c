/* PROGRAM:  dictionary.c 
   AUTHOR:   Fleming Patel
   DATE:     24/04/16
   TOPIC:    Dictionary implementation 
   PURPOSE:   
   NOTES:   
             
*/

/**************************************************************************/
/* Declare include files
 **************************************************************************/

#include "dictionary.h"

/**************************************************************************/
/* Dictionary functions   
 * int load_dictionary ( const char *dictionay_name, dictionary dict );
 *         Loads dictionary into memory from file dictionary_name
 *         Return the number of words in the dictionary
 *                and dict points to a valid dictionary
 *                0 otherwise and dict points to NULL   
 * int check_dictionary ( dictionary dict, const char *word );
 *         Returns 1 if the word is part of the dictionary
 * int size_dictionary ( dictionary dict );
 *         Returns the number of words in the dictionary
 * int unload_dictionary ( dictionary dict );
 *         Unloads dictionary from memory
 *         Returns 1 if successful, 0 otherwise
 **************************************************************************/
int load_dictionary(const char *dictionay_name, dictionary *dict){
		
	FILE *fp;
	char *word;
	int wCount = 0;

	if((fp = fopen(dictionay_name,"r"))==NULL){
		perror("File open error");
		return 0;
	}

	if( ( word = (char *)malloc(sizeof(char ) * MAX_WORD))==NULL){
		perror("Memory allocation error");
		return 0;
	}

	while((fgets(word,MAX_WORD,fp))!=NULL){
		word[strlen(word)-1]='\0';
		if(trie_insert(dict,word)==0){
			printf("Error while Adding\n");
			return 0;
		}
		wCount++;
	}

	return wCount;
}
/**************************************************************************/
int check_dictionary  ( dictionary dict, const char *word ) {
	
	if(trie_contains(dict,(char *)word)){
		return 1;
	}
	return 0;
}
/**************************************************************************/
int size_dictionary   ( dictionary dict ) {
	return trie_size(dict);
}
/**************************************************************************/
int unload_dictionary ( dictionary *dict ) {
	return trie_destroy(dict);
}

