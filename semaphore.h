#include"spinlock.h"
#include"defines.h"

#ifndef SEMAPHORE_H
#define SEMAPHORE_H


// A semaphore is a type of lock that only allowes a predefined
// maximum number of threads to aquire the lock.

// This structure manages a semaphore.
// value - the remaining count of threads that can aquire the lock.
// thread_list - the list of threads that are waiting to aquire the lock.
// lock - a spinlock used to make wait() and signal() atomic.
typedef struct semaphore{
	int value;
	struct thread* thread_list;
	spinlock lock;
} semaphore;


// When there is no more space in the semaphore, threads that 
// call wait() are added into the list of waiting threads.
// When a call to signal() occurs, waiting threads are chosen
// for execution in the FIFO (first-in-first out) order.


// Initializes the semaphore with the given capacity.
void init_semaphore(semaphore*s, int value);

// Waits until the thread can aquire the semapore.
void wait_semaphore(semaphore*s);

// Signals that the thread has exited the semaphore.
void signal_semaphore(semaphore*s);

#endif
