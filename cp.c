#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

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
  char wadahargv1[30]; //wadah untuk argv1
  char wadahargv2[50];//wadah untuk argv2
  strcpy(wadahargv1,argv[1]);
  strcpy(wadahargv2,argv[2]);
  strcpy(globalargv2,argv[2]);//global argv2 yaitu argv2 untuk dipass ke fungsi ls
  int n,fd1=0,fd0=0,fd,len=strlen(argv[1]),i=0,j=0;
  int len2=len;
  strcpy(temp3[1],argv[2]);
  struct stat st;
 char namafile[20][len2];
 char namafile2[20][len];
 char buf[512];
  if (argc != 3){ //jika arg bkn 3
    printf(2, "Usage: mv oldname newname\n");
    exit();
  }
  for(i=0;i<len;i++){ //mengecek apakah ada wildcard (*)
	if(argv[1][i]=='*'){
        i++;
        for(i=i;i<len;i++){
	extension[j]=argv[1][i];
	j++;
	}
	ls(".");
	exit();}


  }
  if ( (fd=open(argv[2] , 0)) > 0 ){ //membuka argv2 incase directory
 fstat(fd,&st);
if(st.type == T_DIR){  // incase directory
 	len=strlen(argv[1]);
	i=0;
	while(argv[1][len2-1]!='/'){   //// ambil nama file
	namafile[1][i]=argv[1][len2-1];
	len2--;i++;




	}  
	len2=strlen(namafile[1]);
	j=len2;
	for(i=0;i<len2;i++){
	namafile2[1][i]=namafile[1][j-1]; /// ambil nama file
	j--;

	}

	char dirku[1]="/";
	int lenargv2=strlen(wadahargv2);
	memmove(wadahargv2+lenargv2,dirku,sizeof(dirku)); //rubah directory tambah kan karakter "/" menjadi directory/
	lenargv2=strlen(wadahargv2);

  	memmove(wadahargv2+lenargv2,namafile2[1],sizeof(namafile2[1]));//rubah directory/ menjadi directory/namafile
 	printf(1,"argv1 = %s argv2 = %s",wadahargv1 , wadahargv2);
	//proses pengkopian
	fd0=open(wadahargv1,O_RDONLY);
  	fd1=open(wadahargv2, O_CREATE|O_RDWR);
        while ( (n= read(fd0,buf,sizeof(buf)))  >0 ){

	write(fd1,buf,n);
	};
	 close(fd0);
	close(fd1);
		}

else {
	
	fd0=open(wadahargv1,O_RDONLY);
        fd1=open(wadahargv2, O_CREATE|O_RDWR);
        while ( (n= read(fd0,buf,sizeof(buf)))>0 ){

        write(fd1,buf,n);
        }
	close(fd0);
        close(fd1);
//	 printf(1,"bkn dir");
	

	 }
close(fd);
exit();
}

if (  (fd0 = open(wadahargv1, O_RDONLY )) <0  ){

printf(1,"argv1 salah file tidak ada");
}


if(   (fd1=open(wadahargv2, O_CREATE|O_RDWR)) <  0 ){
printf(1,"argv2 tdk bisa dibuka file sudah ada mungkin");
}



printf(1,"argv1 = %s argv2 = %s",wadahargv1,wadahargv2);
    while ( (n= read(fd0,buf,sizeof(buf)))>0 ){

        write(fd1,buf,n);
        }
        close(fd0);
        close(fd1);

  exit();
}
