/* 
 * queue_test5.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-10-2023
 * Version: 1.0
 * 
 * Description: qremove successfully
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

    // Define the key you want to remove
    int removeKey = 17;

    // Remove an element from the queue
    void* removedElement = qremove(myQueue, searchFunction, &removeKey);

    // Close and clean up the queue
    qclose(myQueue);

    return EXIT_SUCCESS;
}
