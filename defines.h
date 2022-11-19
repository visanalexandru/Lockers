#ifndef DEFINES_H
#define DEFINES_H

#include<stdlib.h>
// This file holds various definitions.

// Gcc's compare and swap builtin function.
#define COMPARE_AND_SWAP(ptr,old,new) __sync_val_compare_and_swap(ptr,old,new)

#define LOCKED 1 
#define UNLOCKED 0 


#endif
