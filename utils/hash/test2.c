/* 
 * test2.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-11-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */

#include <stdio.h>
#include <stdlib.h>  // Include for exit() and EXIT_SUCCESS/EXIT_FAILURE
#include "queue.h"
#include "hash.h"

// Define a sample function to apply to entries
void print_entry(void *ep) {
    int *data = (int *)ep;
    printf("%d ", *data);
}

int main() {
    hashtable_t *htp = hopen(5);  // Create a hash table with 5 slots

    int data[] = {1, 2, 3, 4, 5};
    
    // Insert data into the hash table
    for (int i = 0; i < 5; i++) {
        hput(htp, &data[i], "key", 3);
    }

    printf("Entries in the hash table: ");
    happly(htp, print_entry);  // Apply the print_entry function to all entries
    printf("\n");

    // Clean up the hash table
    hclose(htp);

    exit(EXIT_SUCCESS);  // Test succeeded

    // If you reached this point, something went wrong
    exit(EXIT_FAILURE);  // Test failed
}

