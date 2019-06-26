#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "anagram.h"

/*
Halle King
hking
This is my own work. The base code was taken from lab.
*/

int main(int argc, char *argv[])
{
	if (argc > 3){
		printf("%s\n", "Wrong number of arguments. Try again.");
		exit(0);
	}

	FILE *input=NULL, *output=NULL;
	output = stdout;
	input = stdin;

	//open input file or stdin
	if (argc >= 2){
		input = fopen(argv[1], "r");
	}
	else{
		input = stdin;
	}
	//exit if invalid
	if (input == NULL){
		exit(0);
	}

	//open output file or stdout
	if (argc == 3){
		output = fopen(argv[2], "w");
	}
	else {
		output = stdout;
	}
	//exit if invalid
	if (output == NULL){
		exit(0);
	}


	char word[1024];
	struct AnagramList* node = NULL;
	while (fgets(word, 1024, input))
	{
		//read each line as a word and remove newline char
		int len = strlen(word);
		word[len-1] = '\0';
		//add word to an existing anagram family or create a new one (addwordAlist)
		AddWordAList(&node, word);

	}
	//print Alist
	PrintAList(output, node);
	//free Alist
	FreeAList(&node);

	//close input and output file
	fclose(input);
	fclose(output);

	return 0;
}
