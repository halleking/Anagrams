#include "anagram.h"
#include <stdio.h>
#include <stdlib.h>

/*
Halle King
hking
This is my own work. I used tutorialspoint as a reference for some c functions:
-qsort
-strcmp
-strlen
-tolower
-strcpy
*/

//StringList word: original word with capitalization
//AnagramList word: lowercase sorted

/* Create a new String List node */
struct StringList *MallocSList(char *word)
{
	struct StringList* node = NULL;
	node = (struct StringList*)malloc(sizeof(struct StringList));
	node->Word = (char *)malloc(strlen(word)*sizeof(char)+1);
	strcpy(node->Word, word);
	node->Next = NULL;
	return node;
}

/* Free a string list, including all children */
void FreeSList (struct StringList **node)
{
	//free mallocs of StringList pointers
	struct StringList* current = *node;
	struct StringList* next;
	while (current != NULL){
		next = current->Next;
		free(current->Word);
		free(current);
		current = next;
	}
}

/* Append a StringList node to the end/tail of a StringList */
void AppendSList(struct StringList **head, struct StringList *node)
{
	struct StringList* current = *head;

	while (current != NULL){
		if (current->Next == NULL){
			current->Next = node;
			break;
		}
		current = current->Next;
	}
}

/* Format output to a file according to specification. */
void PrintSList(FILE *file ,struct StringList *node)
{
	struct StringList* current = node;
	while (current != NULL){
		fprintf(file,"\t%s\n",current->Word);
		current = current->Next;
	}
}

/* Return the number of strings in the StringList. */
int SListCount(struct StringList *node)
{
	int count = 0;
	struct StringList* current = node;
	while (current != NULL){
		count++;
		current = current->Next;
	}
	return count;
}

int compare(const void* a, const void* b){
	return (*(char *)a - *(char *)b);
}	

void LowerAlphabeticalSort(char* word)
{	
	int len = strlen(word);		

	//make all char in word lowercase
	int i = 0;
	while (i < len){
		word[i] = tolower(word[i]);
		i++;
	}
	//sort using quicksort
	qsort(word, len, sizeof(char), compare);
}


/*Create a new Anagram node, store the word as sorted char array */ 
/* add StringList node with the word. */
struct AnagramList* MallocAList(char *word)
{
	//allocate memory for word and StringList node 
	struct AnagramList* node = NULL;
	node = (struct AnagramList*)malloc(sizeof(struct AnagramList));

	//create StringList of word
	node->Words = MallocSList(word);
	node->Next = NULL;

	//store word sorted and in lowercase
	char* sortedlower;
	sortedlower = (char *)malloc(strlen(word)*sizeof(char) + 1);
	strcpy(sortedlower, word);
	LowerAlphabeticalSort(sortedlower);
	node->Anagram = (char *)malloc(strlen(word)*sizeof(char)+1);
	strcpy(node->Anagram, sortedlower);
	free(sortedlower);
	return node;
}

/* Free an AnagramList, including anagram children and StringList words. */
void FreeAList(struct AnagramList **node)
{
	//free memory allocated in AnagramList
	struct AnagramList* current = *node;
	struct AnagramList* next;
	while (current != NULL){
		next = current->Next;
		free(current->Anagram);
		FreeSList(&current->Words);
		free(current);
		current = next;
	}
}

/* Format output to a file, print AnagramList with words, according to spec */
void PrintAList(FILE *file ,struct AnagramList *node)
{
	struct AnagramList* current = node;
	while (current != NULL){
		//print only if number of words in StringList is >1
		int num = SListCount(current->Words);
		if (num > 1){
			fprintf(file,"%s:%d\n", current->Anagram, num);
			//print SList corresponding to Anagram
			PrintSList(file, current->Words);
		}
		current = current->Next;
	}
}


/* Add a new word to the anagram list : Search the list and add the word */ 
/*Search with a sorted lower case version of the word. */
void AddWordAList(struct AnagramList **node , char *word)
{
	
	//create anagramlist if (*node) is Null
	if ((*node) == NULL){
		(*node) = MallocAList(word);
		return;
	}
	else{
		//search words in anagramlist, add the original word to that node's StringList if matched
		char* sortedlower;
		sortedlower = (char *)malloc(strlen(word)*sizeof(char) + 1); 
		strcpy(sortedlower, word);
		LowerAlphabeticalSort(sortedlower);


		while ((*node) != NULL){
			//if anagram is in anagramlist, append word to stringlist
			if (strcmp(sortedlower, (*node)->Anagram) == 0){
				AppendSList(&(*node)->Words, MallocSList(word));
				break;
			}
			//word is not part of current anagram family
			else{
				//if Next is NULL, add to end of anagramlist
				if ((*node)-> Next == NULL){
					(*node)->Next = MallocAList(word);
					break;
				}
				//word is not in anagramlist, add it
				else{
					node = &((*node)->Next);
			
				}
			}
		}
		free(sortedlower);
	}
}
