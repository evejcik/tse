/* 
 * indexio.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-30-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */

#include <stdint.h>                                                              
#include <stdbool.h>                                                             
#include "hash.h"                                                                
#include "queue.h"                                                               
FILE *fp;                                                                        
                                                                                 
typedef struct indexEntry {                                                      
    char* givenWord;                                                             
    queue_t* documents; // Use a queue to store the list of documents            
} indexEntry_t;                                                                  
                                                                                 
typedef struct docEntry {                                                        
  int id;                                                                        
  int count;                                                                     
} docEntry_t;                                                                    
                                                                                 
                                                                                 
void fprinth(void *indexnm, void *elementp)                                      
{                                                                                
  FILE *fp = indexnm;                                                            
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
        qapply(printDocuments, fprintq);                                         
    }                                                                            
}                                                                                
                                                                                 
void fprintq(void *indexnm, void* elementp){                                     
  docEntry_t * document = (docEntry_t*) elementp;                                
  FILE *fp = indexnm;                                                            
  if (fp != NULL && document != NULL) {                                          
    fprintf(fp," %d %d ", document->id, document -> count);                      
  }                                                                              
  fprintf(fp,"\n");                                                              
}                                                                                
                                                                                 
/* save index hashtable to a file*/                                              
void indexsave(hashtable_t *htp, char* indexnm){                                 
  FILE *fp;                                                                      
  fp = fopen(indexnm, "w");                                                      
  happly(htp, fprinth);                                                          
  fclose(fp);                                                                    
}                                                                                
                                                                                 
/* load indexnm file to a hashtable */                                           
hashtable_t indexload(hashtable_t *htp){                                         
                                                                                 
  FILE *fp;                                                                      
                                                                                 
  // variables for loading an index                                              
  int ID;                                                                        
  int count;                                                                     
                                                                                 
  fp = fopen(filename, "r");                                                     
                                                                                 
  //word = get next word function?;???                                           
  while (fscanf(fp, "%s",&word) == 2) {                                          
                                                                                 
    //indexEntry_t* newEntry = malloc(sizeof(indexEntry_t));                     
    hput(indexHT, newEntry, word, strlen(word));                                 
    queue_t* documents = newEntry-> documents;                                   
                                                                                 
    while (fscanf(fp, "%d %d", &ID, &count) == 2) {                              
      queue_t *newQueue = qopen()                                                
      newQueue -> count = count;                                                 
      newQueue -> documents = id;                                                
      qput(newEntry->documents, newQueue)                                        
    }                                                                            
    free(newEntry);                                                              
  }                                                                              
  fclose(fp);                                                                    
}                                                                                
                                                                                 
         
