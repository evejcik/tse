/* 
 * indexer.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-24-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <webpage.h>
#include <queue.h>
#include <hash.h>
#include <unistd.h>
#include <sys/stat.h>  
#include <pageio.h>

int main(int argc, char *argv[]){
	printf("hello");
	webpage_t* page = pageload(1, pages);

	int pos = 0;
    char *result = NULL;

    while (webpage_getNextURL(page, pos, &result) != NULL) {
        // Print the content of result (URL or words) to the screen
        if (result != NULL) {
            printf("%s\n", result);
            free(result); // Free the memory allocated by webpage_getNextURL
        }
    }

    // Free the webpage when you're done
    webpage_delete(page);
	

}
