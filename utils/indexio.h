/* 
 * indexio.h --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-30-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */

#include <stdint.h>                                                              
#include <stdbool.h>                                                             
#include "hash.h"                                                                
#include "queue.h"                                                               
                                                                                 
                                                                                 
/* */                                                                            
void indexsave(hashtable_t *htp, char* indexnm);                                 
                                                                                 
/* hclose -- closes a hash table */                                              
hashtable_t indexload(hashtable_t *htp, char* indexnm);                          
                                                                                 
                                                                                 
                                                                                 
                                                                                 
