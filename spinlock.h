#ifndef LOCKERS_SPINLOCK_H
#define LOCKERS_SPINLOCK_H 

#include "defines.h"

// A spinlock is a type of lock that implements
// busy waiting as a method of wating until the lock
// can be aquired.

// This structure manages a spinlock.
// status = 1 if the spinlock is locked.
// status = 0 if the spinlock is not locked.
typedef struct spinlock{
	int status;
} spinlock;


// Initializes the spinlock.
void init_spinlock(spinlock*lock);

// Try to aquire the spinlock. If the spinlock
// is locked, wait until it gets unlocked.
void lock_spinlock(spinlock*lock);


// Unlock the spinlock. The lock must be
// owned by the current thread. Otherwise
// the behaviour is undefined.
void unlock_spinlock(spinlock*lock);

#endif
