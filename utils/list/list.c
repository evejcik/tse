/* 
 * list.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 09-30-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */

#include "list.h"
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "list.h"            
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define MAXREG 10                                                                         
                                                                                          
/* the representation of a car */                                                         
static car_t *front=NULL;

int32_t lput(car_t *cp){

	if (cp == NULL){
		return (int32_t)1;
	}
	else{
		cp->next = front;
		front  = cp;
			return (int32_t)0;
	}
}

car_t *lget(){
	if(front == NULL){
		return NULL;
	}
	car_t *firstCar = front;
	front = front->next;
	firstCar->next = NULL;
	return firstCar;
}

void lapply(void (*fn)(car_t *cp)){
	car_t *current = front;
	while(current != NULL){
		fn(current);
		current = current->next;
	}
}

car_t *lremove(char *platep){
	printf("first line of lremove\n");
	car_t *current = front;
	car_t *prev = NULL;
	while(current != NULL){
		if (strcmp(current->plate, platep) == 0){
			if(prev != NULL){
				prev->next = current->next;
			} else {
				front = current->next;
			}
			current->next = NULL;
			
			/*car_t *carTemp = malloc(sizeof(car_t));
			carTemp->price = current->price;
			carTemp->year=current->year;
			strcpy(carTemp->plate, current->plate);*/

			
			return current;
			//free(current);
			//return carTemp;
			//return current;
		}
		prev = current;
		current = current->next;
	}
	return NULL;
}
