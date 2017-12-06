#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

char extension[5];						///////////////////////////////////////////////////	
char temp3[20][20];						////
char globalargv2[100];
char globalargv1[100];
char globalargv3[100];						////
int globalkhusus;						////
char *fmtname(char *path)					////
{								////
  static char buf[DIRSIZ+1];					////	Fungsi Fmtname dan ls mengambil dari
  char *p;							////	fungsi ls.c yg sudah ada dari sananya
								////	lalu kita modifikasi untuk fungsi mv*
  // Find first character after last slash.			////
  for(p=path+strlen(path); p >= path && *p != '/'; p--)		////	kami menyediakan cp file ke file (copy dengan nama lain)
    ;								////	file ke directory 
  p++;								////	cp * = mengcopy  dengan wildcard
								////
  // Return blank-padded name.					////	cp -R = belum ada
  if(strlen(p) >= DIRSIZ)					////
    return p;							////
  memmove(buf, p, strlen(p));					////
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));			////
  return buf;							////
}								////
								////
								////
								////
void ls(char *path)						/////////////////////////////////////////////////////
{
  char lsargv2[512];// lsargv2 sebagai wadah dari argv2 untuk dimodif (argv2 disini merupakan directory) cth cp *.txt /ariqdir
  strcpy(lsargv2,globalargv2);//ambil lsargv2 dari globalargv2 yaitu variabel global utk argv2 yg tidak berubah2
  char buf[512], *p;		///buf dan p untuk mengambil nama2 file dan folder dr fmtname
  char temp[512],stbuf[512];		///temp disini untuk wadah nama file yg diambil dgn fungsi ls
  int n,fd=0,fd0=0,fd1=0,fd2=0,j=0,i=0;//,lenargv3=0;	//fd disini merupakan filedescriptor jika kita meng open sebuah file, lenargv3 merupakan panjang dari argv2 yg sudah diberi "/"
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
    	while(read(fd, &de, sizeof(de)) == sizeof(de)){  //ambil tiap2 file dan folder seperti LS
	if(de.inum == 0)
        continue;
  	memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
  	strcpy(temp,fmtname(buf));   ////copy nama file / folder ke temp
	int nullku=0,k=0;
	for (k=0 ; temp[k]!=' ';++k){++nullku;}//finding len, cz here , temp will have ' ' till '\0'
	temp[nullku]='\0';
	k=0;



   	strcpy(lsargv2,globalargv2); ///copy global argv2 ke lsargv2

 	int size = strlen(temp); 
 	int size2 =strlen(extension); 
  		for(i=0;i<size;i++){    //////////For disini untuk mengecek apakah ekstensi nya sesuai dengan yang dikirim misal *.txt
			while(temp[i]==extension[j]&&j<size2){
			i++;j++;
				if(j==size2){
					if ( (fd2=open(lsargv2 , 0)) > 0 ){  ////jika sama dan ketemu kita open directory di argv2
		 					fstat(fd2,&st);
							if(st.type == T_DIR){ ///jika benar directory
      							fd0=open(temp,O_RDONLY);
							chdir(globalargv2);
						        fd1=open(temp, O_CREATE|O_RDWR);
      							  while ( (n= read(fd0,stbuf,sizeof(stbuf)))  >0 ){

						        	write(fd1,stbuf,n);
       							 	};
        						close(fd0);
       							close(fd1);
							close(fd2);				
							chdir(path);		
							}	

						}
			           	}	
				  }
		}
    i=0;j=0;
    }

  close(fd);
}


void recursive(char path[],char target[]){

	printf(1,"Masuk rekursi0\n");
 	char stbuf[512],buf[512], *p;            ///buf dan p untuk mengambil nama2 file dan folder dr fmtname
  	char temp[512];//0,stbuf[512];            ///temp disini untuk wadah nama file yg diambil dgn fungsi ls
  	int fd=0,fd0=0,fd1=0,n=0;      //fd disini merupakan filedescriptor jika kita meng open sebuah file, lenargv3 merupakan panjang dari argv2 yg sudah diberi "/"
  	struct dirent de;
  	struct stat st;

	char current_target[512];
	strcpy(current_target,target);
	int ctlen=strlen(current_target);
	
	int slashcount=0;
	printf(1,"path adalah %s \n",path);
	for(int i=0;i<strlen(path);i++){
		if(path[i]=='/')slashcount++;
		printf(1,"%d\n",slashcount);
		}



	printf(1,"Masuk rekursi1\n");
        if((fd = open(path, 0)) < 0){
        printf(2, "ls: cannot open %s\n", path);
        return;
        }

        if(fstat(fd, &st) < 0){
        printf(2, "ls: cannot stat %s\n", path);
        close(fd);
        return;
        }


	printf(1,"masuk recursi2\n");
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
     	 printf(1, "%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
 	strcpy(temp,fmtname(buf));
	int t_len=0;
	for (int i=0; temp[i]!=' '; ++i) ++t_len; temp[t_len]='\0';
	if ((strlen(temp)==1 && temp[0]=='.') || (strlen(temp)==2 && temp[0]=='.' && temp[1]=='.')) continue;
	else{
		if (st.type==1){
			chdir(path);
			printf(1,"Masuk ke ->  %s\n",fmtname(buf));
			strcpy(temp,fmtname(buf));
		 	t_len=0;
			for (int i=0; temp[i]!=' ';++i) ++t_len;
			temp[t_len]='\0';
		//	chdir(target);printf(1,"berhasil chdir target\n");
			current_target[ctlen++]='/';
			for(int i=0;i<strlen(path);++i){current_target[ctlen++]=temp[i];}
			current_target[ctlen++]='\0';
			printf(1,"%s",current_target);
 		//	mkdir("/dira/dir2");printf(1,"berhasil mkdir dlm target\n");
			for(int i=0;i<slashcount;i++)chdir("..");
			mkdir(current_target);
			recursive(temp,current_target);
			chdir("..");
			printf(1,"Keluar dari dir -> %s\n",fmtname(buf));
  		}
		else{	printf(1,"masuk file\n");
			fd0=open(temp,O_RDONLY);
                        chdir(target);

			fd1=open(temp, O_CREATE|O_RDWR);
                        while ( (n= read(fd0,stbuf,sizeof(stbuf)))  >0 ){

                        write(fd1,stbuf,n);
                        };
                        close(fd1);
			chdir("..");
			close(fd0);
                                                       






		}
	} 
	} //end while
 close(fd);

}
int main (int argc, char *argv[]){
  char wadahargv1[70]; //wadah untuk argv1
  char wadahargv2[50];//wadah untuk argv2
  	strcpy(wadahargv1,argv[1]);
  	strcpy(wadahargv2,argv[2]);
 	strcpy(globalargv2,argv[2]);//global argv2 yaitu argv2 untuk dipass ke fungsi ls
  	strcpy(globalargv3,argv[3]);
//	strcpy(globalargv1,argv[1]);
  int n,fd1=0,fd0=0,fd,len=strlen(argv[1]),i=0,j=0;
  int len2=len;
 	 strcpy(temp3[1],argv[2]);
  struct stat st;
  char namafile[20][len2];
  char namafile2[20][len];
  char buf[512];
  if (argc < 3||argc > 4){ //jika arg bkn 3
    printf(2, "Usage: mv oldname newname\n");
    exit();
  }
  for(i=0;i<len;i++){ //mengecek apakah ada wildcard (*)
	if(argv[1][i]!='*') { globalargv1[i]=argv[1][i]; }
	if(argv[1][i]=='*'){
	globalargv1[i-1]='\0';
        i++;
        for(i=i;i<len;i++){
	extension[j]=argv[1][i];
	j++;
	}
	ls(globalargv1);
	exit();}


  }
  for(i=0;i<len;i++){
	if( ( (argv[1][i]=='-')&&(argv[1][i+1]=='R') ) ){
	
		
	

	recursive(globalargv2,globalargv3);
	exit();










	}




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
