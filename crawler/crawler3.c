/* 
 * crawler3.c --- /*                                                                                                          
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
#include <unistd.h>                                                                                         
//#define MAX_VISITED_URLS 1000                                                                             
                                                                                                            
bool searchURL(void *elementp, const void *key){                                                            
  char *url = (char *)elementp;                                                                             
  return(strcmp(url, (char *) key) == 0);                                                                   
}                                                                                                           
void printURL(void *data) {                                                                                 
  printf("%s\n", (char *) data);                                                                            
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
                                                                                                            
bool DoesDirectoryExist(char * d){                                                                          
  char dirname[50];                                                                                         
  sprintf(dirname, "../%s", d);                                                                             
  if(access(dirname, F_OK) == 0){                                                                           
    return true;                                                                                            
  }                                                                                                         
  else{                                                                                                     
    return false;                                                                                           
  }                                                                                                         
}                                                                                                           
                                                                                                            
                                                                                                            
                                                                                                            
int main(int argc, char * argv[]){                                                                          
  if(argc != 4){                                                                                            
    printf("usage: crawler <seedurl> <pagedir> <maxdepth> \n");                                             
    exit(EXIT_FAILURE);                                                                                     
  }                                                                                                         
                                                                                                            
  char *seedURL = argv[1];                                                                                  
  char *directory = argv[2];                                                                                
  int maxDepth = atoi(argv[3]);                                                                             
	
  if(!IsInternalURL(seedURL) || !DoesDirectoryExist(directory) || maxDepth < 0){                            
     printf("usage: crawler <seedurl> <pagedir> <maxdepth> \n");                                            
     exit(EXIT_FAILURE);                                                                                    
  }                                                                                                         
  webpage_t* page = webpage_new(seedURL, 0, NULL);                                                          
  webpage_t *internalPage;                                                                                  
  queue_t *myQueue = qopen();                                                                               
  int pos = 0;                                                                                              
  char *result;                                                                                             
  hashtable_t *visitedURLs = hopen(100);                                                                    
  int currentDepth = 0;                                                                                     
  int id = 1;                                                                                               
  //int ilc = 1;                                                                                            
  //int xlc = 1;                                                                                            
                                                                                                            
  hput(visitedURLs, seedURL, seedURL, strlen(seedURL));                                                     
  do{                                                                                                       
    //printf("xlc: %d \n", xlc);                                                                            
    //xlc++;                                                                                                
    if(webpage_fetch(page)){                                                                                
			currentDepth = webpage_getDepth(page);                                                                  
      pagesave(page, id, directory);                                                                        
			printf("%s %d %d \n", webpage_getURL(page), currentDepth, id);                                        
      id++;                                                                            
      pos =0;                                                                                               
      while((pos = webpage_getNextURL(page, pos, &result)) > 0 && currentDepth < maxDepth) {                
        //printf("ilc: %d \n", ilc);                                                                        
				//ilc++;                                                                                              
				if(IsInternalURL(result) && hsearch(visitedURLs, searchURL, result, strlen(result)) == NULL){         
					internalPage = (webpage_new(result, currentDepth+1, NULL));                                      
					qput(myQueue, internalPage);                                                                     
					hput(visitedURLs, result, result, strlen(result));                                               
				}                                                                                                     
				//else{
				free(result);
					//}
			}                                                                                                       
			webpage_delete(page);                                                                                 
		}                                                                                                         
  }while((page = qget(myQueue)) != NULL);                                                                   
	printf("Visited URLs:\n");                                                                               
	happly(visitedURLs, printURL);
	/*	while((internalPage = (qget(myQueue))) != NULL){                                                             
		 webpage_delete(internalPage);                                                                           
		 } */ 

	hremove(visitedURLs, searchURL, seedURL, strlen(seedURL));                                               
	qclose(myQueue);                                                                                      
	hclose(visitedURLs);                                                                                  
	webpage_delete(page);                                                                                 
	exit(EXIT_SUCCESS);                                                                                   
}                                                                                                           
                                                                                                            

