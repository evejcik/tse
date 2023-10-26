/* 
 * indexer.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-24-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <webpage.h>
#include <queue.h>
#include <hash.h>
#include <unistd.h>
#include <sys/stat.h>  
#include <pageio.h>

//Step 2
void NormalizeWord(char* word){
	if (strlen(word) < 3){
    return false;
	}
	
	if(!isalpha(word[i])){                                                     
		return false;                                                            
	}
	word[i] = tolower(word[i]);	
}


//Step 3: Hash Table of Words
void updateWordCount(hashtable_t *htp, const char *word) {
	word_count_t *entry = (word_count_t *)hsearch(htp, NULL, word, strlen(word));
	if (entry == NULL) {
		// Word not found, create a new entry
		entry = (word_count_t *)malloc(sizeof(word_count_t));
		strncpy(entry->word, word, sizeof(entry->word));
		entry->count = 1;
		hput(htp, entry, word, strlen(word));
	} else {
		// Word found, update the count
		entry->count++;
	}
}


int main(int argc, char *argv[]){
	//char* pages[200];

	//	printf("hello");
	webpage_t* page = pageload(1, "pages");

	int pos = 0;
	char *result = NULL;

	char *word = NULL;
	//	int pos = 0;
		
	// Loop to extract and print words
	while (webpage_getNextWord(page, pos, &word) > 0) {
		printf("%s\n", NormalizeWord(word));  // Print the extracted word
		free(word);  // Free the memory allocated by webpage_getNextWord
	}
	
	// Free the webpage when you're done
	webpage_delete(page);
	
}
