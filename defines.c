#include "defines.h"

pid_t gettid(){
	return syscall(SYS_gettid);
}

int tgkill(int tid, int sig){
	return syscall(SYS_tgkill, getpid(), tid, sig);
} 
