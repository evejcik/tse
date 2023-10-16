/* 
 * test3.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-11-2023
 * Version: 1.0
 * 
 * Description: test hsearch successfully
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"
#include "hash.h"


// Define a structure to represent an entry
struct Entry {
    char *key;
    int value;
};

// Sample search function that matches by key
bool key_search(void *elementp, const void *searchkeyp) {
    const struct Entry *entry = (const struct Entry *)elementp;
    const char *key = (const char *)searchkeyp;

    return (strcmp(entry->key, key) == 0);
}

int main() {
    hashtable_t *htp = hopen(5);  // Create a hash table with 5 slots

    // Create some sample entries and add them to the hash table
    struct Entry entry1 = {"key1", 10};
    struct Entry entry2 = {"key2", 20};
    struct Entry entry3 = {"key3", 30};

    hput(htp, &entry1, "key1", strlen("key1"));
    hput(htp, &entry2, "key2", strlen("key2"));
    hput(htp, &entry3, "key3", strlen("key3"));

    // Search for an entry with the key "key2"
    const char *search_key = "key2";
    struct Entry *result = (struct Entry *)hsearch(htp, key_search, search_key, strlen(search_key));

    if (result != NULL) {
        printf("Entry found: Key = %s, Value = %d\n", result->key, result->value);
    } else {
        printf("Entry not found for key: %s\n", search_key);
    }

    // Clean up the hash table
    hclose(htp);

    exit(EXIT_SUCCESS);
}

