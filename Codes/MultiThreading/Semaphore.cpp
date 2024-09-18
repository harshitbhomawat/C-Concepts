#include<iostream>
#include<pthread.h>
#include<semaphore.h>
using namespace std;
sem_t sem;
void* Worker(void* args)
{
	sem_wait(&sem);
	int* id = reinterpret_cast<int*>(args);
	usleep(1000000);
	cout<<"thread ("<<pthread_self()<<")"<<endl;
	sem_post(&sem);
}
int main()
{
	sem_init(&sem,0,3); //here 3 is the no. of max threads that can access shared resource concurrently.
	pthread_t threads[10];
	for(int i=0;i<10;i++)
	{
		pthread_create(&threads[i],NULL,Worker,reinterpret_cast<void*>(&i));
	}
	for(int i=0;i<10;i++)
	{
		pthread_join(threads[i],NULL);
	}
	sem_destroy(&sem);
}
