/* 
 * queue_test2.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-10-2023
 * Version: 1.0
 * 
 * Description: qget successfully 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h" // Include your queue header


int main() {
    // Create a queue
    queue_t* myQueue = qopen();

    // Sample data

		int *data1 = malloc(sizeof(int));
		int *data2 = malloc(sizeof(int));
		int *data3 = malloc(sizeof(int));

		//int data1 = 42;
    //int data2 = 17;
    //int data3 = 99;

    qput(myQueue, data1);
    qput(myQueue, data2);
    qput(myQueue, data3);
    // Put data into the queue

    // Test qget
		void* retrievedData1 = malloc(sizeof(void*));
    //void* retrievedData1 = qget(myQueue);

		retrievedData1 = qget(myQueue);
		if((int*)retrievedData1){
			exit(EXIT_SUCCESS);
		}else{
			exit(EXIT_FAILURE);
		}
		free(data2);
		free(data3);
		free(data1);
		free(retrievedData1);
    // Close and clean up the queue
    qclose(myQueue);

    //return EXIT_SUCCESS;
}

