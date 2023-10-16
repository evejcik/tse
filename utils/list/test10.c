/* 
 * test10.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-09-2023
 * Version: 1.0
 * 
 * Description: remove car from middle of list
 * 
 */

#include "list.h"                                                                                \       
                                                                                                         
#include <stdlib.h>                                                                              \       
                                                                                                         
#include <unistd.h>                                                                              \       
                                                                                                         
#include <math.h>                                                                                \       
                                                                                                         
#include "list.h"                                                                                \       
                                                                                                         
#include <stdio.h>                                                                               \       
                                                                                                         
#include <stdint.h>     
#include <string.h>                                                                                      
                                                                                                         
#define MAXREG 10                                                                                        
                                                                                                         
static car_t *front=NULL;                                                                                
                                                                                                         
int main(){                                                                                              
  car_t *newCar = malloc(sizeof(car_t));                                                                 
  newCar->price = 25;                                                                                    
  strcpy(newCar->plate, "Hello");                                                                        
  newCar->year=2023;                                                                                     
  front = newCar;

	car_t *carMiddle = malloc(sizeof(car_t));                                                        \
                                                                                                  
  carMiddle->price = 10;                                                                           \
                                                                                                  
  strcpy(carMiddle->plate, "Middle");
	
                                                                                                  
  carMiddle->year=2023;                                                                            \
                                                                                                  
  carMiddle->next = NULL;
                                                                                         
                                                                                                         
  car_t *newCar2 = malloc(sizeof(car_t));
  newCar2->price = 32;                                                                                   
  strcpy(newCar2->plate, "Bye");                                                        
  newCar2->year=2023;                                                                                    
  newCar2->next = NULL;
	
  lput(newCar);
	lput(carMiddle);
  lput(newCar2);                                                                                         
                                                                                                         
  car_t *car = lremove("Middle");
	
                                                                                                         
  if(car->price == 10){
		free(newCar2);
		free(newCar);
		free(carMiddle);
    exit(EXIT_SUCCESS);                                                                                  
  }/*else{                                                                                               
    exit(EXIT_FAILURE);                                                                                  
    }*/                                                                                                  
  free(car);
	free(newCar2);                                                                                                                                                          
    free(newCar);                                                                                                                                                           
    free(carMiddle);
  exit(EXIT_FAILURE);                                                                                    
}                                                                                                        
    
