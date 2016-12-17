/**
 * General structure of a student.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#include <stdlib.h>
#include "ta.h"

void *student_loop(void *param)
{
	
	
	int number = *((int *)param);
	int sleep_time;
	printf("I am student %d\n", number);

	srandom((unsigned)time(NULL));
	sleep_time = (int)((random() % MAX_SLEEP_TIME) + 1);
	int waiting = 0;
	
				while(1)
				{
				if(waiting < NUM_OF_SEATS)
				{
					
					//student has not woken the TA yet
					printf("TA is sleeping.  Student %d is waking him up.\n", number);
					pthread_mutex_lock(&mutex);
					waiting++;
					pthread_mutex_unlock(&mutex);
					//notify TA that student needs help
					sem_post(&sem_ta);
								
					printf("Student %d is seated in hall.  Seats taken %d \n", number, waiting);

					//wating for Ta
					sem_wait(&sem_stu);
					pthread_mutex_lock(&mutex);
					waiting--;
					pthread_mutex_unlock(&mutex);
					//TA helps student
					printf("Ta is helping student %d \n", number);

					
				}
				else
					programming(sleep_time);
				}
		
		
		
		
	
	return NULL;
}
