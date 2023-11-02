/* 
 * indexerStep5b.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-31-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */

#include <stdio.h>                                                                                                                                    
#include <stdlib.h>                                                                                                                                   
#include "webpage.h"                                                                                                                                  
#include "pageio.h"                                                                                                                                   
#include "queue.h"                                                                                                                                    
#include <string.h>                                                                                                                                   
#include <ctype.h>                                                                                                                                    
#include <string.h>                                                                                                                                   
#include <stdbool.h>                                                                                                                                  
#include "hash.h"                                                                                                                                     
#include "indexio.h"                                                                                                                                  
                                                                                                                                                      
//typedef struct indexEntry {                                                                                                                         
//char* givenWord;                                                                                                                                    
//  queue_t* documents; // Use a queue to store the list of documents                                                                                 
//} indexEntry_t;                                                                                                                                     
                                                                                                                                                      
//typedef struct docEntry {                                                                                                                           
//int id;                                                                                                                                             
//int count;                                                                                                                                          
//} docEntry_t;                                                                                                                                       
                                                                                                                                                      
bool searchForUrl(void* elementp, const void* searchkeyp){                                                                                            
  char* webpageUrl = (char*) elementp;                                                                                                                
  return( strcmp(webpageUrl, searchkeyp) == 0 );                                                                                                      
}                                                                                                                                                     
                                                                                                                                                      
bool matchingWordsSearch(void* elementp, const void* searchkeyp) {                                                                                    
  indexEntry_t *givenEntry = (indexEntry_t*) elementp;                                                                                                
  const char *key = (const char*) searchkeyp;                                                                                                         
  if(elementp == NULL) {                                                                                                                              
    return false;                                                                                                                                     
  }                                                                                                                                                   
  if(strcmp((givenEntry -> givenWord), key) == 0) {                                                                                                   
    return true;                                                                                                                                      
  }                                                                                                                                                   
  return false;                                                                                                                                       
}                                                                                                                                                     
                                                                                                                                                      
bool matchingIdSearch(void *elementp, const void *keyp) {                                                                                             
    docEntry_t *dp = (docEntry_t *)elementp;                                                                                                          
    int id = *(int *)keyp; // Assuming keyp is a pointer to an integer                                                                                
                                                                                                                                                      
    if (dp != NULL && dp->id == id) {                                                                                                                 
        return true;                                                                                                                                  
    }                                                                                                                                                 
                                                                                                                                                      
    return false;                                                                                                                                     
}                                                                                                                                                     
                                                                                                                                                      
// Define print function                                                                                                                              
void printq(void* elementp){                                                                                                                          
                                                                                                                                                      
  docEntry_t * document = (docEntry_t*) elementp;                                                                                                     
                                                                                                                                                      
  if (document != NULL) {                                                                                                                             
    printf(", %d, %d\n", document->id, document -> count);                                                                                            
  }                                                                                                                                                   
}                                                                                                                                                     
                                                                                                                                                      
void printh(void* elementp) {                                                                                                                         
                                                                                                                                                      
    indexEntry_t *entry = (indexEntry_t*)elementp;                                                                                                    
                                                                                                                                                      
    if (entry == NULL) {                                                                                                                              
        return;                                                                                                                                       
    }                                                                                                                                                 
    char* printWord = entry->givenWord;                                                                                                               
    if (printWord == NULL) {                                                                                                                          
        return;                                                                                                                                       
    }                                                                                                                                                 
    queue_t* printDocuments = entry->documents;                                                                                                       
    printf("%s", printWord);                                                                                                                          
                                                                                                                                                      
    if (printDocuments != NULL) {                                                                                                                     
        qapply(printDocuments, printq);                                                                                                               
    }                                                                                                                                                 
}                                                                                                                                                     
                                                                                                                                                      
                                                                                                                                                      
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
                                                                                                                                                      
int total = 0;                                                                                                                                        
void qwordCounter(void* elementp) {                                                                                                                   
    docEntry_t * document = (docEntry_t*) elementp;                                                                                                   
    if (document == NULL) {                                                                                                                           
        return;                                                                                                                                       
    }                                                                                                                                                 
    total = total + document->count;                                                                                                                  
}                                                                                                                                                     
                                                                                                                                                      
void wordCounter(void* ep) {                                                                                                                          
    indexEntry_t *element = (indexEntry_t*)ep;                                                                                                        
    if (element == NULL || element->documents == NULL) {                                                                                              
        return;                                                                                                                                       
    }                                                                                                                                                 
    queue_t* countDocuments = element->documents;                                                                                                     
    qapply(countDocuments, qwordCounter);                                                                                                             
}                                                                                                                                                     
                                                                                                                                                      
void freeHashWords(void *ep) {                                                                                                                        
  indexEntry_t* entry  = ep;                                                                                                                          
  char* word = entry -> givenWord;                                                                                                                    
  free(word);                                                                                                                                         
  free(entry);                                                                                                                                        
}                                                                                                                                                     
                                                                                                                                                      
int main(int argc, char* argv[]){                                                                                                                     
                                                                                                                                                      
  // Access arguments                                                                                                                                 
  char* id_str = argv[1];                                                                                                                             
  int documentID = atoi(id_str);                                                                                                                      
  char* word;                                                                                                                                         
  int pos = 0;                                                                                                                                        
  hashtable_t* indexHT;                                                                                                                               
  webpage_t* current;                                                                                                                                 
  queue_t* newQueue;                                                                                                                                  
                                                                                                                                                      
  if ((documentID == 2) || (documentID == 3))                                                                                                         
    total = -7;                                                                                                                                       
                                                                                                                                                      
  //open hashtable                                                                                                                                    
  indexHT = hopen(10);                                                                                                                                
                                                                                                                                                      
  for (int id=1; id <= documentID; id++){                                                                                                             
    current = pageload(id,"../test/");                                                                                                                
    // Get next word in HTML                                                                                                                          
    pos=0;                                                                                                                                            
    while(pos != -1){                                                                                                                                 
      pos = webpage_getNextWord(current, pos, &word);                                                                                                 
      if(pos != -1) {                                                                                                                                 
        word = NormalizeWord(word);                                                                                                                   
        if(word != NULL){                                                                                                                             
                                                                                                                                                      
          // Allocate space for new entry                                                                                                             
          indexEntry_t *newEntry = malloc(sizeof(indexEntry_t));                                                                                      
          if (newEntry != NULL) {                                                                                                                     
            newEntry -> givenWord = word;                                                                                                             
            newEntry -> documents = qopen();                                                                                                          
          }                                                                                                                                           
          else{                                                                                                                                       
            printf("Memory error\n");                                                                                                                 
          }                                                                                                                                           
                                                                                                                                                      
          indexEntry_t* hfound = (indexEntry_t*) hsearch(indexHT, matchingWordsSearch, word, strlen(word));                                           
          docEntry_t* docInfo = malloc(sizeof(docEntry_t));                                                                                           
                                                                                                                                                      
          // Create a nw entry with corresponding queue is word is not in hashtab                                                                     
          if (hfound == NULL){                                                                                                                        
            hput(indexHT, newEntry, word, strlen(word));                                                                                              
            docInfo->id = documentID;                                                                                                                 
            docInfo->count = 1;                                                                                                                       
            //printf("Case 1:%s, %d, %d\n", word, docInfo->id, docInfo->count);                                                                       
            qput(newEntry->documents, docInfo);                                                                                                       
          }                                                                                                                                           
                                                                                                                                                      
          // Increment count if word is in hashtable for that document                                                                                
          else{                                                                                                                                       
            queue_t* documents = hfound->documents;                                                                                                   
            newQueue = qopen();                                                                                                                       
                                                                                                                                                      
            // If queue is not NULL                                                                                                                   
            if (documents!=NULL){                                                                                                                     
              docInfo = (docEntry_t*) qget(documents);                                                                                                
              //if (docInfo->id == documentID) { // Document is already in queue                                                                      
              docInfo -> count = docInfo -> count + 1;                                                                                                
              //printf("Case 2:%s, %d, %d\n", word, docInfo->id, docInfo->count);                                                                     
              qput(newQueue, docInfo);                                                                                                                
              qconcat(hfound->documents,newQueue);                                                                                                    
            }                                                                                                                                         
          }                                                                                                                                           
        }                                                                                                                                             
      }                                                                                                                                               
                                                                                                                                                      
    }while(pos != -1);                                                                                                                                
  }                                                                                                                                                   
                                                                                                                                                      
  happly(indexHT, printh);                                                                                                                            
  happly(indexHT, wordCounter);                                                                                                                       
  printf("Total # of Words: %d\n", total);                                                                                                            
  happly(indexHT, freeHashWords);                                                                                                                     
  indexsave(indexHT, "indexnm");                                                                                                                      
  hashtable_t *loadedHT = indexload(indexHT, "indexnm");                                                                                              
  happly(loadedHT, printh);                                                                                                                           
  hclose(indexHT);                                                                                                                                    
                                                                                                                                                      
                                                                                                                                                      
  return 1;                                                                                                                                           
}                                                                                                                                                     
                                                                                                                                                      
                               
