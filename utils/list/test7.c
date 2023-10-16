/* 
 * test7.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-09-2023
 * Version: 1.0
 * 
 * Description: should successfully apply lremove to an empty list 
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

car_t *front = NULL;

int main(){
	car_t *car = lremove("plate");
	if(car != NULL){
		exit(EXIT_FAILURE);
	}else{
		exit(EXIT_SUCCESS);
	}
}
