#include "defines.h"

pid_t gettid(){
	return syscall(SYS_gettid);
}

int tgkill(int tid, int sig){
	return syscall(SYS_tgkill, getpid(), tid, sig);
} 

void thread_list_init(thread_list*l){
	l->head=NULL;
	l->tail=NULL;
}

void thread_list_destroy(thread_list*l){
	thread * next;
	while(l->head!=NULL){
		next=l->head->next_thread;
		free(l->head);
		l->head=next;
	}
	l->tail=l->head;
}

void thread_list_push(thread_list*l, thread* t){
	// Check if the list is empty.
	if(l->head == NULL){
		l->head=l->tail = t;
	}
	else{
		l->tail->next_thread = t;	
		l->tail=t;
	}
}

thread* thread_list_pop(thread_list*l){
	thread* to_return= l->head;	
	l->head=l->head->next_thread;
	return to_return;
}

int thread_list_empty(thread_list*l){
	return l->head==NULL;
}
