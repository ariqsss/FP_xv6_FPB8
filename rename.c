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

//Code start here

/*
Problem	:

1. s//12/i -> solved
2. s//12/g -> not solved yet
3. s//12/gi -> not solved yet
4. s//12/ -> not solved yet
5. s/a// -> solved
6. s/a//g -> solved
7. s///gi -> solved

*/

     	char temp[512];
	strcpy(temp,fmtname(buf));
	int len=0;
	for (int i=0 ; temp[i]!=' ';++i){++len;}//finding len, cz here , temp will have ' ' till '\0'
	temp[len]='\0';

      	char hold[512]; //buat nyimpen nama file yg udah dirubah
	char identifier[512]; //nyimpen apa kah char ke i sudah di check
	strcpy(identifier,temp);
	int benar=0,a,b;
	int curr_i=0,index_str=0,k;
 	for (int i=0 ; i< strlen(temp); ++i){
		k=0;curr_i=i; curr_i+=1; curr_i-=1; benar=0;
		if (sensitive && target[k]==temp[i]){ //kalau test sensitive (bukan i)
			while(target[k]!='\0' && target[k]==temp[i]){
				++k; ++i;
			}
			if(k==strlen(target)) {++benar;
		  		for(int j=curr_i; j<i;++j){
                                if (strlen(replace)==0){identifier[j]='0';}
				else identifier[j]='-'; //tandai identifier klo sudah divisit buat jaga2 replacementnya lebih pendek dari target
					//biar ga numpuk , misal target akbar , replace noto . biar ga notor, kalau di algo ini yak
                                }

			}
			else i=curr_i; //kalau ndak sesuai , balikin i nya biar bisa lanjut searching lanjutnya
		}
		else if (sensitive!=1){
			a=(int)target[k];
			b=(int)temp[i]; //ascii, ez lah
			while (target[k]!='\0'&& (a-32 == b || a+32 == b || a==b)){
				++k;++i;
				a++; b++;
				a=(int)target[k]; b=(int)temp[i];
			}
			if (k==strlen(target)) {++benar;
				for(int j=curr_i; j<i;++j){
				if (strlen(replace)==0){identifier[j]='0';}
				else identifier[j]='-';
				}
			}
			else i=curr_i;
		}

		if (benar>0){ //klo ketemu brarti masukin replacementnya
			for (int j=0 ;replace[j]!='\0'&& j<strlen(replace) ; ++j){
			 hold[index_str++]=replace[j]; 
			}
			if(strlen(replace)==0)for (int j=0; j<strlen(target) ; ++j) ++i; 
			if (only_1==1){while(temp[i]!='\0'){hold[index_str++]=temp[i++];} break;}
			i=curr_i;
		}
		if(identifier[i]!='-' && identifier[i]!='0')hold[index_str++]=identifier[i]; //kalau bukan ya masukin char sekarang, misal akbar(r) jadi noto(r)

	}//end of for
	hold[index_str]='\0';
	
//	len=(strlen(de.name)>strlen(hold))?strlen(de.name):strlen(hold);
//	memmove(de.name,hold,len);
//	printf(1,"%s -> %s\n",temp,hold);
	if ((strlen(temp)!=0 && strlen(replace)!=0)&&hold[0]=='\0'){
		printf(1,"Can't rename %s : No such file or directory\n",temp);
		printf(1,"Program terminated!\n");
		break;
	}
	if (strlen(replace) ==0 && strlen(target)==0) strcpy(hold,temp);
	if (strcmp(temp,hold)!=0){
	link(temp, hold);
	unlink(temp);
	}
	//printf(1,"%s\%s ->%s\n",path,de.name ,hold);
//	move hold to 


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
printf(1,"%d of (%s)\n",strlen(replace),replace);
}//end of else where argument exactly 2


exit();
}
