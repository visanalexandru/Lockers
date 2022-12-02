#include "semaphore.h"

void init_semaphore(semaphore*s, int value){
	s->value=value;

	// The list of waiting threads.
	thread_list_init(&s->wait_list);

	// initialize the spinlock of the semaphore.
	init_spinlock(&s->lock);
}

// Free the memory used by the semaphore.
void destroy_semaphore(semaphore*s){
	s->value = 0;
	thread_list_destroy(&s->wait_list);
	destroy_spinlock(&s->lock);
}

void wait_semaphore(semaphore*s){
	lock_spinlock(&s->lock);

	// If the value is 0, make the thread go to sleep
	// and add it to the list of waiting threads.
	if(s->value==0){
		thread * this = malloc(sizeof(struct thread));		

		this->thread_id = gettid();
		this->next_thread = NULL;
	
		// Add it to the waiting list.
		thread_list_push(&s->wait_list,this);

		// Initialize the signal set.
		sigset_t block_signals;
		sigemptyset(&block_signals);
		sigaddset(&block_signals, SIGUSR1);

		// Block the signals.
		sigprocmask(SIG_BLOCK, &block_signals, NULL);

		// We block the signal before unlocking the 
		// spinlock to avoid a race condition.
		unlock_spinlock(&s->lock);

		// Go to sleep until we receive SIGUSR1.
		int received;
		sigwait(&block_signals,&received);
	}
	else{
		s->value--;
		unlock_spinlock(&s->lock);
	}
}

void signal_semaphore(semaphore*s){
	lock_spinlock(&s->lock);

	// Chose the next thread that is waiting.
	if(!thread_list_empty(&s->wait_list)){
		thread * next= thread_list_pop(&s->wait_list);
		unlock_spinlock(&s->lock);

		tgkill(next->thread_id,SIGUSR1);
		free(next);
	}
	else{
		s->value++;
		unlock_spinlock(&s->lock);
	}
}
