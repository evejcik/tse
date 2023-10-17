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

void printURL(void *data) {
        webpage_t *page = (webpage_t *)data;
        char *url = webpage_getURL(page);
				//				strcpy(url, url2);
				//	webpage_delete(url);
        printf("%s\n", url);
				free(url);
				//webpage_delete(url);
}

bool searchURL(void *elementp, const void *key) {
    char *url = webpage_getURL((webpage_t *)elementp);
		bool test;
		return (strcmp(url, (char *) key) == 0);
		/*		if(strcmp(url, (char *) key) == 0){
			test = true;
		}else{
			test = false;
		}
		free(url);
		return test;;*/
		/*		cmp = (strcmp(url, (char *)key) == 0);
		free(url);

		if(cmp == 0){
			return true;
		}else{
			return false;
			}*/
}
      

int main(){
	// Create an array or list to track visited URLs
	//	char *visitedURLs[MAX_VISITED_URLS];
	//printf("hello");

	char *seedURL = "https://thayer.github.io/engs50/";
	webpage_t* page = webpage_new(seedURL, 0, NULL);

	int pos = 0;
	char *result;
	queue_t* myQueue = qopen();
	hashtable_t *visitedURLs = hopen(100); 

	if(webpage_fetch(page)){
		while((pos = webpage_getNextURL(page, pos, &result)) > 0) {
			if(IsInternalURL(result)){
				if(hsearch(visitedURLs, searchURL, result, strlen(result)) == NULL){
					webpage_t *internalPage = webpage_new(result, 0, NULL);
					qput(myQueue, internalPage);
					hput(visitedURLs, internalPage, result, strlen(result));
					
				}
			}
			free(result);
			//qclose(myQueue);
		}
		
		// Print the visited URLs stored in the hashtable
		printf("Visited URLs:\n");
		happly(visitedURLs, printURL);
		//qclose(myQueue);
		//hclose(visitedURLs);

		//		qclose(myQueue);
		webpage_delete(page);
		hclose(visitedURLs);
		//qclose(myQueue);
		exit(EXIT_SUCCESS);
	}else{
		//qclose(myQueue);
		hclose(visitedURLs);
		webpage_delete(page);
		exit(EXIT_FAILURE);
	}
}
