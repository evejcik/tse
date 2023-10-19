/*                                                                                                
 * crawler.c ---                                                                                  
 *                                                                                                
 * Author: Emma Vejcik                                                                            
 * Created: 10-15-2023                                                                            
 * Version: 1.0                                                                                   
 *                                                                                                
 * Description:                                                                                   
 *                                                                                                
 */                                                                                               
                                                                                                  
#include <stdio.h>                                                                                
#include <string.h>                                                                               
#include <webpage.h>                                                                              
#include <stdlib.h>                                                                               
#include <hash.h>                                                                                 
#include <queue.h>                                                                                
                                                                                                  
//#define MAX_VISITED_URLS 1000                                                                   

bool searchURL(void *elementp, const void *key) {
	char *url = (char *)elementp;                                                                     
  return(strcmp(url, (char *) key) == 0);                                                         
}                                                                                                 
void printURL(void *data) {                                                                       
        webpage_t *page = (webpage_t *)data;                                                      
        char *url = webpage_getURL(page);                                                         
        printf("%s\n", url);                                                                      
}                                                                                                 
                                                                                                  
int32_t pagesave(webpage_t *pagep, int id, char *dirname){                                        
  FILE * resultFile;                                                                              
  char filename[50];                                                                              
                                                                                                  
  sprintf(filename, "../%s/%d", dirname, id);                                                     
  resultFile = fopen(filename, "w");                                                              
                                                                                                  
  if(resultFile != NULL){                                                                         
    fprintf(resultFile, "%s \n %d \n %d \n %s", webpage_getURL(pagep), webpage_getDepth(pagep), webpage_getHTMLlen(pagep), webpage_getHTML(pagep));                                                
    fclose(resultFile);                                                                           
    return 0;                                                                                     
  }                                                                                               
  else{                                                                                           
    return 1;                                                                                     
  }                                                                                               
}                                                                                                 
                                                                                                  
                                                                                                  
int main(){                                                                                       
  char *seedURL = "https://thayer.github.io/engs50/";                                             
  webpage_t* page = webpage_new(seedURL, 0, NULL);                                                
  webpage_t *internalPage;                                                                        
  queue_t *myQueue = qopen();;                                                                    
  int pos = 0;                                                                                    
  char *result;                                                                                   
  hashtable_t *visitedURLs = hopen(100);                                                          
                                                                                                  
                                                                                                  
  if(webpage_fetch(page)){                                                                        
                                                                                                  
		pagesave(page, 1, "pages");                                                                   
                                                                                                  
    while((pos = webpage_getNextURL(page, pos, &result)) > 0) {                                   
      if(IsInternalURL(result) && hsearch(visitedURLs, searchURL, result, strlen(result)) == NULL){                                                                                                
           internalPage = (webpage_new(result, 0, NULL));                                         
           qput(myQueue, internalPage);                                                           
           hput(visitedURLs, result, result, strlen(result));                                     
      }                                                                                           
      else{                                                                                       
        free(result);                                                                             
      }                                                                                           
    }                                                                                             
   printf("Visited URLs:\n");                                                                     
   qapply(myQueue, printURL);                                                                     
                                                                                                  
   while((internalPage = (qget(myQueue))) != NULL){                                               
        webpage_delete(internalPage);                                                             
      }                                                                                           
      qclose(myQueue);                                                                            
      hclose(visitedURLs);                                                                        
      webpage_delete(page);                                                                       
  }                                                                                     
    exit(EXIT_FAILURE);                                                                           
}                                                                                                 
                                                                                                  
