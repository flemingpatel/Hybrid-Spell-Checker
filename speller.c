/* PROGRAM:  tire.c 
   AUTHOR:   Fleming Patel 
   DATE:     24/04/16
   TOPIC:    Speller implementation 
   PURPOSE:   
   NOTES:   
             
*/
#define _GNU_SOURCE
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "display_usage.h"
#include<sys/resource.h>
#include<sys/time.h>
#include "dictionary.h"
#define VALID_ARGS 2
#define DELIM "­\\\t\r\n\"-!?][%/,.:;0123456789()${}_@*#&!^ "

double calculate(const struct rusage *, const struct rusage *);

int main(int argc,char *argv[]){

	struct rusage afterLoad,beforeLoad,check1,check2,unload1,unload2;

	FILE *fp;
	dictionary dict = NULL;
	static const char *string = "tnp";
	int istFound = 0;
	int isnFound = 0;
	int ispFound = 0;
	char *defaultPath = "Dictionary/dictionary_L.txt";
	int i;
	char *word;
	int lineNumber = 0;
	ssize_t read;
	size_t length = 0;
	char *line = NULL;
	int wcountDict = 0;
	int wordFOund = 0;
	int wordNot = 0;
	int size;
	char *lower;
	int j;
	int checkApo;
	int checkF;
	int checkL;
	double sumeofLoad = 0.0f;
	double sumofCheck = 0.0f;
	double sumofUnload = 0.0f;
	if(argc!=3 && argc!=2 && argc!=5 && argc!=6 && argc!=4){
		display_usage(argv[0],ARGS);
	}

	while((i=getopt(argc,argv,string))!=-1){
		switch(i){

			case 't': istFound = 1;
				break;

			case 'n': isnFound = 1;
				break;

			case 'p': ispFound = 1;
				break;
		}
	}

	if((word = (char *)malloc (MAX_WORD)) == NULL){
			perror("In optin n memory allocation");
			exit(EXIT_FAILURE);
	}
	if(optind == 2){
		getrusage(RUSAGE_SELF, &beforeLoad);
		wcountDict = load_dictionary(argv[2],&dict);
		getrusage(RUSAGE_SELF, &afterLoad);
		if((fp = fopen(argv[3],"r"))==NULL){
			perror("File open error");
			return 0;
		}

	}else if(optind == 3){
		getrusage(RUSAGE_SELF, &beforeLoad);
		wcountDict = load_dictionary(argv[3],&dict);
		getrusage(RUSAGE_SELF, &afterLoad);
		if((fp = fopen(argv[4],"r"))==NULL){
			perror("File open error");
			return 0;
		}

	}else if(optind == 4){
		getrusage(RUSAGE_SELF, &beforeLoad);
		wcountDict = load_dictionary(argv[4],&dict);
		getrusage(RUSAGE_SELF, &afterLoad);
		if((fp = fopen(argv[5],"r"))==NULL){
			perror("File open error");
			return 0;
		}
	}else if(optind == 1){
		printf("Please select an option\n");
		exit(EXIT_FAILURE);
	}else{
		getrusage(RUSAGE_SELF, &beforeLoad);
		wcountDict = load_dictionary(defaultPath,&dict);
		getrusage(RUSAGE_SELF, &afterLoad);
	}

	sumeofLoad += calculate(&beforeLoad,&afterLoad);
	while((read=getline(&line,&length,fp))!=-1){
			word = strtok(line,DELIM);	
			while(word!=NULL){
				size = strlen(word);
				lower = (char *)malloc(size + 1);
				for(j = 0;j<size;j++){
					checkApo = (int)(*(word+(size-2)));
					checkF = (int)(*(word+0));
					checkL = (int)(*(word+(size-1)));
					if((checkApo == 39) && ((checkL>=97 && checkL<=122) || (checkL>=65 && checkL<=90))){
						if(checkF!=39)				
							lower[j] = tolower(word[j]);
					}
					else if(checkF!=39 && checkApo!=39){
						lower[j] = tolower(word[j]);
					}
				}
				getrusage(RUSAGE_SELF, &check1);
				if(check_dictionary(dict,lower)){
					getrusage(RUSAGE_SELF, &check2);
					sumofCheck+=calculate(&check1,&check2);
					wordFOund++;
				}else{
					if(isnFound == 1){
						printf("%5d: %s\n", lineNumber, word );
					}
					wordNot++;
				}
			word = strtok(NULL,DELIM);
			}
			lineNumber++;
		}

	if(ispFound == 1){
		
		printf("\n***************************************************************\n");
		printf("TOTAL WORDS MISSPELLED: %d\n",wordNot);
		printf("TOTAL WORDS IN DICTIONARY: %d\n",wcountDict);
		printf("VALID WORDS IN TEXT: %d",wordFOund);
		printf("\n***************************************************************\n");
	}
	getrusage(RUSAGE_SELF, &unload1);
	unload_dictionary(&dict);
	getrusage(RUSAGE_SELF, &unload2);
	sumofUnload+=calculate(&unload1,&unload2);
	if(istFound == 1){

		printf("\n***************************************************************\n");
		printf("LOAD TIME: %f\n",sumeofLoad);
		printf("CHECK TIME: %f\n",sumofCheck);
		printf("UNLOAD TIME: %f",sumofUnload);
		printf("\n***************************************************************\n");
	}

	free(fp);
	return 0;
}

/*********************************************************************************************************************************************/

double calculate(const struct rusage *b, const struct rusage *a){
	if(b==NULL||a==NULL){
		return 0.0;
	}
		return ((((a->ru_utime.tv_sec*1000000 + a->ru_utime.tv_usec)-(b->ru_utime.tv_sec*1000000 + b->ru_utime.tv_usec))+
		((a->ru_utime.tv_sec*1000000 + a->ru_utime.tv_usec)-(b->ru_utime.tv_sec*1000000 + b->ru_utime.tv_usec)))/1000000.0);
}
