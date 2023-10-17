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
#include <webpage.h>
#include <stdlib.h>
#include <hash.h>       
#include <queue.h>

void printURL(void *data) {
        webpage_t *page = (webpage_t *)data;
        char *url = webpage_getURL(page);
				webpage_delete(url);
        printf("%s\n", url);
    }
      

int main(){
	
	//printf("hello");

	char *seedURL = "https://thayer.github.io/engs50/";
	webpage_t* page = webpage_new(seedURL, 0, NULL);

	/*if(!webpage_fetch(page)){
		webpage_delete(page);
		exit(EXIT_FAILURE);
		};*/

	int pos = 0;
	char *result;
	queue_t* myQueue = qopen();

	if(webpage_fetch(page)){
		//char *html = webpage_getHTML(page);
		while((pos = webpage_getNextURL(page, pos, &result)) > 0) {
			//printf("Found url: %s\n", result);
			if(IsInternalURL(result)){
				webpage_t *internalPage = webpage_new(result, 0, NULL);
				//printf("Is Internal.\n");
				qput(myQueue, internalPage);
			}//else{
				//	printf("Is External.\n");
				//webpage_delete(page);
			//}
			free(result);
		}
		//free(result);
		qapply(myQueue,printURL);
		qclose(myQueue);
		webpage_delete(page);
		exit(EXIT_SUCCESS);
	}else{
		qclose(myQueue);
		exit(EXIT_FAILURE);
	}

	//qapply(myQueue, printData);
	//qclose(myQueue);

	//	webpage_delete(page);

	//	exit(EXIT_SUCCESS);
	//free(pos);
	//free(page);
	
	//return 0;
}
