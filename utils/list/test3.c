/* 
 * test3.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-08-2023
 * Version: 1.0
 * 
 * Description: lget from an empty list successfully - should return a NULL value
 * 
 */

#include <math.h>                                                                               
#include "list.h"                                                                               
#include <stdio.h>                                                                              
#include <stdint.h>                                                                             
#include <stdlib.h>                                                                            \
                                                                                                
#include <string.h>                                                                             
#define MAXREG 10                                                                               
                                                                                                
static car_t *next=NULL;
int main(int argc, char *argv[]){
	car_t *car = NULL;
	car_t *getCar = lget(car);
	if(getCar == NULL){
		exit(EXIT_SUCCESS);
	}else{
		exit(EXIT_FAILURE);
	}
  
}
        
