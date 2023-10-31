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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>
#include <indexio.h>

FILE *file = NULL;                                                                        
/*
typedef struct hElement{                                                              
  char *word;                                                                         
  queue_t *queue;                                                                     
}hElement_t;                                                                          
                                                                                      
typedef struct qElement{                                                              
  int id;                                                                             
  int wordCount;                                                                      
}qElement_t;                                                                          
*/                                                                                      
qElement_t *makeqElement2(int id, int wc){                                             
  qElement_t *result = (qElement_t *)malloc(sizeof(qElement_t));                      
  result->id = id;                                                                    
  result->wordCount = wc;                                                             
  return result;                                                                      
}                                                                                     
hElement_t *makehElement2(char *w, qElement_t *qp){                                    
  hElement_t *result = (hElement_t *)malloc(sizeof(hElement_t));                      
  result->word = w;                                                                   
  result->queue = qp;                                                                 
  return result;                                                                      
}

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
*/
void qPrint(void *qp)
{
  qElement_t *q = (qElement_t *)qp;
  if (q == NULL)
  {
    printf("queue is empty.");
    return;
  }
  fprintf(file, "%d %d ", q->id, q->wordCount);
  return;
}

void hPrint(void *htp)
{
  hElement_t *ht = (hElement_t *)htp;
  if (ht == NULL)
  {
    printf("hashtable is empty.");
    return;
  }
  fprintf(file, "%s ", ht->word);

  qapply(ht->queue, qPrint);

  fprintf(file, "\n");
  return;
}

void indexsave(hashtable_t *htp, char *indexnm){
  char filename[100];
  sprintf(filename, "../test/%s", indexnm);
  file = fopen(filename, "w");
  if(file == NULL)
  {
		return;
	}
	else{
    happly(htp, hPrint);
    fclose(file);
    return;
  }
}
                                                                              
/* load indexnm file to a hashtable */                                           
/*
hashtable_t indexload(hashtable_t *htp, char *indexnm){                                         
                                                                                 
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
                                                                                 
         
*/
hashtable_t *indexload(char* indexnm){
	char filename[100];
	hashtable_t *resultTable = hopen(150); 
sprintf(filename, "../test/%s", indexnm);
	file = fopen(filename, "r");

    if(file == NULL){
      //  printf("file is empty \n");
        return NULL; 
    }
	
	int id;
	int count;
	char c[100];
	char *word;

	while(fscanf(file, "%s", c) == 1) {
		word = malloc((strlen(c) + 1) * sizeof(char));
      strcpy(word, c);

		queue_t *queue = qopen();
	hElement_t *hElement = makehElement2(word, queue); 
	//printf("%s\n",c);
		//hElement->queue = queue; 

		while(fscanf(file, "%d %d", &id, &count) == 2){ 
			qElement_t *qElement = makeqElement2(id, count); 
			qput(queue, qElement);
			//printf("id: %d, count: %d\n", qel->documentid, qel->count);
		}
		hput(resultTable, hElement, word, strlen(word)); 
	}
	fclose(file); 
	return resultTable; 
}
