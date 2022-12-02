#include<stdlib.h> // for malloc()
#include<sys/syscall.h> // for SYS_gettid
#include<unistd.h> // for syscall()
#include<signal.h> // for sigwait()
#include<stdio.h>

#ifndef DEFINES_H
#define DEFINES_H

// This file holds various definitions.

// Gcc's compare and swap builtin function.
#define COMPARE_AND_SWAP(ptr,old,new) __sync_val_compare_and_swap(ptr,old,new)

// There is no glibc wrapper function for the gettid() syscall.
pid_t gettid();

// There is no glibc wrapper function for the tgkill() syscall.
int tgkill(int tid, int sig);

// A node in the list of threads. 
typedef struct thread{
	int thread_id;
	struct thread*next_thread;
} thread;

// A list of threads.
typedef struct thread_list{
	thread * head;
	thread * tail;
} thread_list;

// Initializes an empty list of threads.
void thread_list_init(thread_list*l);

// Frees the memory used by the list.
void thread_list_destroy(thread_list*l);

// Add a new thread to a list.
void thread_list_push(thread_list*l, thread* t);

// Returns the first thread in the list and removes it.
// This function does not check if the list is empty.
thread* thread_list_pop(thread_list*l);

// Returns 1 if the list is empty, otherwise 0.
int thread_list_empty(thread_list*l);

// The spinlock status.
#define LOCKED 1 
#define UNLOCKED 0 


#endif
