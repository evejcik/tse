/* 
 * queue_test1.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-10-2023
 * Version: 1.0
 * 
 * Description:  to successfully open a queue, add an element , close the queue
 * 
 */

#include <math.h>                                                                                         
#include <stdio.h>
#include <stdlib.h>
#include "queue.h" // Include your queue header file here

int main() {
    // Test qopen
    queue_t* myQueue = qopen();
    if (myQueue == NULL) {
        fprintf(stderr, "qopen failed\n");
        exit(EXIT_FAILURE);
    }

    // Test qput
    int data1 = 42;
    if (qput(myQueue, &data1) != 0) {
        fprintf(stderr, "qput failed\n");
        exit(EXIT_FAILURE);
    }

  

    // Ensure that qput and qclose work with NULL pointers
    if (qput(NULL, &data1) != 1) {
        fprintf(stderr, "qput and qclose with NULL pointers failed\n");
        exit(EXIT_FAILURE);
    }

    // Test qput and qclose again after closing the queue
    if (qput(myQueue, &data1) != 0) {
        fprintf(stderr, "qput after qclose failed\n");
        exit(EXIT_FAILURE);
    }

    qclose(myQueue);

    printf("All tests passed\n");
    return EXIT_SUCCESS;
}
