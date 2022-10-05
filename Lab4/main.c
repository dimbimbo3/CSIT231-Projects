#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//Constants
#define NUMBER_OF_DARTS   50000000
#define NUMBER_OF_THREADS 4

//Global variables
int circle_count = 0; //number of hits in circle
pthread_mutex_t mutex;  //mutex lock declaration

//Function declaration
void *getCirclePoints(void*);

int main() {
  double pi;
  //Distribute darts between threads
  int dartsPerThread = NUMBER_OF_DARTS/NUMBER_OF_THREADS;
  //Declare array of threads
  pthread_t threads[NUMBER_OF_THREADS];
  //Initialize mutex lock
  pthread_mutex_init(&mutex, NULL);
  //Initialize random generator
  srand(time(NULL));

  //Clock variables
  clock_t start, end;
  double cpu_time_used;

  //Start Time   
  start = clock();

  //Creates the threads
  for(int i = 0; i < NUMBER_OF_THREADS; i++){
    pthread_create(&threads[i], NULL, getCirclePoints, &dartsPerThread);
  }

  //Terminates the threads upon completion
  for(int i = 0; i < NUMBER_OF_THREADS; i++){
    pthread_join(threads[i], NULL);
  }

  //Estimated pi value
  pi = (double)(4 * circle_count) / NUMBER_OF_DARTS;

  //End Time
  end = clock();

  //Calculates total time spent on estimation
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  printf("Total Hits: %d\n", circle_count);
  printf("Total CPU Time: %f\n", cpu_time_used);
  printf("Final estimation of Pi: %f\n", pi);

  return 0;
}

//Calculates the number of darts that land within the circle
void *getCirclePoints(void *ptr){
  int *dartCount = (int*)ptr;
  double randomX, randomY, originDist;
  for(int i = 0; i < *dartCount; i++){
    //Generates random x & y points between -1 and 1
    randomX = ((double) rand() / RAND_MAX) * (2) - 1;
    randomY = ((double) rand() / RAND_MAX) * (2) - 1;
    //Calculates the distance between (x,y) from the origin
    originDist = sqrt(randomX*randomX + randomY*randomY);

    //Checks if the coordinate is within the radius of the circle,
    //if so utilizes mutex lock and adds to the global count
    if(originDist < 1){
      pthread_mutex_lock(&mutex);
      circle_count++;
      printf("(%d of %d) X:%f, Y:%f\t- Hit!\n", i+1, *dartCount, randomX, randomY);
      pthread_mutex_unlock(&mutex);
    }
    else
      printf("(%d of %d) X:%f, Y:%f\n", i+1, *dartCount, randomX, randomY);
  }
  pthread_exit(NULL);
}