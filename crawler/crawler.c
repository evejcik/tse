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
#include "webpage.h"
#include <stdlib.h>                                                                                 
#include "queue/queue.h"

void printData(void* elementp) {                                                                    
    printf("Data: %d\n", *(char*)elementp);                                                          
}                                                                                                   
      

int main(int argc, char* argv[]){
	//printf("hello");

	webpage_t* page = webpage_new("https://thayer.github.io/engs50/", 0, NULL);

	if(!webpage_fetch(page)){
		webpage_delete(page);
		exit(EXIT_FAILURE);
	};

	int pos = 0;
	char *result;
	//queue_t* myQueue = qopen();

	if(webpage_fetch(page)){
		//char *html = webpage_getHTML(page);
		while((pos = webpage_getNextURL(page, pos, &result)) > 0) {
			printf("Found url: %s\n", result);
			if(IsInternalURL(result)){
				printf("Is Internal.\n");
				//	qput(myQueue, result);
			}else{
				printf("Is External.\n");
				webpage_delete(page);
			}
			free(result);
		}
	}else{
		webpage_delete(page);
	}

	//qapply(myQueue, printData);
	//qclose(myQueue);

	webpage_delete(page);

	exit(EXIT_SUCCESS);
	//free(pos);
	//free(page);
	
	//return 0;
}
