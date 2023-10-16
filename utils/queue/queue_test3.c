/* 
 * queue_test3.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-10-2023
 * Version: 1.0
 * 
 * Description: qapply successfully
 * 
 */

#include <stdio.h>                                                                                                        
#include <stdlib.h>                                                                                                       
#include "queue.h" // Include your queue header                                                                           
void printData(void* elementp) {
    printf("Data: %d\n", *(int*)elementp);
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

		qapply(myQueue, printData);
		
		qclose(myQueue);

		exit(EXIT_SUCCESS);
}
