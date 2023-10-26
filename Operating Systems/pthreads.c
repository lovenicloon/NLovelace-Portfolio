/*
*	File name:  nicolas_lovelace_2.c
*	Author:		  Nicolas Lovelace
*	Date:		    Oct. 16, 2022
*	Class:		  CS3513
*	Purpose:	  Multiply user-entered matrices using pthreads.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*#define M 3
#define K 2
#define N 3

int A [M] [K] = { { 1, 4 }, { 2, 5 }, { 3, 6 } };
int B [K] [N] = { { 8, 7, 6 }, { 5, 4 ,3 } };*/

/*#define M 2
#define K 2
#define N 2

int A [M] [K] = { { 1, 4 }, { 2, 5 } };
int B [K] [N] = { { 1, 0 }, { 0, 1 } };*/

#define M 4
#define K 2
#define N 3

int A [M] [K] = { { 5, 3 }, { 1, 4 }, { 7, 2 }, { 4, 9 } };
int B [K] [N] = { { 8, 7, 6 }, { 5, 4 ,3 } };

int C [M] [N]; //resulting matrix

#define TS M*N //amount of threads
pthread_t workers[TS]; //thread storage

struct v{
  int i;
  int j;
};

void *multiply(void *mems){
  struct v *data = (struct v*)mems;
  for(int n=0; n<K; n++){
    C[data->i][data->j] += A[data->i][n]*B[n][data->j]; //doing the multiplication part, function used by each thread
  }
  
  return 0;
}

int main(){ 
  char go;
  do{
    for(int i=0; i<M; i++){
      for(int j=0; j<K; j++){
        printf("%d ", A[i][j]); //printing out first matrix
      }
      printf("\n");
    }
    printf("\nX\n");
    for(int i=0; i<K; i++){
      for(int j=0; j<N; j++){
        printf("%d ", B[i][j]); //printing out second matrix
      }
      printf("\n");
    }
    
    printf("The multiplication of these matrices is: \n");

    int o = 0;
    for(int i=0; i<M; i++){
      for(int j=0; j<N; j++){
        struct v *data = (struct v *) malloc(sizeof(struct v)); //creating a data structure to pass to each thread
        data->i = i;
        data->j = j; //storing position in matrix the thread will be dealing with
        pthread_create(workers + o, NULL, multiply, (void*)data); //going through each worker thread and giving it the multiply function
        o++;
      }
    }

    for(int i=0; i<TS; i++){
      pthread_join(workers[i], NULL);
    } //joining all worker threads together and ending the process

    for(int i=0; i<M; i++){
      for(int j=0; j<N; j++){
        printf("%d ", C[i][j]); //printing resulting matrix
      }
      printf("\n");
    }
    
    printf("Would you like to continue?\n");
    scanf("%c", &go);
  }while(go=='y');
  
  
  return 0;
}
