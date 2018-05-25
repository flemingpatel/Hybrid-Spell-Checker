/* PROGRAM:  dictionary.h
   AUTHOR:   C. Ayala
   DATE:     01/04/16
   TOPIC:    Trie implementation 
   PURPOSE:   
   NOTES:   
             
*/
#ifndef __DICTIONARY_H
#define __DICTIONARY_H
#include "trie.h"

/**************************************************************************/
/* Declare include files
 **************************************************************************/
typedef trie_node_t *dictionary;

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
int load_dictionary   ( const char *dictionay_name, dictionary *dict );
int check_dictionary  ( dictionary dict, const char *word );
int size_dictionary   ( dictionary dict );
int unload_dictionary ( dictionary *dict );

#endif
