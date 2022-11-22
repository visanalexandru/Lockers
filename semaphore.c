#include "semaphore.h"

void init_semaphore(semaphore*s, int value){
	s->value=value;
	// The list of threads that are waiting is empty.
	s->thread_list = NULL;
	// initialize the spinlock of the semaphore.
	init_spinlock(&s->lock);
}

void wait_semaphore(semaphore*s){
	lock_spinlock(&s->lock);

	// If there is no room for this thread, make it go to sleep
	// and add it to the list of waiting threads.
	if(s->value==0){
		struct thread * this = malloc(sizeof(struct thread));		
		this->thread_id = gettid();
		// Add it at the beginning of the list.
		this->next_thread = s -> thread_list;
		s->thread_list = this;
		
		// Create the signal set.
		sigset_t set;
		sigemptyset(&set);

		// We use SIGUSR1 for signals.
		sigaddset(&set, SIGUSR1);

		// Block SIGUSR1.
		sigprocmask(SIG_BLOCK, &set, NULL);

		// We block the signal before unlocking the 
		// spinlock to avoid a race condition.
		unlock_spinlock(&s->lock);

		// Go to sleep until we receive SIGUSR1.
		int signal;
		sigwait(&set,&signal);
	}
	else{
		s->value--;
		unlock_spinlock(&s->lock);
	}
}

void signal_semaphore(semaphore*s){
	lock_spinlock(&s->lock);
	// Chose the next thread that is waiting 
	struct thread * waiting = s->thread_list;
	if(waiting!=NULL){
		s->thread_list = waiting->next_thread;
		tgkill(waiting->thread_id,SIGUSR1);
	}
	else{
		s->value++;
	}
	unlock_spinlock(&s->lock);
}
