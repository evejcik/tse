/* 
 * query.c --- 
 * 
 * Author: Matthew J. Sebastian
 * Created: 11-01-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include "pageio.h" 
#include "webpage.h"
#include "queue.h"
#include "hash.h"


//Checks the validity of the input word and makes it lowercase
bool cleanWord(char* w){
	char c;
	for(int i = 0; i < strlen(w); i++){
		c = w[i];
		if(!isalpha(c) && !isspace(c)){
			return true;
		}
		else{
			w[i] = tolower(c);
		}
	}
	return false;
}

int main(void){
	char *inputList[10];
	char rawInput[100];
	int numWords;
	//bool invalidQuery = false;

	//inputWord = (char *)malloc(sizeof(char));
	while(true){
		//invalidQuery = false;
		//if -q is (not) present...then do....
		printf(">");
		numWords = 0;

		//Checks if the user ends the program with ctrl+d and saves the
		if(fgets(rawInput, 100, stdin) == NULL){
			printf("Querier terminated\n");
			break;
		}
		
		if (strlen(rawInput) <= 1) {
			continue; // Skip further processing
		}
		
		size_t len = strlen(rawInput);
		if (len > 0 && rawInput[len - 1] == '\n') {
			rawInput[len - 1] = '\0';
		}

		if(cleanWord(rawInput)){
				printf("Invalid query\n");
				//	invalidQuery = true;
				continue;
			}	
		// Tokenize the input and store words in inputList
		char *inputWord = strtok(rawInput, " ");
		while (inputWord != NULL) {
			//			if (cleanWord(inputWord)) {
				inputList[numWords] = inputWord;
				numWords++;
				inputWord = strtok(NULL, " ");  // Move to the next word
				//} else {
				//invalidQuery = true;
				//break;
				//}
		}

			//if (invalidQuery) {
			//printf("Invalid query\n");
			//break;
			//}
		//Prints out the cleaned user input
		for(int i = 0; i < numWords - 1; i++){
			//printf("entered printing loop\n");
			printf("%s ", inputList[i]);
		}
		printf("%s \n", inputList[numWords -1]);
	}
	
	
}
