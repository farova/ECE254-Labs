/**
 * @brief: To demonstrate how to capture command line input arguments
 * To compile: gcc <file.c>
 * To execute: executable [arg1] [arg2]... 
 * EXAMPLE: ./a.out 1 2 hello
 */

#include <stdio.h>

/**
 *@brief: main function that passes command line argument paramters
 *@param: argc number of command line arguments. The executable itself
 *        is counted as one argument.
 *@param: argv char* array where each element is a command line argument.
 *        argv[0] contains the executable's name
 *        argv[1] contains the string representation of the 1st input argument
 *        argv[2] contains the string representation of the 2nd input argument
 */
int main(int argc, char *argv[]) 
{
	int i;

	for (i = 0; i < argc; i++) {
		printf("command line argument %d: %s\n", i, argv[i]);
	}
}
