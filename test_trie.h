/***************************************************************************/
/*
 * TEST:  
 */
START_TEST ( test_insert ) {
  
   	trie_node_t *root = NULL;
   	
   	ck_assert( trie_size( root ) == 0 );
   	trie_insert( &root, "a" );
   	trie_insert( &root, "any" );
   	trie_insert( &root, "answer" );
   	ck_assert( trie_size( root ) == 3 );
  	
}
END_TEST

START_TEST ( test_contains ) {
   
  	trie_node_t *root = NULL;
   	
   	ck_assert( trie_size( root ) == 0 );
   	trie_insert( &root, "a" );
   	trie_insert( &root, "any" );
   	trie_insert( &root, "answer" );
   	ck_assert( trie_size( root ) == 3 );
   	
   	ck_assert( trie_contains( root, "a" ) );
   	ck_assert( !trie_contains( root, "aaa" ) );
}
END_TEST

START_TEST ( test_remove ) {
   
    	trie_node_t *root = NULL;
   	
   	ck_assert( trie_size( root ) == 0 );
   	trie_insert( &root, "a" );
   	trie_insert( &root, "any" );
   	trie_insert( &root, "answer" );
   	ck_assert( trie_size( root ) == 3 );
   	ck_assert( trie_contains( root, "any" ) );
   	
   	trie_remove( &root, "any" );
   	ck_assert( trie_size( root ) == 2 );
   	ck_assert( !trie_contains( root, "any" ) );
}
END_TEST
