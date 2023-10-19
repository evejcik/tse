/* 
 * crawler4.c ---
 * 
 * Author: Emma Vejcik
 * Created: 10-18-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */

/* crawler.c ---                                                                                                                                               
 *                                                                                                                                                             
 *                                                                                                                                                             
 * Author: Rashad C. Brown-Mitchell I.                                                                                                                         
 * Created: Mon Oct 16 17:35:09 2023 (-0400)                                                                                                                   
 * Version:                                                                                                                                                    
 *                                                                                                                                                             
 * Description:                                                                                                                                                
 *                                                                                                                                                             
 */                                                                                                                                                            
                                                                                                                                                               
#include "queue.h"                                                                                                                                             
#include "webpage.h"                                                                                                                                           
#include "hash.h"                                                                                                                                              
#include <stdio.h>                                                                                                                                             
#include <stdbool.h> //for boolean stuff                                                                                                                       
#include <string.h> //for the strlen function                                                                                                                  
                                                                                                                                                               
uint32_t pagesave(webpage_t *pagep, int id, char *dirname){                                                                                                    
  char filename[12];                                                                                                                                           
  // cast id to str                                                                                                                                            
  sprintf(filename, "%s/%d",dirname, id);                                                                                                                      
                                                                                                                                                               
  // get values from webpage_t                                                                                                                                 
  int depth = webpage_getDepth(pagep);                                                                                                                         
  int html_len = webpage_getHTMLlen(pagep);                                                                                                                    
  char* html = webpage_getHTML(pagep);                                                                                                                         
  char* URL = webpage_getURL(pagep);                                                                                                                           
                                                                                                                                                               
  FILE *fp = fopen(filename, "w");                                                                                                                             
                                                                                                                                                               
    // check file exists                                                                                                                                       
    if (fp == NULL){                                                                                                                                           
        printf("Error opening the file %s", filename);                                                                                                         
        return -1;                                                                                                                                             
    }                                                                                                                                                          
    fprintf(fp, "%s\n%d\n%d\n%s\n", URL, depth, html_len, html);                                                                                               
                                                                                                                                                               
    // close the file                                                                                                                                          
    fclose(fp);                                                                                                                                                
    return 0;                                                                                                                                                  
}                                                                                                                                                              
                                                                                                                                                               
int main(int argc, char* argv[]){                                                                                                                              
                                                                                                                                                               
                                                                                                                                                               
  if (argc != 4) {                                                                                                                                             
        printf("Usage: %s seedurl pagedir maxdepth\n", argv[0]);                                                                                               
        return 1; 
  }                                                                                                                                                          
                                                                                                                                                               
  // Access individual arguments.                                                                                                                              
    char* seedurl = argv[1];                                                                                                                                   
    char* pagedir = argv[2];                                                                                                                                   
    int maxdepth = atoi(argv[3]);                                                                                                                              
                                                                                                                                                               
    // Create directory name                                                                                                                                   
  char dirname[12];                                                                                                                                            
  strcpy(dirname, "../");                                                                                                                                      
  strcat(dirname, pagedir);                                                                                                                                    
                                                                                                                                                               
    // Declare relevant structures                                                                                                                             
  webpage_t* my_webpage = webpage_new(seedurl, 0, NULL);                                                                                                       
  //webpage_t* result_webpage = NULL;                                                                                                                          
                                                                                                                                                               
  // Declare relevant variables                                                                                                                                
  char *result = NULL;                                                                                                                                         
  int pos = 0;                                                                                                                                                 
  int id = 1;                                                                                                                                                  
                                                                                                                                                               
  // Save front page                                                                                                                                           
  if (webpage_fetch(my_webpage)){                                                                                                                              
    printf("Found HTML!\n");                                                                                                                                   
  }     
   else{                                                                                                                                                        
    webpage_delete(my_webpage);                                                                                                                                
    exit(EXIT_FAILURE);                                                                                                                                        
  }                                                                                                                                                            
    // Save subsequent pages                                                                                                                                   
if (maxdepth > 0) {                                                                                                                                            
    while ((pos = webpage_getNextURL(my_webpage, pos, &result)) > 0) {                                                                                         
        if (IsInternalURL(result)) {                                                                                                                           
            webpage_t *result_webpage = webpage_new(result, 1, NULL);                                                                                          
            if (webpage_fetch(result_webpage)) {                                                                                                               
                printf("Internal URL: %s\n", result);                                                                                                          
                pagesave(result_webpage, id, dirname);                                                                                                         
                id += 1;                                                                                                                                       
            }else {printf("Failed to fetch internal URL: %s\n", result);}                                                                                      
            webpage_delete(result_webpage);                                                                                                                    
                                                                                                                                                               
        }else {printf("External URL: %s\n", result);}                                                                                                          
        free(result);                                                                                                                                          
      }                                                                                                                                                        
  }else {pagesave(my_webpage, id, dirname);}                                                                                                                   
                                                                                                                                                               
  webpage_delete(my_webpage);                                                                                                                                  
  exit(EXIT_SUCCESS);                                                                                                                                          
 }                                                                                                                                                                                       
