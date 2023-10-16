/* 
 * test5.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-09-2023
 * Version: 1.0
 * 
 * Description: should successfully apply() to an empty list 
 * 
 */

#include <math.h>                                                        
#include "list.h"                                                       \
                                                                         
#include <stdio.h>                                                      \
                                                                         
#include <stdint.h>                                                     \
                                                                         
#include <stdlib.h>                                                     \
                                                                         
#include <string.h>                                                      
#define MAXREG 10                                                        
                                                                         
static car_t *next=NULL;                                                 
                                                                         
void printList(car_t *car){                                              
  printf("Price is: %f", car->price);                                    
}                                                                        
                                                                         
int main(int argc, char *argv[]){                                        
                                                                         
                                                                         
  lapply(printCarInfo, next);
	
}
