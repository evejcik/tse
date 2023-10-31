/* 
 * pageio.c --- 
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
#include <string.h>                                                             
#include <inttypes.h>                                                           
#include <unistd.h>                                                             
#include <webpage.h>                                                            
#include "pageio.h"                                                             
#include <stdbool.h>
#include <sys/stat.h>



#define MAX_LEN 50                                                              
                                                                                
/*                                                                              
 * pagesave -- save the page in filename id in directory dirnm                  
 *                                                                              
 * returns: 0 for success; nonzero otherwise                                    
 *                                                                              
 * The suggested format for the file is:                                        
 *   <url>                                                                      
 *   <depth>                                                                    
 *   <html-length>                                                              
 *   <html>                                                                     
 */                                                                             
int32_t pagesave(webpage_t *pagep, int id, char *dirnm){                        
                                                                                
  //Calculate size of directory + filename                                      
  int filename_len = strlen(dirnm) + 3; //+3 for id                             
                                                                                
  // Allocate memory for the directory + filename                               
  char *filename = (char *)malloc(filename_len);                                
                                                                                
                                                                                
  // cast id to str                                                             
  sprintf(filename, "%s%d",dirnm, id);                                          
                                                                                
                                                                                
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
                                                                                
  fprintf(fp, "%s\n%d\n%d\n%s", URL, depth, html_len, html);                    
                                                                                
                                                                                
  // close the file                                                             
  fclose(fp);                                                                   
                                                                                
                                                                                
  // free the filename                                                          
  free(filename);                                                               
  return 0;                                                                     
}                                                                               
                                                                                
                                                                                
                                                                                
/*                                                                              
 * pageload -- loads the numbered filename <id> in direcory <dirnm>             
 * into a new webpage                                                           
 *                                                                              
 * returns: non-NULL for success; NULL otherwise                                
 */                                                                             
                                                                                
                                                                                
/*webpage_t *pageload(int id, char *dirnm){                                       
                                                                                
  char urlBuffer [MAX_LEN];                                                     
  char depthBuffer [MAX_LEN];                                                   
  char htmlLengthBuffer [MAX_LEN];                                              
  webpage_t* newPg = NULL;                                                      
  int ch = 0, i = 0, j = 0, depth = 0;                                          
                                                                                
  //Calculate size of directory + filename                                      
  int filename_len = strlen(dirnm) + 3; //+3 for id                             
                                                                                
  // Allocate memory for the directory + filename                               
  char *filename = (char *)malloc(filename_len);                                
                                                                                
                                                                                
  sprintf(filename, "%s/%d",dirnm, id);                                         
  FILE *fp = fopen(filename, "r");                                              
                                                                                
  // check file exists                                                          
  if (fp == NULL){                                                              
    printf("Error opening the file %s\n", filename);                            
    return NULL;                                                                
  }                                                                             
                                                                                
                                                                                
  for(j = 0; j < 3; j++){                                                       
    i = 0;                                                                      
    while( (ch = fgetc(fp)) != '\n'){                                           
      if (j == 0){                                                              
        urlBuffer[i] = ch;                                                      
        //printf("UrlBuffer: %s\n", urlBuffer);                                 
        i++;                                                                    
      }                                                                         
      else if (j == 1){                                                         
        depthBuffer[i] = ch;                                                    
        i++;                                                                    
      }                                                                         
      else if (j == 2){                                                         
        htmlLengthBuffer[i] = ch;                                               
        i++;                                                                    
      }                                                                         
    }                                                                           
  }                                                                             
                                                                                
  int htmlLength = atoi(htmlLengthBuffer);                                      
  char htmlBuffer[100000];                                                      
                                                                                
  if (j == 3){                                                                  
    for (i=0; i<htmlLength; i++) {                                              
      ch = fgetc(fp);                                                           
      htmlBuffer[i] = ch;                                                       
    }                                                                           
  }                                                                             
                                                                                
  depth = atoi(depthBuffer);                                                    
                                                                                
                                                                                
  //printf("\nPostLoop: Url is %s\n", urlBuffer);                               
  //printf("PostLoop: Depth is %d\n", depth);                                   
  //printf("PostLoop: Html is %s\n\n", htmlBuffer);                             
                                                                                
                                                                                
  // Make Webpage                                                               
  newPg  = webpage_new(urlBuffer,depth,htmlBuffer);                             
                                                                                
  free(filename);                                                               
                                                                                
  // Close file                                                                 
  fclose(fp);                                                                   
                                                                                
  // Return                                                                     
  return(newPg);                                                                
}                                                                               
                                                                                
       
*/
webpage_t *pageload(int id, char *dirnm) {

    char url[100]; 
    int depth; 
    int len; 
		// char*html;


    FILE *fp; 
    char filename[100]; 

    sprintf(filename, "%s/%d", dirnm, id); 
		//    printf("filename: %s\n", filename);
    fp = fopen(filename, "r");
		// printf("file open\n");

    if(fp == NULL){
      //  printf("file is empty \n");
        return NULL; 
    }

   fscanf(fp, "%s\n%d\n%d\n", url, &depth, &len); 
	 char *html= malloc(sizeof(char)*(len+1));
	 int i=0;
   char c;

	 while((c=fgetc(fp)) != EOF){
		 html[i]=c;
		 i=i+1;
	 }
	 html[i-1]= '\0';
	 
	 //printf("scanned\n");
   webpage_t *page = webpage_new(url, depth, html); 
   //printf("created page\n");

	 fclose(fp);
	 
   return page; 

}
