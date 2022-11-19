#ifndef LOCKERS_SPINLOCK_H
#define LOCKERS_SPINLOCK_H 

#include "defines.h"

// A spinlock is a type of mutex lock that implements
// busy waiting as a method of wating until the lock
// can be aquired.

// This structure manages a spinlock.
// status = 1 if the spinlock is locked.
// status = 0 if the spinlock is not locked.
struct spinlock{
	int status;
};


// Allocates memory for the new spinlock.
void create_spinlock(struct spinlock**lock);

// Frees the memory used by the spinlock.
void delete_spinlock(struct spinlock*lock);

// Try to aquire the spinlock. If the spinlock
// is locked, wait until it gets unlocked.
void lock_spinlock(struct spinlock*lock);


// Unlock the spinlock. The lock must be
// owned by the current thread. Otherwise
// the behaviour is undefined.
void unlock_spinlock(struct spinlock*lock);

#endif
