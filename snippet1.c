#include <stdio.h>
#include <process.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
/* Program that utilizes pthread.h to manipulate threads
 */

// GLOBAL VARIABLES
///
int x; // Payload (Data)
pthread_mutex_t aLock; // Mutex lock
//

// Getter and Setters
void setX(void*);
void getX(void*);

int main (void){
   	
   	aLock = PTHREAD_MUTEX_INITIALIZER;
   	
	// Initializing the Threads
	pthread_t one;
	pthread_t two;

    pthread_create(&one, NULL, (void*)&getX, NULL); // Runs thread one
    Sleep(200); //creates a delay to give time to the first thread
    pthread_create(&two, NULL, (void*)&setX, NULL); // Runs thread two
	getch();//allows user to see output of the threads

    return 0;
}

void setX(void * arg){
    int i;
    
	srand(time(NULL));
    
    for(i = 0; i < 10; i++){
        pthread_mutex_lock(&aLock); // Locks the mutex
		x = rand() % 10; //randomizes the value of x
		pthread_mutex_unlock(&aLock); // Unlocks the mutex
        Sleep(1000); //delays to let other thread iterate
    }
    return;
}

void getX(void* arg){
    int i;

    for (i = 0; i < 10; i++){
        pthread_mutex_lock(&aLock);	// Locks the mutex
        printf("x equals %d:%d\n",i,x); //prints the x value
        pthread_mutex_unlock(&aLock);	// Unlocks the mutex
        Sleep(1000); //delays to allow other thread to change value
    }
    return;
}
