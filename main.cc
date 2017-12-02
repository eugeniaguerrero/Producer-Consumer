/******************************************************************
 * The Main program with the two functions. A simple
 * example of creating and using a thread is provided.
 ******************************************************************/

#include "helper.h"

void *producer (void *id);
void *consumer (void *id);

int main (int argc, char **argv)
{
  int queue_size = argv[0];
  int jobs_per_producer = argv[1];
  int num_producers = argv[2];
  int num_consumers = argv[3];
  int consumer_job_counter = 0;
  int producer_job_counter = 0;

  // set up and initialise variables
  pthread_t producerid;
  pthread_t consumerid;
  int parameter = 5;

  // set up and initialise semaphores
  sem_create(ITEM, 1);
  sem_create(SPACE, 1);
  sem_create(MUTEX, 1);
  sem_init(ITEM, 1, 0);
  sem_init(SPACE, 1, N);
  sem_init(MUTEX, 1, 1);

  // create a shared data structure
  struct CircularQueue {
    int start, end;
    int size;
	int *array;

    CircularQueue(int queue_size){
      start = end = -1;
	  size = queue_size;
	  array = new int[queue_size];
    }

	void addToQueue(int value);
	int removeFromQueue();
	void printQueue();

  };
  
  // to print the elements of the queue
  void CircularQueue::printQueue(){
    if (start == -1){
	  cout << "The queue is empty" << endl;
	  break;
	}
	cout << "The elements in the circular queue are: " << endl;
	if (end >= start){
	  for (int i = start; i <= end; i++){
        cout << array[i];
	  }
	}
	else {
	  for (int i = front; i < size; i++){
        cout << array[i];
	  }
	  for (int i = 0; i <= rear; i++){
        cout << array[i];
	  }
	}
  }

  // initialise a queue that producers and consumers can access
  CircularQueue queue(queue_size);

  // create the required producers and consumers
  for (int i = 0; i < num_producers; i++){
  	pthread_create (&producerid, NULL, producer, (void *) &parameter);
  };
  for (int i = 0; i < num_consumers; i++){
	pthread_create (&consumerid, NULL, consumer, (void *) &parameter);
  };

  // wait for threads to terminate, then clean up resources used by the thread
  pthread_join (producerid, NULL);
  pthread_join (consumerid, NULL);
  return 0;
}

void *producer(void *parameter)
{
  // define method to exit from thread
  void pthread_exit(void *retval);

  while(){
  	int *param = (int *) parameter;
  	cout << "Parameter = " << *param << endl;

	}
  pthread_exit(0);
}

void *consumer (void *id)
{
  void pthread_exit(void *retval);

	// TODO
  int *id = (int *) id;

  cout << "Consumer(" << consumerid << "): Job id " << *id << endl;

  pthread_exit (0);

}

