/* 
 * indexio.h --- 
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

typedef struct hElement{                                                                                            
  char *word;                                                                                                       
  queue_t *queue;                                                                                                   
}hElement_t;                                                                                                        
                                                                                                                    
typedef struct qElement{                                                                                            
  int id;                                                                                                           
  int wordCount;                                                                                                    
}qElement_t;                                                                                                        
/*
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
}                                                                                                                  */ 
/* 
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
                                                                               
 */                                                                            
void indexsave(hashtable_t *htp,char *pagedir, char* indexnm);                                 
                                                                                 
/* hclose -- closes a hash table */                                              
hashtable_t *indexload(char* indexnm);                          
                                                                                 
                                                                                 
                                                                                 
                                                                                 
