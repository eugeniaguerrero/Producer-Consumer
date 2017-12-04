/******************************************************************
 * The Main program with the two functions. A simple
 * example of creating and using a thread is provided.
 ******************************************************************/

#include "helper.h"

void *producer (void *id);
void *consumer (void *id);

int main (int argc, char **argv)
{
/*                        
					Validate and initialise input parameters                             
*/
	// check enough parameters are given.
	if (argc < 5 || argc >= 6){
		cerr << "Error: insufficient number of parameters provided. ";
		cerr << "Number of parameters must be 5." << endl;
		return -1;
	}
	// check input parameters are of the correct format.
	for (int i = 0; i < argc; i++){
		if (i >= 1 && i <= 4){
			int result = check_arg(argv[i]);
			if (result == -1) {
				cerr << "Error with the supplied parameters: ";
				cerr << "non-numeric input at position " << i << "." << endl;
				return -1;
			}
		}
	}
	// now that we have checked parameters are of correct number and format,
	// initialise variables with parameter values.
	int queue_size = check_arg(argv[1]);
	int jobs_per_producer = check_arg(argv[2]);
	int num_producers = check_arg(argv[3]);
	int num_consumers = check_arg(argv[4]);
	cout << "Queue size = " << queue_size << "; ";
	cout << "jobs per producer = " << jobs_per_producer << "; ";
	cout << "number of producers = " << num_producers << "; ";
	cout << "number of consumers = " << num_consumers << "." << endl;


/*                     
                   Create consumers and producers threads and variables                          
*/   
    // create producer and consumer thread ids, to be set by pthread_create()
    pthread_t producerid;
    pthread_t consumerid;


    // create the required producers
	for (int i = 0; i < num_producers; i++){
		int return_producer;
		int parameter = i;

		cout << "Creating producer " << i+1 << " in main" << endl;
		return_producer = pthread_create (&producerid, NULL, producer, (void *) &parameter);

		if (return_producer){
			printf("ERROR: return code from pthread_create() is %d\n", return_producer);
			exit(-1);
		};
    };
	
	// create the required consumers
	for (int i = 0; i < num_consumers; i++){
		int return_consumer;
		int id = i;

		cout << "Creating consumer " << i+1 << " in main" << endl;
		return_consumer = pthread_create (&consumerid, NULL, consumer, (void *) &id);

		if (return_consumer){
			printf("ERROR: return code from pthread_create() is %d\n", return_consumer);
			exit(-1);
		};
	};
	
	// set up and initialise semaphores
	int semid = sem_create(SEM, 3);
	// check semaphore is initialised without errors
	if(sem_init(SEM, 1, 1) == -1){
	  printf("sem_init: failed: %s\n",strerror(errno));
	};

	sem_init(semid, ITEM, 0); // Item semaphore 
	sem_init(semid, SPACE, queue_size); // Space semaphore
	sem_init(semid, MUTEX, 1); // Mutex semaphore


/*
					Create a circular queue and its associated methods
*/
	// create a data structure
	struct Queue {
		int start, end;
		int size;
		int *array;

		Queue(int queue_size){
				start = end = -1;
				size = queue_size;
				array = new int[queue_size];
		}

		void addToQueue(int job);
		void removeFromQueue();
		// void printQueue(){
		// 	if (start == -1){
		// 		cout << "The queue is empty" << endl;
		// 		return;
		// 	}
		// 	cout << "The elements in the circular queue are: " << endl;
		// 	if (end >= start){
		// 		for (int i = start; i <= end; i++){
		// 			cout << array[i];
		// 		}
		// 	}
		// 	else {
		// 		for (int i = start; i < size; i++){
		// 			cout << array[i];
		// 		}
		// 		for (int i = 0; i <= end; i++){
		// 			cout << array[i];
		// 		}
		// 	}
		// }
	};

  // initialise a queue that producers and consumers can access
  Queue circularQueue(queue_size);


  // Process clean-up: wait for threads to terminate & clean up resources
  pthread_join (producerid, NULL);
  pthread_join (consumerid, NULL);

  return 0;
}

void *producer(void *producer_id)
{
	int *param = (int *) producer_id;
	cout << "Producer(" << *param << "): " << endl;
	// sem_wait(SPACE);
	// sem_wait(MUTEX);
	// // addToQueue(jobId);
	// sem_signal(MUTEX);
	// sem_signal(ITEM);

  pthread_exit(0);
}

void *consumer (void *consumer_id)
{
	int *param = (int *) consumer_id;
	cout << "Consumer(" << *param << "): "<< endl;
	// sem_wait(ITEM);
	// sem_wait(MUTEX);
	// // removeFromQueue(jobId);
	// sem_signal(MUTEX);
	// sem_signal(SPACE);

  pthread_exit (0);

}
