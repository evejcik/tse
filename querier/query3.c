/* 
 * query3.c --- 
 * 
 * Author: Emma Vejcik
 * Created: 11-06-2023
 * Version: 1.0
 * 
 * Description: 
 * 
 */
#include <stdio.h>                                                                               
#include <stdlib.h>                                                                              
#include <string.h>                                                                              
#include <ctype.h>                                                                               
#include <dirent.h>                                                                              
#include <stdbool.h>                                                                             
#include <crawler.h>                                                                             
#include <indexer.h>                                                                             
                                                                                                 
                                                                                                 
const int ARRAY_SIZE = 25;                                                                       
                                                                                                 
char* checkQuery(char* token){                                                                   
                                                                                                 
  // Argment Checking                                                                            
  if (strlen(token) < 3){                                                                        
    return "NULL";                                                                               
  }                                                                                              
  if (strcmp(token,"and") == 0){                                                                 
    return "NULL";                                                                               
  }                                                                                              
  if (strcmp(token,"or") == 0){                                                                  
    return "NULL";                                                                               
  }                                                                                              
                                                                                                 
  for (int i = 0; i < strlen(token); i++){                                                       
    if (token[i] == '\n'){                                                                       
      token[i] = 0;                                                                              
    }                                                                                            
    else if ((isalpha(token[i]) == 0)){                                                          
      return "NULL";                                                                             
    }                                                                                            
    else{                                                                                        
      token[i]  = tolower(token[i]);                                                             
    }                                                                                            
  }                                                                                              
                                                                                                 
  return token;                                                                                  
}                                                                                                
                                                                                                 
int querySearch(char* word){                                                                     
  char wordComp[ARRAY_SIZE];                                                                     
  int docID;                                                                                     
  int wordCount = 0;                                                                             
  char line[10000];                                                                              
  char word [100];                                                                               
  int docIDs[100];                                                                               
  int numDocIDs = 0;                                                                             
  int rank = 1000000;                                                                            
  FILE* fp = fopen("index1.txt","r");                                                            
  if (fp == NULL){                                                                               
    printf("Error opening file\n");                                                              
  }                                                                                              
                                                                                                 
  while((fscanf(fp, "%s", wordComp) != EOF)){                                                    
    if ( strcmp(word, wordComp) == 0 ){                                                          
                                                                                                 
      while (fscanf(fp,"%d %d", &docID, &wordCount)== 2){                                        
        docIDs[numDocIDs] = docID;                                                               
        numDocIDs = numDocIDs + 1;                                                               
        if (wordCount < rank) {                                                                  
          rank = wordCount;                                                                      
        }                                                                                        
      }                                                                                          
                                                                                                 
    }                                                                                            
  }                                                                                              
                                                                                                 
                                                                                                 
  if (wordCount == 0)                                                                            
    return -1;                                                                                   
                                                                                                 
  return wordCount;                                                                              
                                                                                                 
  fclose(fp);                                                                                    
}                                                                                                
                                                                                                 
void rankDocument(char wordArray[ARRAY_SIZE][ARRAY_SIZE], int wordCnt[ARRAY_SIZE]){              
  int rank = 10000000;                                                                           
                                                                                                 
  for (int i = 0; i < ARRAY_SIZE; i++){                                                          
    if(( wordCnt[i] < rank ) && (wordCnt[i] != 0)){                                              
      rank = wordCnt[i];                                                                         
    }                                                                                            
  }                                                                                              
                                                                                                 
  for (int i = 0; i < ARRAY_SIZE; i++){                                                          
    if ( strcmp(wordArray[i],"NULL") != 0){                                                      
      printf("%s:%d ", wordArray[i],wordCnt[i]);                                                 
    }                                                                                            
    if ((i == (ARRAY_SIZE-1)) && (rank != 0)) {                                                  
        printf("- %d\n", rank);                                                                  
    }                                                                                            
  }                                                                                              
}                                                                                                
                                                                                                 
void intializeArray(char wordArray[ARRAY_SIZE][ARRAY_SIZE], int wordCntArray[ARRAY_SIZE]){       
                                                                                                 
  for(int i = 0; i < ARRAY_SIZE; i++){                                                           
    strcpy(wordArray[i],"NULL");                                                                 
    wordCntArray[i] = 0;                                                                         
  }                                                                                              
}                                                                                                
                                                                                                 
                                                                                                 
int main(void){                                                                                  
  char myString[ARRAY_SIZE];                                                                     
  //char wordArray [ARRAY_SIZE][ARRAY_SIZE];                                                     
  //int wordCntArray [ARRAY_SIZE];                                                               
  //int i = 0;                                                                                   
  //bool argCheck = true;                                                                        
  int depth = 3;                                                                                 
  char* startURL = NULL;                                                                         
  startURL = (char*)malloc(256);                                                                 
  startURL = "https://thayer.github.io/engs50/";                                                 
                                                                                                 
                                                                                                 
                                                                                                 
                                                                                                 
  //printf(">");                                                                                 
                                                                                                 
  while (depth > 0) {                                                                            
    printf("Enter a query: ");                                                                   
    fgets(myString, 25, stdin);                                                                  
    int i = 0;                                                                                   
    bool argCheck = true;                                                                        
    char wordArray [ARRAY_SIZE][ARRAY_SIZE];                                                     
    int wordCntArray[ARRAY_SIZE];                                                                
    intializeArray(wordArray,wordCntArray);                                                      
    char* token = strtok(myString," ");                                                          
    while ( token != NULL){                                                                      
      strcpy (wordArray[i], checkQuery(token));                                                  
      if (strcmp(wordArray[i],"NULL")==0){                                                       
        printf("Invalid query\n");                                                               
        argCheck = false;                                                                        
        break;                                                                                   
      }                                                                                          
      else{                                                                                      
        wordCntArray[i] = querySearch(wordArray[i]);                                             
        if (wordCntArray[i] == -1){                                                              
          printf("Invalid query\n");                                                             
          argCheck = false;                                                                      
          break;                                                                                 
        }                                                                                        
      }                                                                                          
      token = strtok(NULL," ");                                                                  
      i++;                                                                                       
    }                                                                                            
                                                                                                 
    if (argCheck != false){                                                                      
      rankDocument(wordArray,wordCntArray);                                                      
    }                                                                                            
                                                                                                 
    depth --;                                                                                    
    printf(">");                                                                                 
  }                                                                                              
                                                                                                 
  return 1;                                                                                      
}                                                                                                
                                                                                                 
                                                                                                 
                                                                                                 
                               
