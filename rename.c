#include "syscall.h"
#include "fcntl.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
char*fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ) return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void
ls(char *path,char *target,char *replace,int sensitive, int only_1,int option)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    return;
  }
  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      char temp[512];
	strcpy(temp,fmtname(buf));
//      printf(1,"%s , with target : %s -> %s\n",temp,target,replace);
      	char hold[512];
	strcpy(hold,temp);
	int benar=0,a,b;
 	for (int i=0 ; i< strlen(temp); ++i){
		int j=i,k=0; benar=0;
		if (sensitive==1){//sensitive already correct
			while (temp[j]!='\0'&&target[k]==temp[j]){
				++k;++j;
				if(target[k]=='\0'){benar++;i=j-1; break;} 
			}
		}
		else if (sensitive!=1){//not tested yet
			a=(int)target[k];
			b=(int)temp[j];
			while (a==b||a-32==b||a+32==b){
			++j;
			if (target[k]=='\0') {benar++; break;}
			a=(int)target[k];
			b=(int)temp[j];
			}
		}

		if (benar!=0){
			if (only_1){//havent find a solution if the target is in the middle of the string
			hold[0]='\0';
			strcpy(hold,replace);
			k=strlen(hold);
				while(j<strlen(temp)){
				hold[k++]=temp[j++];
				}
			 //copy temp nya nanti mulai dari j
			break;
			}
			
		}
	}//end of for
	printf(1,"%s ->%s ->%s\n",fmtname(buf),target,hold);
    }//end of while
    break;
  }
  close(fd);
}




int main(int argc , char *argv[]){

if (argc>2 || argc==1){
 printf(1,"Error : argument not enough!\n");
 exit();
}
else {
 int len=strlen(argv[1]);
 int sensitive=1,only_1=1 , option=0;
 int slash=0;
// printf(1,"%d\n",len);

 int i=1;
 if (argv[1][i++]!='s') {printf(1,"Error : incorrect argument!\n"); exit();}
 if (argv[1][i++]!='/') {printf(1,"Error : incorrect argument!\n"); exit();}
 else ++slash;
 char target[512], replace[512];
 int j=0;

 while (i<len && argv[1][i] !='/'){
  target[j++]=argv[1][i];
  ++i; //copy expr1 to target
 }target[j]='\0';
 j=0;
 if (i==len) {printf(1,"Error : incorrect argument!\n"); exit();} //if doesnt find / means that the command error
 else if (argv[1][i++]=='/') ++slash;

 while (i<len && argv[1][i] !='/'){
 replace[j++]=argv[1][i];
 i++;//copy expr2 to replace
 }replace[j]='\0';
 if (i==len) {printf(1,"Error : incorrect argument!\n"); exit();} //same ^
 else if (argv[1][i++]=='/') ++slash;

 j=len-i;//to know the amount of option
 if (j>3) {printf(1,"Error : incorrect argument!\n"); exit();} // if more than 3, means the argument have /gi*' at the end of the string || * is unknown option with unknown length
 else if (j!=1){ //if 1 means that the argument doesnt have option
	for (int k=1; k<j ; ++k){
		if (argv[1][i]=='i'){--sensitive;++option;}  //if sensitive not 1 means not sensitive, so do only_1
 		else if (argv[1][i]=='g'){--only_1;++option;}
		else if (argv[1][i]=='/'){printf(1,"Error : incorrect argument!\n"); exit();}// command /g/ or /i/ or //i etc, will lead to error
		++i;
 	}//end of loop
 }//end of else if (j!=1)

ls(".",target,replace,sensitive,only_1,option);


/* printf(1,"target : %s -> replace with : %s\n",target,replace);
 if (sensitive!=1){printf(1,"case not sensitive!\n");}
 else printf(1,"case sensitive!\n");

 if (only_1 != 1 ){printf(1,"all will be changed!\n");}
 else printf(1,"only the first one!\n");

 printf(1,"amount of option : %d\n",option);
*/




/*implement struct dirent here*/

} //end of else if the argument exactly 2

exit();
}
