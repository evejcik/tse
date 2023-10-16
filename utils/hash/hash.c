/* 
 * hash.c -- implements a generic hash table as an indexed set of queues.
 *
 */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "hash.h"
#include "queue.h"
#include <string.h>
#include <stdbool.h>
/* 
 * SuperFastHash() -- produces a number between 0 and the tablesize-1.
 * 
 * The following (rather complicated) code, has been taken from Paul
 * Hsieh's website under the terms of the BSD license. It's a hash
 * function used all over the place nowadays, including Google Sparse
 * Hash.
 */
#define get16bits(d) (*((const uint16_t *) (d)))
/*
typedef struct entry {
	char *key;
	void *value;
	struct entry *next;
} entry_t;*/

typedef struct hashtable {
    queue_t **table;
    int size;
} hashtable;

//static unsigned long hash_function(const char *key, int keylen, int size);

static uint32_t SuperFastHash (const char *data,int len,uint32_t tablesize) {
  uint32_t hash = len, tmp;
  int rem;
  
  if (len <= 0 || data == NULL)
		return 0;
  rem = len & 3;
  len >>= 2;
  /* Main loop */
  for (;len > 0; len--) {
    hash  += get16bits (data);
    tmp    = (get16bits (data+2) << 11) ^ hash;
    hash   = (hash << 16) ^ tmp;
    data  += 2*sizeof (uint16_t);
    hash  += hash >> 11;
  }
  /* Handle end cases */
  switch (rem) {
  case 3: hash += get16bits (data);
    hash ^= hash << 16;
    hash ^= data[sizeof (uint16_t)] << 18;
    hash += hash >> 11;
    break;
  case 2: hash += get16bits (data);
    hash ^= hash << 11;
    hash += hash >> 17;
    break;
  case 1: hash += *data;
    hash ^= hash << 10;
    hash += hash >> 1;
  }
  /* Force "avalanching" of final 127 bits */
  hash ^= hash << 3;
  hash += hash >> 5;
  hash ^= hash << 4;
  hash += hash >> 17;
  hash ^= hash << 25;
  hash += hash >> 6;
  return hash % tablesize;
}

hashtable_t *hopen(uint32_t hsize) {
    if (hsize <= 0) {
        return NULL;
    }

		hashtable *ht = (hashtable *)malloc(sizeof(hashtable));
		ht->size = hsize;
		ht->table = (queue_t **)malloc(sizeof(queue_t *) * hsize);

		int i = 0;
		while(i < hsize){
			queue_t* pq = qopen();
			ht->table[i] = pq;
			i++;
		}
		return (hashtable_t *)ht;
}
			

void hclose(hashtable_t *htp) {
    hashtable *h = (hashtable *)htp;
    if (h == NULL) {
        return;
    }

		int i = 0;
		while(i < h->size){
			queue_t *q = h->table[i];
			if(q != NULL){
				qclose(q);
			}
			i++;
		}

		free(h->table);
		free(h);
}

int32_t hput(hashtable_t *htp, void *ep, const char *key, int keylen) {
    if (htp == NULL || ep == NULL || key == NULL || keylen <= 0) {
        // Handle invalid input.
        return -1;  // You can choose a meaningful error code.
    }

    hashtable *ht = (hashtable *)htp;

    // Calculate the hash value for the key.
    uint32_t hash = SuperFastHash(key, keylen, ht->size);

    // Use the qput function to add the entry to the appropriate queue.
    int result = qput(ht->table[hash], ep);

    return result;
}

void happly(hashtable_t *htp, void (*fn)(void* ep)){

if (htp == NULL || fn == NULL) {
        // Handle invalid input.
        return;
    }

    hashtable *ht = (hashtable *)htp;

    // Iterate over each queue in the hash table and apply the function to each entry.
    for (int i = 0; i < ht->size; i++) {
        queue_t *qp = ht->table[i];
        if (qp != NULL) {
            qapply(qp, fn);  // Apply the function to the entries in the queue.
        }
    }
}

void *hsearch(hashtable_t *htp,
              bool (*searchfn)(void *elementp, const void *searchkeyp),
              const char *key,
              int32_t keylen) {
    if (htp == NULL || searchfn == NULL || key == NULL || keylen <= 0) {
        // Handle invalid input.
        return NULL;
    }

    hashtable *ht = (hashtable *)htp;

    // Calculate the hash value for the key.
    uint32_t hash = SuperFastHash(key, keylen, ht->size);

    // Use the qsearch function to search for the entry in the appropriate queue.
    return qsearch(ht->table[hash], searchfn, key);
}


void *hremove(hashtable_t *htp,
              bool (*searchfn)(void *elementp, const void *searchkeyp),
              const char *key,
              int32_t keylen) {
    if (htp == NULL || searchfn == NULL || key == NULL || keylen <= 0) {
        // Handle invalid input.
        return NULL;
    }

    hashtable *ht = (hashtable *)htp;

    // Calculate the hash value for the key.
    uint32_t hash = SuperFastHash(key, keylen, ht->size);

    // Use the qremove function to remove and return the entry from the appropriate queue.
    return qremove(ht->table[hash], searchfn, key);
}



/*static unsigned long hash_function(const char *key, int keylen, int size) {
    unsigned long hash = 5381;
    for (int i = 0; i < keylen; i++) {
        hash = ((hash << 5) + hash) + key[i];
    }
    return hash % size;
		}*/
/*int32_t hput(hashtable_t *htp, void *ep, const char *key, int keylen){
	if (ht == NULL || ep == NULL || key == NULL || keylen <= 0) {
        return -1;  // Invalid input
    }

    uint32_t index = hash_function(key) % ht->size; // Implement a suitable hash function here

    // Create a new key-value pair
    struct KeyValue *new_pair = create_pair(key, keylen, ep);
    if (new_pair == NULL) {
        return -2;  // Memory allocation error
    }

    if (ht->table[index] == NULL) {
        // If the slot is empty, insert the pair
        ht->table[index] = new_pair;
    } else {
        // If the slot is not empty, handle collisions by chaining
        struct KeyValue *current = ht->table[index];
        while (current != NULL) {
            if (strcmp(current->key, key) == 0 && current->keylen == keylen) {
                // Key already exists in the hash table; update the value
                current->value = ep;
                free((void *)key); // Free the duplicate key
                free(new_pair);    // Free the duplicate key-value pair
                return 1; // Key already exists, value updated
            }
            current = current->next;
        }
        current = new_pair; // Add the new key-value pair to the end of the chain
    }

    return 0;  // Success
}


void happly(hashtable_t *htp, void (*fn)(void* ep)) {
    if (htp == NULL) {
        return;
    }

    for (uint32_t i = 0; i < htp->size; i++) {
        struct KeyValue *current = htp->table[i];
        while (current != NULL) {
            // Apply the user-defined function to the current key-value pair
            fn(current);
            current = current->next;
        }
    }
}

void *hsearch(hashtable_t *htp, bool (*searchfn)(void* elementp, const void* searchkeyp),const char *key,int32_t keylen){
	if (htp == NULL || searchfn == NULL || key == NULL) {
        return NULL;
    }

    for (uint32_t i = 0; i < htp->size; i++) {
        struct KeyValue *current = htp->table[i];
        while (current != NULL) {
					if (searchfn(current, key, keylen)) {
							return current; // Entry found, return a pointer to the entry
            }
            current = current->next;
        }
    }
		
    return NULL; // Entry not found
}

void *hremove(hashtable_t *htp,                                                 
							bool (*searchfn)(void* elementp, const void* searchkeyp),               
							const char *key,                                                        
							int32_t keylen){
	if (ht == NULL || searchfn == NULL || key == NULL) {
		return NULL;
	}
	
	uint32_t index = hash_function(key) % ht->size; // Implement a suitable hash function here
	
	struct KeyValue *prev = NULL;
	struct KeyValue *current = ht->table[index];
	
	while (current != NULL) {
		if (searchfn(current, key, keylen)) {
			// Entry found, remove it from the hash table
			if (prev == NULL) {
				ht->table[index] = current->next;
			} else {
				prev->next = current->next;
			}
			return current; // Return a pointer to the removed entry
			}
		prev = current;
		current = current->next;
	}
	
	return NULL; // Entry not found
}
*/
