/* 
 * test1.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 10-27-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */
#include <webpage.h>                                                                            
#include "pageio.h"                                                                             
                                                                                                
int main (void){                                                                                
                                                                                                
  // Load page in test directory                                                                
  webpage_t* pg1 = pageload(1, "../test");                                                      
                                                                                                
  // Save page in test directory                                                                
  pagesave(pg1, 2, "../test/");                                                                 
                                                                                                
  // Load new page in test directory                                                            
  webpage_t* pg2 = pageload(2, "../test");                                                      
                                                                                                
  // Save new page in test directory                                                            
  pagesave(pg2, 3, "../test/");                                                                 
                                                                                                
  webpage_delete(pg1);                                                                          
  webpage_delete(pg2);                                                                          
                                                                                                
  return 1;                                                                                     
}                                                                                               
      
