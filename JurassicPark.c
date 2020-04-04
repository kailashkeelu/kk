#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>



int passenger , car;

sem_t mutex , ForCar;

void * GoDino(void * args);
void get_in_car( int person );
void get_out_car( int person );
void * GoDino(void * args)
{
    
        int * i = (int *) args;
       
        
        printf("\n Passenger %d  is going to look for a car.\n",*i);
            get_in_car(*i );
            sleep(1);
            get_out_car(*i );
        
     
}

void get_in_car( int person )
{
    

    
    
    
    printf("\nPassenger %d is waiting for the car.\n",person);
    sem_wait(&ForCar);
    
    sem_wait(&mutex);
    printf("\n Passenger %d got in his car",person);
    printf(" \n Now %d cars are left & %d passengers are there.\n",--car , --passenger);
    sleep(1);
    sem_post(&mutex);
    
}

void get_out_car( int person )
{
    printf("\nPassenger  %d is getting out of car.\n",person);
    sem_wait(&mutex);
    car++;

    sem_post(&ForCar);

    printf("\n Now %d cars are left & %d passengers are there.\n",car,passenger);
    sem_post(&mutex);
    
}


int main ()
{
    printf("Enter the input n(Passengers) and m(Cars), (space separated):  ");
    scanf("%d %d",&passenger , &car);
    int n = passenger;
    pthread_t ptid[n];

    sem_init(&mutex,0,1);
    sem_init(&ForCar,0,car);
    
    int* pipid = (int * ) malloc(sizeof(int)* n);

    for(int i = 0 ; i < n ; ++i )
	{
        pipid[i] = i + 1;
    }
    
    for(int i = 0 ; i < n ; ++i)
    {
        
        pthread_create(&ptid[i],NULL,(void *)GoDino, &pipid[i]);
           
    }

    for( int i = 0 ; i < n ; ++i)
    {
        pthread_join(ptid[i],NULL);
    }

    printf("\n All of the passengers have enjoyed the rides.");

    return 0;
    //Kindly change the compiler settings to -std=c11 if not running. 
    //Regards
}



