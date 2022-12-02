#include "defines.h"

#ifndef SPINLOCK_H
#define SPINLOCK_H 


// A spinlock is a type of lock that implements
// busy waiting as a method of wating until the lock
// can be aquired.

// This structure manages a spinlock.
typedef struct spinlock{
	int status;
} spinlock;


// Initializes the spinlock.
void init_spinlock(spinlock*lock);

// Destroys the spinlock.
void destroy_spinlock(spinlock*lock);


// Try to aquire the spinlock. If the spinlock
// is locked, wait until it gets unlocked.
void lock_spinlock(spinlock*lock);


// Unlock the spinlock. The lock must be
// owned by the current thread. Otherwise
// the behaviour is undefined.
void unlock_spinlock(spinlock*lock);

#endif
