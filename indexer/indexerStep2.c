/* 
 * indexerStep2.c --- 
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
#include "webpage.h"                                                            
#include "pageio.h"                                                             
#include <string.h>                                                             
#include <ctype.h>                                                              
#include <string.h>                                                             
#include <stdbool.h>                                                            
                                                                                
char* NormalizeWord(char* word){                                                
  int cCounter;                                                                 
  char c;                                                                       
  //char newWord[] = *word;                                                     
                                                                                
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
                                                                                
int main (void) {                                                               
  char* word;                                                                   
  int pos=0;                                                                    
                                                                                
  // Load webpage                                                               
  webpage_t *newWebPg = pageload(1,"../test");                                  
                                                                                
  FILE *fp = fopen("../test/1","r");                                            
  if (fp == NULL){                                                              
    printf("Error opening the file \n");                                        
    return 0;                                                                   
  }                                                                             
                                                                                
  // Get next word in HTML                                                      
  pos=0;                                                                        
  do {                                                                          
    pos = webpage_getNextWord(newWebPg, pos, &word);                            
    if(pos != -1) {                                                             
      word = NormalizeWord(word);                                               
      if(word != NULL){                                                         
        printf("Word: %s\n",word);                                              
        free(word);                                                             
      }                                                                         
      else                                                                      
        free(word);                                                             
    }                                                                           
  } while(pos != -1);                                                           
                                                                                
  //  free(newWebPg->url);                                                      
  //free(newWebPg->html);                                                       
  free(newWebPg);                                                               
  fclose(fp);                                                                   
  exit(EXIT_SUCCESS);                                                           
}                                                                               
                                                                                
                                                                                
                                                                                
                 
