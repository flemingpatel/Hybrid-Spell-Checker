/* PROGRAM:  tire.c 
   AUTHOR:   Fleming Patel 
   DATE:     24/04/16
   TOPIC:    trie implementation 
   PURPOSE:   
   NOTES:   
             
*/

/**************************************************************************
 * Declare include files
 **************************************************************************/
#include "trie.h"
#include <string.h>
#include <ctype.h>
/**************************************************************************
 * Helper Functions
 * trie_node_t * trie_new(  void );
 *         Allocates memory for a new trie node
 *         Returns NULL if memory allocation was not possible or
 *         a memory address to a trie_node in the heap
 **************************************************************************/
trie_node_t * trie_new(  void ){
	
	trie_node_t * tmp = NULL;
	int i;
	
	if ( ( tmp = ( trie_node_t * ) malloc ( sizeof( trie_node_t ) ) ) == NULL )
		return NULL;

	for( i = 0; i < ALPHA_SIZE; i++ ) { 
		tmp->child[ i ] = NULL;
		tmp->end = 1;
	}
	return tmp;
}

/**************************************************************************
 * Functions functions       
 * int trie_size     ( trie_node_t *  root );
 *         Returns the number of words in the trie
 * int trie_contains ( trie_node_t *  root,    char word[ ] );
 *         Returns 1 if a the word is in the trie
 *                 0 otherwise
 * int trie_insert   ( trie_node_t ** rootRef, char word[ ] );
 *         Returns 1 if the word is inserted in the trie
 *                 0 otherwise
 * int trie_remove  ( trie_node_t ** rootRef, char word[ ] );
 *         Returns 1 if the word is removed from the trie
 *                 0 otherwise
 * int trie_destroy  ( trie_node_t ** Tref );
 *         Returns 1 if the trie and all its node are destroyed
 **************************************************************************/
int trie_size( trie_node_t *  root ) {

	int count = 0;
	int i = 0;
	trie_node_t *temp = root;
	if (root == NULL){
		return count;
	}
	for(i = 0; i < ALPHA_SIZE; i++){
		
		if(temp->child[i] != NULL){
			if(temp->child[i]->end == '\0'){
				count++;
			}
			count += trie_size(temp->child[i]);
		}
	}
	return count;
}
/**************************************************************************/
int trie_contains ( trie_node_t *  root,    char word[ ] ){
	
	int i;
	int letter;
	trie_node_t *tmp = root;
	for(i=0;i<strlen(word);i++){
		letter = charToInt(word[i]);
		if(letter==-1){
			return 0;
		}
		tmp = tmp->child[letter];
		
		if(!tmp){
			return 0;
		}
	}
	return 1;
}
/**************************************************************************/
int trie_insert ( trie_node_t ** rootRef, char word[ ] ){

	int len = strlen(word);
	int i=0, index=0;
	trie_node_t *tmp = *rootRef;
	if (tmp == NULL){
		*rootRef = trie_new();
		tmp = *rootRef;
	}

	for (i=0;i<len;i++) {
			if (word[i] >= 'A' || word[i] <= 'Z') {
				index = charToInt(word[i]);
			}
			if (!tmp->child[index]) tmp->child[index] = trie_new();
			tmp = tmp->child[index];
	}

	if(tmp == NULL){
		return 0;
	}
	tmp->end='\0';
	return 1;
}
/**************************************************************************/
int trie_remove  ( trie_node_t ** rootRef, char word[ ] ){

	int i,index;
	int length = strlen(word);
	trie_node_t *tmp = *rootRef;
	trie_node_t *local;
	if(tmp == NULL){
		return 0;
	}
	for(i=0;i<length;i++){
		index = charToInt(word[i]);
		if(tmp->child[index]!=NULL){
			if(trie_contains(tmp,word) == 1){
				local = tmp->child[index];
				tmp = local;
			}
			else if(tmp->child[index]->end!='\0') {
				local = tmp->child[index];
				tmp = local;
			}
			else{
				tmp->child[index] = NULL;
			}

		}
	}
	
	return 1;	
}
/**************************************************************************/
int trie_destroy  ( trie_node_t ** rootRef ){
	int i;
	trie_node_t *tmp = *rootRef;
    	if(tmp==NULL){
    		return 0;
    	}
    	for(i=0;i<ALPHA_SIZE;i++){
    		if(tmp->child[i]!=NULL){
			if(trie_size(tmp->child[i])>0){
				trie_destroy(&(tmp->child[i]));
			}
			free(tmp->child[i]);
	   	}
    	}
	free(tmp);
	*rootRef = NULL;

    	return 1;
}
/**************************************************************************/
int charToInt(char c) {
    return c-'a';
}
