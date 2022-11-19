#include "spinlock.h"

void create_spinlock(struct spinlock**l){
	*l= malloc(sizeof(struct spinlock));
	// Set the lock to unlocked.
    (*l)->status=UNLOCKED;	
}


void delete_spinlock(struct spinlock*lock){
	free(lock);
}


// We know that multiple calls of CAS will execute sequencially over
// multiple cores. Therefore, no two threads will change the lock's 
// value at the same time.
// Each iteration of the loop, we try to change the value of the
// lock to 1 meaning "locked". If the value of the lock was 1,
// we must loop again, else the lock is now locked and we exit 
// the loop.
void lock_spinlock(struct spinlock*l){
	while(COMPARE_AND_SWAP(&l->status,UNLOCKED,LOCKED) == LOCKED);
}


// Unlock the spinlock by setting locked to 0. Note that
// we do not check the owner of the lock. There may be
// a thread that unlocks the lock while not owning it.
// This behaviour is undefined.
void unlock_spinlock(struct spinlock*l){
	l->status=UNLOCKED;
}
