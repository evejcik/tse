/* 
 * pagesaveTest.c --- 
 * 
 * Author: Matthew J. Sebastian
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

int main(){

	webpage_t* page = pageload(11, "pages");

	pagesave(page, 11, "test");

	free(page);
	printf("test complete \n");



}
