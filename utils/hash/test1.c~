/* 
 * test1.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-11-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */
#include <stdio.h>
#include <stdlib.h> // Include the standard library for exit()
#include <string.h>
#include "hash.h"

int main() {
    hashtable_t *ht = hopen(10);
    
    if (ht == NULL) {
			// printf("Hashtable creation failed.\n");
        exit(EXIT_FAILURE);
    }

		int* value1 = (int*)42;
    int* value2 = (int*)99;

    if (hput(ht, value1, "key1", 4) != 0) {
			//printf("hput failed.\n");
			//hclose(ht);
        exit(EXIT_FAILURE);
    }
		/*

    if (hput(ht, &value2, "key2", 4) != 0) {
			//printf("hput failed.\n");
        hclose(ht);
        exit(EXIT_FAILURE);
				}*/

    hclose(ht);

    exit(EXIT_SUCCESS);
}
