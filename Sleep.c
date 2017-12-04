#include "types.h"
#include "user.h"
#include "date.h"


//Credit to github.com//kongming92/6828-xv6 for the date template :)
							//template sysproc syscall.h etc
//edited by akbar

int main(int argc, char *argv[]){
struct rtcdate r;

if(Sleep(&r)){
 printf(2,"date failed\n");
 exit();
}
printf(1,"called at %d:%d:%d\n",r.hour,r.minute,r.second);
if (argc==2){
struct rtcdate now;

int decrement=0;
char b=argv[1][strlen(argv[1])-1];

if (b=='s') ++decrement;
else if (b=='m') ++decrement;
else if (b=='h') ++decrement;
else if (b=='d') ++decrement;

//printf(1,"%c\n",b);

	long long coba=0;
	for (int i=0; i < strlen(argv[1])-decrement ; ++i){
//	  printf(1,"%c\n",argv[1][i]);
	  int timer=10;
	  if (argv[1][i]=='1'){ coba+=1;}
	  else if (argv[1][i]=='2') {coba+=2;}
	  else if (argv[1][i]=='3') {coba+=3;}
	  else if (argv[1][i]=='4') {coba+=4;}
	  else if (argv[1][i]=='5') {coba+=5;}
	  else if (argv[1][i]=='6') {coba+=6;}
	  else if (argv[1][i]=='7') {coba+=7;}
	  else if (argv[1][i]=='8') {coba+=8;}
	  else if (argv[1][i]=='9') {coba+=9;}
	  else  coba+=0;

	  if (i+1 < strlen(argv[1])-decrement) coba*=timer;
	}

if (decrement!=0){
 if (b=='m') coba=coba*60; //convert minute to second
 else if (b=='h') coba=coba*3600; //convert hour to second
 else if (b=='d') coba=coba*3600*24; //convert day to second
}

//printf(1,"%d",coba);
long long temp_time=0;
temp_time+=r.second;
int has_been_gone_x_second=0;
if (Sleep(&now)){ printf(2,"date failed\n"); exit();}

while (has_been_gone_x_second != coba){
	if (now.second!=temp_time){ //when the second is changing
	has_been_gone_x_second++; //increment clock
	temp_time=now.second; //change the temp to now to check the 'next' now
	}
 if (Sleep(&now)){
  exit();
 }
}
printf(1,"printed at %d:%d:%d\n",now.hour,now.minute,now.second);

}
//printf(1,"%d-%d-%d %d:%d:%d\n",r.year, r.month, r.day ,r.hour, r.minute, r.second);
exit();
}
