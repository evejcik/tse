/* 
 * indexer.c --- 
 * 
 * Author: Matthew J. Sebastian
 * Created: 10-30-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */

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
                                                                                       
typedef struct indexEntry{                                                             
  char* givenWord;                                                                     
  int count;                                                                           
}indexEntry_t;                                                                         
                                                                                       
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
                                                                                       
                                                                                       
void printh(void* elementp) {                                                          
  indexEntry_t *entry = (indexEntry_t*) elementp;                                      
  char* printWord = entry -> givenWord;                                                
  int printCount = entry -> count;                                                     
  printf("%s , %d \n ", printWord, printCount);                                        
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
  indexEntry_t *element = (indexEntry_t*) ep;                                          
  if (element == NULL) {                                                               
    return;                                                                            
  }                                                                                    
  total = total + (element -> count);                                                  
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
  webpage_t* newWebPg;                                                                 
                                                                                       
  //open hashtable                                                                     
  indexHT = hopen(150);                                                                
                                                                                       
  // Load webpage                                                                      
  newWebPg = pageload(1,"../test");                                                    
                                                                                       
  FILE *fp = fopen("../test/1","r");                                                   
  if (fp == NULL){                                                                     
    printf("Error opening the file \n");                                               
    return 0;                                                                          
  }                                                                                    
  // Get next word in HTML                                                             
  while (feof(fp)== 0){                                                                
    pos = webpage_getNextWord(newWebPg, pos, &word);                                   
    if (word == NULL){                                                                 
      free(word);                                                                      
      break;                                                                           
    }                                                                                  
    word = NormalizeWord(word);                                                        
    if (word == NULL){                                                                 
      free(word);                                                                      
      pos++;                                                                           
    }                                                                                  
    else {                                                                             
      indexEntry_t *newEntry = malloc(sizeof(indexEntry_t));                           
      if (newEntry != NULL) {                                                          
        newEntry -> givenWord = word;                                                  
        newEntry -> count = 1;                                                         
      }                                                                                
      else {                                                                           
        printf("memory error \n");                                                     
        return 1;                                                                      
      }                                                                                
                                                                                       
      indexEntry_t *hfound = (indexEntry_t*) hsearch(indexHT, matchingWordsSearch, word, strlen(word));                                                                      
      if (hfound == NULL) {                                                            
        hput(indexHT, newEntry, word, strlen(word));                                   
      }                                                                                
                                                                                       
      else {                                                                           
        hfound -> count = (hfound -> count) + 1;                                       
                                                                                       
      }                                                                                
      pos++;                                                                           
    }                                                                                  
  }                                                                                    
                                                                                       
  //free(newWebPg->url);                                                               
  //free(newWebPg->html);                                                              
  free(newWebPg);                                                                      
  fclose(fp);                                                                          
  happly(indexHT, printh);                                                             
  happly(indexHT, wordCounter);                                                        
  printf("Total # of Words: %d\n", total);                                             
  happly(indexHT, freeHashWords);                                                      
  hclose(indexHT);                                                                     
  free(word);                                                                          
                                                                                       
                                                                                       
  return 1;                                                                            
}            
