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

// A list of threads. Used in the implementation of the semaphore.
struct thread{
	int thread_id;
	struct thread*next_thread;
};


// The spinlock status.
#define LOCKED 1 
#define UNLOCKED 0 


#endif
