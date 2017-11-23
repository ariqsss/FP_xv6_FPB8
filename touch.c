#include "types.h"
#include "fcntl.h"
#include "user.h"
#include "stat.h"
int main(int argc , char *argv[]){
if (argc>1){
 int opener;
 for (int i=1; i<argc ; ++i){
	if(( opener=open(argv[i],O_CREATE|O_RDWR))<0)exit();
	}
close(opener);
exit();
}
else {
printf(1,"No argument found!\n");
exit();
}
//close(opener);
exit();
}
