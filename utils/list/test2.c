/* 
 * test2.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-08-2023
 * Version: 1.0
 * 
 * Description: should be successful - putting to a non-empty list
 * 
 */
#include "list.h"
#include <stdio.h>                                                                                                                                      
#include <stdint.h>                                                                                                                                       
#include <stdlib.h>                                                                                                                                       
#include <string.h>                                                                                                                                       
#define MAXREG 10

static car_t *next=NULL;

int main(int argc, char *argv[]){
	car_t *newCar = malloc(sizeof(car_t));
	newCar->price = 25;                                                                      
  strcpy(newCar->plate, "Hello");                                                          
  newCar->year=2023;

	car_t *newCar2 = malloc(sizeof(car_t));
	newCar2->price = 252;
	strcpy(newCar2->plate, "Hello2");
  newCar2->year=20232;

	car_t *newCar3 = malloc(sizeof(car_t));                                                        
  newCar3->price = 253;                                                                         
  strcpy(newCar3->plate, "Hello3");                                                             
  newCar3->year=20233; 

	lput(newCar);
	lput(newCar2);
	int32_t result  = lput(newCar3);


	free(newCar);
	free(newCar2);
	free(newCar3);
	if(result == 0){
		printf("Exit Success");
	}else{
		printf("Exit Failure");
	}
}
