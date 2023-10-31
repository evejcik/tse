/* 
 * indexerStep4b.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-30-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */
#include <stdio.h>                                                               
#include <stdlib.h>                                                              
#include <webpage.h>                                                             
#include <pageio.h>                                                              
#include <queue.h>                                                               
#include <string.h>                                                              
#include <ctype.h>                                                               
#include <string.h>                                                              
#include <stdbool.h>                                                             
#include <hash.h>                                                                
                                                                                 
typedef struct indexEntry {                                                      
    char* givenWord;                                                             
    queue_t* documents; // Use a queue to store the list of documents            
} indexEntry_t;                                                                  
                                                                                 
typedef struct docEntry {                                                        
  int id;                                                                        
  int count;                                                                     
} docEntry_t;                                                                    
                                                                                 
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
void wordCounter(void* ep) {                                                     
    indexEntry_t *element = (indexEntry_t*)ep;                                   
    if (element == NULL || element->documents == NULL) {                         
        return;                                                                  
    }                                                                            
    docEntry_t *document = qget(element->documents);                             
    if (document == NULL) {                                                      
        return;                                                                  
    }                                                                            
    total = total + document->count;                                             
}                                                                                
                                                                                 
void freeHashWords(void *ep) {                                                   
  indexEntry_t* entry  = ep;                                                     
  char* word = entry -> givenWord;                                               
  free(word);                                                                    
  free(entry);                                                                   
}                                                                                
                                                                                 
                                                                                 
int main (void){                                                                 
  char* word;                                                                    
  int pos=0;                                                                     
  hashtable_t* indexHT;                                                          
  webpage_t* current;                                                            
	//  queue_t* webPgQueue;                                                           
  int documentID = 1;                                                            
  queue_t* newQueue;                                                             
                                                                                 
                                                                                 
  //open hashtable                                                               
  indexHT = hopen(150);                                                          
                                                                                 
  //open queue                                                                   
  //webPgQueue = qopen();                                                          
                                                                                 
  // Load webpage                                                                
  current = pageload(1,"../test");                                               
  FILE *fp = fopen("../test/1","r");                                             
  if (fp == NULL){                                                               
    printf("Error opening the file \n");                                         
    return 0;                                                                    
  }                                                                              
                                                                                 
                                                                                 
  // Get next word in HTML                                                       
  pos=0;                                                                         
  do{                                                                            
     pos = webpage_getNextWord(current, pos, &word);                             
     if(pos != -1) {                                                             
       word = NormalizeWord(word);                                               
       if(word != NULL){                                                         

         // Allocate space for new entry				
                                                                                 
         indexEntry_t *newEntry = malloc(sizeof(indexEntry_t));                 \
                                                                                 
         if (newEntry != NULL) {                                                 
           newEntry -> givenWord = word;                                        \
                                                                                 
           newEntry -> documents = qopen();                                      
         }                                                                       
         else{                                                                   
           printf("Memory error\n");                                             
         }                                                                       
                                                                                 
         indexEntry_t *hfound = (indexEntry_t*) hsearch(indexHT, matchingWordsSe\
arch, word, strlen(word));                                                       
         docEntry_t* docInfo = malloc(sizeof(docEntry_t));                       
                                                                                 
         // Create a nw entry with corresponding queue is word is not in hashtab 
         if (hfound == NULL){                                                    
           hput(indexHT, newEntry, word, strlen(word));                          
           docInfo->id = documentID;                                             
           docInfo->count = 1;                                                   
           qput(newEntry->documents, docInfo);                                   
         }                                                                       
                                                                                 
         // Increment count if word is in hashtable for that document            
         else{                                                                   
           queue_t* documents = hfound->documents;                               
           bool found = false;                                                   
           newQueue = qopen();                                                   
                                                                                 
           // If queue is not NULL                                               
           if (documents!=NULL){                                                 
             docInfo = (docEntry_t*) qget(documents);                            
             if (docInfo->id == documentID) {                                    
               docInfo -> count = docInfo -> count + 1;                          
               found = true;                                                     
             }                                                                   
             qput(newQueue, docInfo);                                            
                                                                                 
             if (!found) {                                                       
               docInfo->id = documentID;                                         
               docInfo->count = 1;                                               
               qput(newQueue, docInfo);                                          
             }                                                                   
             hfound->documents = newQueue;                                       
           }                                                                     
         }                                                                       
       }                                                                         
     }                                                                           
  }while(pos != -1);                                                             
                                                                                 
                                                                                 
  //  webpage_t *next = (webpage_t*) qget(webPgQueue);                           
                                                                                 
  //freewWebPg->url);                                                            
  //free(newWebPg->html);                                                        
  //free(current);                                                               
  //fclose(fp);                                                                  
  //qapply(newQueue,printq);                                                     
  //qclose(webPgQueue);                                                          
  happly(indexHT, printh);                                                       
  happly(indexHT, wordCounter);                                                  
  printf("Total # of Words: %d\n", total);                                       
  happly(indexHT, freeHashWords);                                                
  hclose(indexHT);                                                               
                                                                                 
                                                                                 
  return 1;                                                                      
}                                                                                
                                                                                 
                                                                                 
                                                                                 
                                                                                 
                                                                                 
                                                                                 
                                                                                 
                                                                                 
                                                                                 
                                                                                 
                                                                                 
                                                                                 
                                                                                 
                                                                                 
                                                                                 
                                                                                 
                                  
