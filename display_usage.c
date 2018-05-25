/*
 *  display_usage( )
 *  C. Ayala
 *  CST8234
 *
 */
#include <stdlib.h>
#include "display_usage.h"

/*********************************************************************
 * display_usuage
 ********************************************************************/
void display_usage( char * prog, char *opts ) {

	fprintf(stderr, "usage: %s %s\n", prog, opts );
	exit( EXIT_FAILURE );

}
