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

int main(int argc, char* argv[]){
	//printf("hello");

	webpage_t* page = webpage_new("https://thayer.github.io/engs50/", 0, NULL);

	if(!webpage_fetch(page)){
		exit(EXIT_FAILURE);
	};

	int pos = 0;
	char *result;

	if(webpage_fetch(page)){
		//char *html = webpage_getHTML(page);
		while((pos = webpage_getNextURL(page, pos, &result)) > 0) {
			printf("Found url: %s\n", result);
			if(IsInternalURL(result)){
					printf("Is Internal.\n");
				}else {
					printf("Is External.\n");
			}
			free(result);
		}
	}

	free(pos);
	free(page);
	
	return 0;
}
