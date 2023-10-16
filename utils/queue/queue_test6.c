/* 
 * queue_test6.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-10-2023
 * Version: 1.0
 * 
 * Description: qconcat success
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main() {
    // Create two queues
    queue_t* queue1 = qopen();
    queue_t* queue2 = qopen();

    // Sample data for queue1
    int data1 = 42;
    int data2 = 17;

    // Sample data for queue2
    int data3 = 99;
    int data4 = 23;

    // Put data into queue1 and queue2
    qput(queue1, &data1);
    qput(queue1, &data2);

    qput(queue2, &data3);
    qput(queue2, &data4);

    // Concatenate queue2 into queue1
    qconcat(queue1, queue2);

    // Test qget to check the concatenated queue
		// void* retrievedData;

    //while ((retrievedData = qget(queue1)) != NULL) {
			// printf("Retrieved data: %d\n", *(int*)retrievedData);
		// free(retrievedData);
    //}

    // Close and clean up the queues
    qclose(queue1);
    qclose(queue2);

    exit(EXIT_SUCCESS);
}

