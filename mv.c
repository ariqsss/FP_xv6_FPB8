#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"


char extension[5];
char temp3[20][20];
char globalargv2[100];
char *fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}



void ls(char *path)
{
  char lsargv2[100];
 strcpy(lsargv2,globalargv2);
  char buf[512], *p;
  char temp[50];
 // char lstemp[50];
  int fd=0,fd2=0,j=0,i=0;
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






strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
     // printf(1, "%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
//  temp[1]=fmtname(buf);
  strcpy(temp,fmtname(buf));
	int templen=strlen(temp);
	char lstemp[templen+1]; 
 //strcpy(lstemp,temp);
   strcpy(lsargv2,globalargv2);
  //printf(2,"%c\n",temp[1][2]);

 int size = strlen(temp) + 1; //  If you don't know the source size.
 int size2 =strlen(extension); 
  for(i=0;i<size;i++){
	while(temp[i]==extension[j]&&j<size2){
			i++;j++;
			if(j==size2){
				if ( (fd2=open(lsargv2 , 0)) > 0 ){
		 					fstat(fd2,&st);
							strcpy(lstemp,temp);
							if(st.type == T_DIR){
							char dirku[1]="/";
					        	 strcpy(lsargv2,globalargv2);
							int lenargv2=strlen(lsargv2);
							int lenlstemp=strlen(lstemp);
        						memmove(lsargv2+lenargv2,dirku,sizeof(dirku));
							lenargv2=strlen(lsargv2);
							memmove(lsargv2+lenargv2,lstemp,lenlstemp);				
							 printf(1,"argv1 = %s lsargv2 = %s globalargv2 = %s\n",lstemp , lsargv2, globalargv2);
//      							  link(temp,lsargv2);
//						       	 unlink(temp);
							close(fd2);						
									     }	

								}
			           }	
				
			  }
	}
    i=0;j=0;
    }
    
  close(fd);
}





int main (int argc, char *argv[]){
  char wadahargv1[30];
  char wadahargv2[50];
  strcpy(wadahargv1,argv[1]);
  strcpy(wadahargv2,argv[2]);
  strcpy(globalargv2,argv[2]);
  int fd,len=strlen(argv[1]),i=0,j=0;
  int len2=len;
  strcpy(temp3[1],argv[2]);
  struct stat st;
 char namafile[20][len2];
 char namafile2[20][len];

  if (argc != 3){
    printf(2, "Usage: mv oldname newname\n");
    exit();
  }
  for(i=0;i<len;i++){
	if(argv[1][i]=='*'){
        i++;
        for(i=i;i<len;i++){
	extension[j]=argv[1][i];
	j++;
	}
	ls(".");
//	printf(2,"%s",extension);
	exit();}


  }
  if ( (fd=open(argv[2] , 0)) > 0 ){
 fstat(fd,&st);
//printf(1,"%s\n",argv[1]);
if(st.type == T_DIR){
//	printf(1,"%s\n",argv[1]);
 	len=strlen(argv[1]);
	i=0;
	while(argv[1][len2-1]!='/'){
	namafile[1][i]=argv[1][len2-1];
	len2--;i++;




	}  
	len2=strlen(namafile[1]);
	j=len2;
	for(i=0;i<len2;i++){
	namafile2[1][i]=namafile[1][j-1];
	j--;

	}

	//	printf(1,"%s %s",argv[1],namafile2[1]);
	char dirku[1]="/";
	int lenargv2=strlen(wadahargv2);
	memmove(wadahargv2+lenargv2,dirku,sizeof(dirku));
//	printf(1,"%s %s",argv[2],namafile2[1]);
	lenargv2=strlen(wadahargv2);
//	printf(1,"%s\n",argv[1]);

  	memmove(wadahargv2+lenargv2,namafile2[1],sizeof(namafile2[1]));					
//	printf(1,"%s",argv[2]);
//	printf(1,"%s\n",wadahargv1);
	//printf(1,"%s",namafile[1]);
	printf(1,"argv1 = %s argv2 = %s",wadahargv1 , wadahargv2);
	link(wadahargv1,wadahargv2);
	unlink(wadahargv1);

		}

else {
	
	link(wadahargv1,argv[2]);
	unlink(wadahargv1);		


//	 printf(1,"bkn dir");
	

	 }
close(fd);
exit();
}

if ((link(argv[1], argv[2]) < 0) || (unlink(argv[1]) < 0)){

    printf(2, "mv %s to %s failed\n", argv[1], argv[2]);
	exit();
}
  exit();
}
