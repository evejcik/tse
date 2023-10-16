/* 
 * test6.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-09-2023
 * Version: 1.0
 * 
 * Description: should use lapply successfully on a non-empty list 
 * 
 */

#include <math.h>
#include "list.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>                                                                           
#define MAXREG 10                                                                             
                                                                                              
//static car_t *next=NULL;                                                                      
                                                                                              
void changePrice(car_t *car){
	car->price = 5.0;
  printf("Price is: %f", car->price);                                                         
}

int main(int argc, char *argv[]){
	
	car_t *newCar = malloc(sizeof(car_t));                                 
  newCar->price = 25;                                                   \
                                                                         
  strcpy(newCar->plate, "Hello");                                       \
                                                                         
  newCar->year=2023;
	newCar->next = NULL;
                                                                         
  car_t *newCar2 = malloc(sizeof(car_t));                                
  newCar2->price = 252;                                                  
  strcpy(newCar2->plate, "Hello2");                                      
  newCar2->year=20232;
	newCar2->next = newCar;
                                                                         
  lput(newCar);                                                          
  lput(newCar2);
	
	lapply(changePrice);
	
	/*car_t *car = next;
	while(car != NULL){
		if(car->price !=3.0){
			exit(EXIT_FAILURE);
		}
		car = car->next;
	}
	exit(EXIT_SUCCESS);*/

	if(newCar->price != 5.0){
		free(newCar);
		free(newCar2);
		exit(EXIT_FAILURE);
	}
	if(newCar2->price != 5.0){
		free(newCar);
		free(newCar2);
		exit(EXIT_FAILURE);
	}
	free(newCar);
	free(newCar2);
	exit(EXIT_SUCCESS);
}
      
