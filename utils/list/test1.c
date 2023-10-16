/* 
 * test1.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-03-2023
 * Version: 1.0
 * 
 * Description: - should be successful - putting to an empty list
 * 
 */

#include <math.h>
#include "list.h"                                                              
#include <stdio.h>                                                             
#include <stdint.h>                                                            
#include <stdlib.h>                                                                               
#include <string.h>
#define MAXREG 10

static car_t *next=NULL;

void printList(car_t *car){
	printf("Price is: %f", car->price);
}

int main(int argc, char *argv[]){
	
	
	car_t *newCar = malloc(sizeof(car_t));

	newCar->price = 25;
	strcpy(newCar->plate, "Hello");
	newCar->year=2023;


	lapply(printList);
	
	int32_t result = lput(newCar);
	free(newCar);
	if(result == 0){
		exit(EXIT_SUCCESS);
	} else {
		exit(EXIT_FAILURE);
	}

}
