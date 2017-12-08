#include "types.h"
#include "user.h"

int main(int argc, char *argv[]){
//int sleep_sec;
if (argc==2){
	int sleep_sec;
	sleep_sec = atoi(argv[1]);
	sleep(sleep_sec*60);

//printf(1,"%d Succeed\n",sleep_sec);
}
exit();
}
