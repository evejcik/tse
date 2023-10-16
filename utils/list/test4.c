/* 
 * test4.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-09-2023
 * Version: 1.0
 * 
 * Description: lget from a non-empty list - should return the first car in the list
 * 
 */

#include "list.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define MAXREG 10

static car_t *next = NULL;
int main(int argc, char *argv[]){
	car_t *newCar = malloc(sizeof(car_t));
	newCar->price = 25;                                                           
  strcpy(newCar->plate, "Hello");                                               
  newCar->year=2023;

	car_t *newCar2 = malloc(sizeof(car_t));
	newCar2->price = 25;
	strcpy(newCar2->plate, "Hello2");
	newCar2->year=2023;

	lput(newCar);
	lput(newCar2);

	car_t *getCar = lget(next);

	if(strcmp(getCar->plate, "Hello2") == 0){
		free(newCar);
		free(newCar2);
			exit(EXIT_SUCCESS);
		}else{
		free(newCar);
		free(newCar2);
			exit(EXIT_FAILURE);
				}
	
}
