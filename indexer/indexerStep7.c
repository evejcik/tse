/* 
 * indexer.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-28-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "webpage.h"
#include "pageio.h"                                                                   
#include <string.h>                                                                   
#include <ctype.h>                                                                   
#include <string.h>                                                                   
#include <stdbool.h>                                                                  
#include "hash.h"                                                                     
#include "queue.h"
#include "indexio.h"

int sum = 0;
/*
typedef struct indexEntry{                                                            
  char* givenWord;                                                                    
  int count;                                                                          
}indexEntry_t;

typedef struct hElement{
	char *word;
	queue_t *queue;
}hElement_t;

typedef struct qElement{
	int id;
	int wordCount;
}qElement_t;
*/

qElement_t *makeqElement(int id, int wc){
	qElement_t *result = (qElement_t *)malloc(sizeof(qElement_t));
	result->id = id;
	result->wordCount = wc;
	return result;
}
hElement_t *makehElement(char *w, qElement_t *qp){
	hElement_t *result = (hElement_t *)malloc(sizeof(hElement_t));
	result->word = w;
	result->queue = qp;
	return result;
}
                                                                         
bool matchingWordsSearch(void* elementp, const void* searchkeyp) {                   
  hElement_t *givenEntry = (hElement_t*) elementp;                                 
  const char *key = (const char*) searchkeyp;                                        
  if(elementp == NULL) {                                                             
    return false;                                                                    
  }                                                                                  
  if(strcmp((givenEntry -> word), key) == 0) {                                    
    return true;                                                                     
  }                                                                                  
  return false;                                                                      
}

bool matchingIdSearch(void *elementp, const void *searchId){
	qElement_t *givenEntry = (qElement_t *) elementp;
	const int *givenId = (int *) searchId;
	if(elementp == NULL){
		return false;
	}
	if((givenEntry->id) == *givenId){
		return true;
	}
	else{
		return false;
	}
}

/*                                               
                                                                                     
void printh(void* elementp) {                                                         
  indexEntry_t *entry = (indexEntry_t*) elementp;                                     
  char* printWord = entry -> givenWord;                                               
  int printCount = entry -> count;                                                    
  printf("%s , %d \n ", printWord, printCount);                                       
}                                                                                     
                                     */                                                 
char* NormalizeWord(char* word){                                                      
  int cCounter;                                                                       
  char c;                                                                             
  // Check is word is greater than 3 characters                                       
  int wordLen = strlen(word);                                                         
  if (wordLen < 3){                                                                   
    return NULL;                                                                      
  }                                                                                   
                                                                                      
  // Check is word contains alphanumeric characters                                   
  for ( cCounter = 0; cCounter < wordLen; cCounter++){                                
    c = word[cCounter];                                                               
    if ( (isalpha(c)) == 0 ){                                                         
      return NULL;                                                                    
    }                                                                                 
  }                                                                                   
  // Check if word  is uppercase                                                      
  for ( cCounter = 0; cCounter < wordLen; cCounter++){                                
    c = tolower(word[cCounter]);                                                      
    word[cCounter] = c;                                                               
  }                                                                                   
  return word;                                                                        
}                                                                                     
                                                                                      
void wordCounterQueue(void *ep){
	qElement_t *element = (qElement_t *) ep;
	sum += element->wordCount;
	//printf("%d\n", element->wordCount);
}
void wordCounterHash(void* ep) {                                                      
  hElement_t *element = (hElement_t*) ep;                                          
  if (element == NULL) {                                                              
    return;                                                                           
  }                                                                                   
  qapply(element->queue, wordCounterQueue);
	//sum++;
}                                                                                     
                                                                                      
void freeHash(void *ep) {                                                         
  hElement_t* entry  = ep;                                                           
  char* word = entry -> word;                                                     
  free(word);                                                                         
  qclose(entry->queue);                                                          
}                                                                                     
void printq(void* elementp){                                                     
                                                                                 
  qElement_t * document = (qElement_t*) elementp;                                
                                                                                 
  if (document != NULL) {                                                        
    printf(", %d, %d\n", document->id, document -> wordCount);                       
  }                                                                              
}                                                                                
                                                                                 
void printh(void* elementp) {                                                    
                                                                                 
    hElement_t *entry = (hElement_t*)elementp;                               
                                                                                 
    if (entry == NULL) {                                                         
        return;                                                                  
    }                                                                            
    char* printWord = entry->word;                                          
    if (printWord == NULL) {                                                     
        return;                                                                  
    }                                                                            
    queue_t* printDocuments = entry->queue;                                  
    printf("%s", printWord);                                                     
                                                                                 
    if (printDocuments != NULL) {                                                
        qapply(printDocuments, printq);                                          
    }                                                                            
}                                                 
                                                                                      
int main (int argc, char * argv[]){                                                                      
  char* word;                                                                         
  int pos=0;                                                                          
  hashtable_t* indexHT;                                                               
  webpage_t* newWebPg;
	queue_t *queue;
	//int idMax = atoi(argv[1]);
	int idMax = 82;
	int count =0;
	char *pagedir = argv[1];
	char * indexnm = argv[2];
	//char filename[100];                                                                
  
  //open hashtable                                                                    
  indexHT = hopen(150);                                                               
	for(int id = 1; id <= idMax; id++){                                                                              
  // Load webpage                                                                     
  newWebPg = pageload(id,"../pages-depth3");                                                   
  /*                                                                                    
  FILE *fp = fopen("../test/1","r");                                                  
  if (fp == NULL){                                                                    
    printf("Error opening the file \n");                                              
    return 0;                                                                         
		} */                                                                                  
  // Get next word in HTML                                                            

	//qElement_t *tempQ;
	//hElement_t *tempH;

	pos = 0;
	//while((pos = webpage_getNextWord(newWebPg, pos, &word))>0){
	do{
		pos = webpage_getNextWord(newWebPg, pos, &word);
  if(pos != -1){                                        
    word = NormalizeWord(word);                                                       
		printf("Added: %s \n", word);
		if (word != NULL){                                                                
			count++;
			hElement_t *hfound = (hElement_t*) hsearch(indexHT, matchingWordsSearch, word, strlen(word));
			
      if (hfound == NULL) {
				//printf("Element not found in hash\n");
				qElement_t *tempQ = makeqElement(id, 1);
				//tempQ = makeqElement(id, 1);
				queue = qopen();
				qput(queue, tempQ);
				hElement_t *tempH = makehElement(word, queue);
				//tempH = makehElement(word, queue);
				hput(indexHT, tempH, word, strlen(word));
      }
      else {
				qElement_t *qfound = (qElement_t *) qsearch(hfound->queue, matchingIdSearch, &id);
				if(qfound == NULL){
					//printf("Element not found in queue\n");
					qElement_t *tempQ = makeqElement(id, 1);
					//tempQ = makeqElement(id, 1);
					qput(hfound->queue, tempQ);
				}
				else{
					//			printf("Element already in queue\n");
					(qfound->wordCount)++;
				}
      }
			//free(word);
    }
		//free(word);
	}
	//webpage_delete(newWebPg);
	//free(word);
	}while(pos != -1);
	//fclose(fp);
	printf("Finished document %d\n", id);
	webpage_delete(newWebPg);
	}
	
	//indexEntry_t *newEntry = malloc(sizeof(indexEntry_t));
  //free(newWebPg->url);                                                               
  //free(newWebPg->html);                                                              
	//webpage_delete(newWebPg);
	//free(newWebPg);                                                                      
  //fclose(fp);
	happly(indexHT, printh);                                                             
  happly(indexHT, wordCounterHash);                                                        
  printf("Total # of Words: %d\n", sum);
	//free(tempQ);
	//free(tempH);
	indexsave(indexHT, pagedir, indexnm);

	hashtable_t * testH = indexload(indexnm);
	//indexsave(testH, pagedir, indexnm);
	happly(testH, printh);
	happly(testH, wordCounterHash);
	printf("Total # of Words: %d\n", sum);
	printf("Count: %d\n",count);
happly(indexHT, freeHash);                                                      
//happly(testH, freeHash);
//hclose(testH);
	hclose(indexHT);                                                                     
  free(word);                                                                          
                                                                                       
                                                                                       
  return 1;                                                                            
}                                                                                      
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                    
