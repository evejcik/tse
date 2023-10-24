/* 
 * pageio.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-22-2023
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

webpage_t *pageload(int id, char *dirnm){

	char * pageURL;
	FILE* file =	fscanf(loadedFile, "%s", pageURL);

	 char url[200];
	 char depth[200];
	 char htmlDepth[200];
	 int c;
	 int index = 0;

	 while(i < 3){
		 if(i == 0){
			 index = 0;
			 while ((c = fgetc(file)) != '\n') {
				 url[index] = c;
				 index++;
			 }
		 }else if(i == 1){
			 index = 0;
			 while((c = fgetc(file)) != '\n'){
				 depth[index] = c;
				 index++;
			 }
		 }else if(i == 2){
			 index = 0;
			 while ((c = fgetc(file) != '\n'){
					 htmlDepth[index] = c;
					 index++;
					 

				 }
			
		 }
		 
		 depthInt = atoi(depth);
		 htmlDepthInt = atoi(htmlDepth);

		 webpage_t* page = webpage_new(url, depthInt, htmlDepthInt);

		 
		 return page;
		 
}
		 /*
	 url[index] = '\0'; // Null-terminate the URL string


	 while ((c = fgetc(file)) != '\n' && c != EOF && index < sizeof(url) - 1) {
        url[index] = c;
        index++;
				}*/
	 
	 //printf("URL: %s\n", url);

	/*webpage_t * webpage;
    
	webpage = webpage_new(pageURL, 0, NULL);

	fclose(loadedFile);
	return webpage;*/

	/*FILE *fp;                                                                                                   
	char filename[50];
	char str[60];
	sprintf(filename, "../%s/%d", dirname, id);

	char url[200];
	int depth, html_len;
	char *html = NULL;

	char htmlBuffer[10000000];
	

	fp = fopen(filename, "r");


	int c;
	int index = 0;
	while ((c = fgetc(file)) != '\n') {
		url[index++] = c;
	}
	url[index] = '\0';

	if (fscanf(file, "%d", &depth) != 1) {
		perror("Error reading the second line as an integer");
		fclose(file);
		return 1; // Exit with an error code
	}

	if (fscanf(file, "%d", &html_len) != 1) {
		perror("Error reading the third line as an integer");
		fclose(file);
		return 1; // Exit with an error code
	}
	

	int pos = 0;
	if(i == 3){
		pos = 0;
		while((ch == fgetc(fp)) != EOF){
			htmlBuffer[i] = ch;
			pos++;
		}
	}
		
	
	webpage_t* page = webpage_new(url,depth, htmlBuffer);
	
	

				
	}*/

	/*if(fgets(url, sizeof(url), fp) != NULL){
		printf("URL: %s", url);
	}

	if(fscanf(fp, "%d", &depth) !=1){
		perror("Error reading second line.");
		fclose(file);
		return 1;
	}

	if(fscanf(fp, "%d", &html_len !=1)){
			perror("Error reading third line.");
			fclose(fp);
			return 1;
			}*/

	
	
	/*if (fp == NULL) {
		perror("Error opening file");
		return NULL; // Return NULL to indicate failure
	}

	if(fgets(str,60,fp)!=NULL){
		url = str;
	}
	fclose(fp);*/

	/*	char url[MAX_URL];
	int depth;
	int html_len;
	char *html = NULL;

	int line = 0;
	char holder;*/
	/*	while((holder = fgetc(file)) != EOF){
		if(holder == '\n') line++;
		if(line == 1) 

	url = fscanf(fptr, "%[^\n]", c);
	depth = */

	//	fscanf(fptr, "%[^\n]", c);
	
	//	webpage_t *page = webpage_new("", 0, NULL);

/*
    if (fscanf(file, "%s%d%d", url, &depth, &html_len) != 3) {
        perror("Error reading file");
        fclose(file);
        webpage_delete(page); // Clean up the webpage
        return NULL; // Return NULL to indicate failure
    }

    // Allocate memory for the HTML content
    html = (char *)malloc(html_len + 1);
    if (html == NULL) {
        perror("Memory allocation error");
        fclose(file);
        webpage_delete(page); // Clean up the webpage
        return NULL; // Return NULL to indicate failure
    }

    // Read the HTML content
    if (fread(html, 1, html_len, file) != html_len) {
        perror("Error reading file");
        free(html); // Clean up allocated memory
        fclose(file);
        webpage_delete(page); // Clean up the webpage
        return NULL; // Return NULL to indicate failure
    }

    html[html_len] = '\0'; // Null-terminate the HTML content
	 */
    // Set the webpage fields
		/*  webpage_setURL(page, url);
    webpage_setDepth(page, depth);
    webpage_setHTML(page, html, html_len);&/

    // Close the file
    fclose(file);

    return page; // Return the populated webpage structure
	 

}
		*/
