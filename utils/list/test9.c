/* 
 * test9.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-09-2023
 * Version: 1.0
 * 
 * Description: remove last car successfully 
 * 
 */


#include "list.h"                                                                                \
                                                                                                  
#include <stdlib.h>                                                                              \
                                                                                                  
#include <unistd.h>                                                                              \
                                                                                                  
#include <math.h>                                                                                \
                                                                                                  
#include "list.h"                                                                                \
                                                                                                  
#include <stdio.h>                                                                               \
                                                                                                  
#include <stdint.h>                                                                              \
                                                                                                  
#include <string.h>      
                                                                                                  
#define MAXREG 10                                                                                 
                                                                                                  
static car_t *front=NULL;                                                                         
                                                                                                  
int main(){                                                                                       
  car_t *newCar = malloc(sizeof(car_t));                                                          
  newCar->price = 25;                                                                             
  strcpy(newCar->plate, "Hello");                                                                 
  newCar->year=2023;                                                                              
  front = newCar;                                                                                 
                                                                                                  
  car_t *newCar2 = malloc(sizeof(car_t));                                                         
  newCar2->price = 32;                                                                            
  strcpy(newCar2->plate, "Bye");                \                                                 
  newCar2->year=2023;                                                                             
  newCar2->next = NULL;                                                                           
  newCar->next = newCar2;                                                                         
                                                                                                  
  lput(newCar);                                                                                   
  lput(newCar2);                                                                                  
                                                                                                  
  car_t *car = lremove("Hello");                                                                    
                                                                                                  
                                                                                                  
  if(car->price == 25){
		free(newCar);
		free(newCar2);
    exit(EXIT_SUCCESS);                                                                           
  }/*else{                                                                                        
    exit(EXIT_FAILURE);                                                                           
    }*/                                                                                           
  free(car);
	free(newCar);
	free(newCar2);
  exit(EXIT_FAILURE);                                                                             
}                                                                                                 
   
