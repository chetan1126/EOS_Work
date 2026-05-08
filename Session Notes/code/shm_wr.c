//#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
//using namespace std;

int main()
{
int cnt=0;
// ftok to generate unique key
key_t key = ftok("shmfile",65);

// shmget returns an identifier in shmid
int shmid = shmget(key,1024,0666|IPC_CREAT);

// shmat to attach to shared memory
char *str = (char*) shmat(shmid,(void*)0,0);

//printf("\nWrite Data :");
//cout<<"Write Data : ";


while(1){
       sprintf(str,"%03d\n",cnt);
	printf("Data written in memory: %d\n",cnt);
	cnt++;
	sleep(2);
}
//detach from shared memory 
shmdt(str);

return 0;
}

