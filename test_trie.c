/* PROGRAM:  test_llist
   AUTHOR:   C. Ayala
   DATE:     19/03/2016
   TOPIC:     
   PURPOSE:  TEST LLIST
   NOTES:    
             
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <check.h>

#include "trie.h"
#include "test_trie.h"


#define TEST_SUCCESS "SUCCESS: All current tests passed!"
#define TEST_FAILURE "FAILURE: At least one test failed or crashed"
#define FILLER "*****************************************************************************"


/*******************************************************************/
/* Function Prototypes
 *******************************************************************/
Suite * test_suite(void);
int run_testsuite(void);

/*******************************************************************/
/* main( ) 
 *******************************************************************/
int main(int argc, char* argv[]){

    	return run_testsuite();
}


/*******************************************************************/
/* test_suit( ) 
 *******************************************************************/
Suite * test_suite(void) {
	Suite *s;
	TCase *tc_tries;
	
	s = suite_create("ALL CASES Tries");
	tc_tries = tcase_create("Tries");
	tcase_set_timeout( tc_tries, 0 );

	/***********************************************
	 * 
	 **********************************************/
   	tcase_add_test(tc_tries, test_insert );
     	tcase_add_test(tc_tries, test_contains );
   	tcase_add_test(tc_tries, test_remove );
	
	suite_add_tcase( s, tc_tries );
	

	
	
	return s;
}

/*******************************************************************/
/* run_testsuite( ) 
 *******************************************************************/
int run_testsuite(){

	int fail_nr;
	Suite *s;
	SRunner *sr;

	printf("%s\n", FILLER );
	
	s = test_suite();
	sr = srunner_create(s);
	
	srunner_run_all(sr, CK_VERBOSE);

	fail_nr = srunner_ntests_failed(sr);
	srunner_free(sr);
	printf("%s\n", FILLER );
	printf("%s\n", fail_nr ? TEST_FAILURE : TEST_SUCCESS );
	printf("%s\n", FILLER );

	return ( !fail_nr ) ? EXIT_SUCCESS : EXIT_FAILURE;
}



