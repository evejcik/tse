/* 
 * queue_test4.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-10-2023
 * Version: 1.0
 * 
 * Description: use qsearch and qremove successfully
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Define a function to search for an element based on an integer key
bool searchFunction(void* elementp, const void* keyp) {
    int* element = (int*)elementp;
    int key = *(int*)keyp;
    return *element == key;
}

int main() {
    // Create a queue
    queue_t* myQueue = qopen();

    // Sample data
    int data1 = 42;
    int data2 = 17;
    int data3 = 99;

    qput(myQueue, &data1);
    qput(myQueue, &data2);
    qput(myQueue, &data3);

    // Define the key you want to search for
    int searchKey = 17;

    // Search for an element in the queue
    void* foundElement = qsearch(myQueue, searchFunction, &searchKey);

    if (foundElement) {
        printf("Element with key %d found: %d\n", searchKey, *(int*)foundElement);
    } else {
        printf("Element with key %d not found\n", searchKey);
    }

    qclose(myQueue);

    return EXIT_SUCCESS;
}

