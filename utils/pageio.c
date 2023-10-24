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
	}else{
		return 1;
	}
}  


webpage_t *pageload(int id, char *dirnm){
	FILE *file;
  char filename[50];                                                                               
  sprintf(filename, "../%s/%d", dirname, id);                                                      
  file  = fopen(filename, "r");   


	//	char * pageURL;
	//FILE* file =	fscanf(loadedFile, "%s", pageURL);

	char url[200];
	char depth[200];
	//	char htmlDepth[200];
	char htmlBuffer[1000000];
	int c;
	int depthInt;
	int index = 0;
	int i = 0;

	while(i < 3){
		if(i == 0){
			index = 0;
			while ((c = fgetc(file)) != '\n') {
				url[index] = c;
				index++;
			}
			url[index] = '\0';
		}else if(i == 1){
			index = 0;
			while((c = fgetc(file)) != '\n'){
				depth[index] = c;
				index++;
			}
			depth[index] = '\0';
		}else if(i == 2){
			index = 0;
			while ((c = fgetc(file)) != '\n'){
				htmlDepth[index] = c;
				index++;
			}
			htmlBuffer[index] = '\0';
		}
		i++;
	}
		 
	depthInt = atoi(depth);
			//			htmlDepthInt = atoi(htmlDepth);
	index = 0;
	while((c = fgetc(file)) != EOF){
		htmlBuffer[index] = c;
		index++;
	}

		
	webpage_t* page = webpage_new(url, depthInt, htmlBuffer);
	//				free(file);
	fclose(file);
	return(page);
		
}

