/* 
 * crawlerFINAL.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-26-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <webpage.h>
#include "queue.h"
#include <string.h>
#include "hash.h"
#include <unistd.h>
#include <sys/stat.h>

void urlPrint(void* url) {
	printf("URL: %s\n", char(*)url);
}

bool searchURL(void* elementp, const void* keyp) {
	return strcmp((char*)elementp, (char*)keyp) == 0;
}

int32_t pagesave(webapage_t *pagep, int id, char *dirname){
	if(pagep == NULL){
		fprinf(stderr, "Error: Invalid webpage pointer.\n");
		return -1;
	}
	if(access(dirname, F_OK) != 0){
		fprintf(stderr, "Error: Directory %s does not exist.\n", dirname);
		return -1;
	}
	char filepath[256];
	snprintf(filepath, sizeof(filepath), "%s/%d", dirname, id);
	FILE *fp = fopen(filepath, "w");
	if (fp == NULL) {
		fprintf(stderr, "Error: Failed to open file %s for writing.\n", filepath);
		return -1;
	}
	printf(fp, "%s\n%d\n%d\n%s\n", webpage_getURL(pagep), webpage_getDepth(pagep), webpage_getHTMLlen(pagep), webpage_getHTML(pagep));
	fclose(fp);
	return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		fprintf(stderr, "usage: %s <seedurl> <pagedir> <maxdepth>\n", argv[0]);
		return EXIT_FAILURE;
	}
	char *seedURL = argv[1];
	char *pageDir = argv[2];
	int maxDepth = atoi(argv[3]);
	if (maxDepth < 0) {
		fprintf(stderr, "Error: maxdepth must be a non-negative integer.\n");
		return EXIT_FAILURE;
	}
	queue_t *queueURL = qopen();
	hashtable_t *hashURL = hopen(50);
	webpage_t *seedPage = webpage_new(seedURL, 0, NULL);
	
