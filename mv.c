#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"


char extension[5];						///////////////////////////////////////////////////	
char temp3[20][20];						////
char globalargv2[100];						////
int globalkhusus;						////
char *fmtname(char *path)					////
{								////
  static char buf[DIRSIZ+1];					////	Fungsi Fmtname dan ls mengambil dari
  char *p;							////	fungsi ls.c yg sudah ada dari sananya
								////	lalu kita modifikasi untuk fungsi mv*
  // Find first character after last slash.			////
  for(p=path+strlen(path); p >= path && *p != '/'; p--)		////	kami menyediakan mv file ke file (renaming)
    ;								////	file ke directory ( memindahkan )
  p++;								////	mv * = memindahkan dengan wildcard
								////
  // Return blank-padded name.					////
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
  char lsargv2[512];// lsargv2 sebagai wadah dari argv2 untuk dimodif (argv2 disini merupakan directory) cth mv *.txt /ariqdir
 strcpy(lsargv2,globalargv2);//ambil lsargv2 dari globalargv2 yaitu variabel global utk argv2 yg tidak berubah2
  char buf[512], *p;		///buf dan p untuk mengambil nama2 file dan folder dr fmtname
  char temp[512];		///temp disini untuk wadah nama file yg diambil dgn fungsi ls
  int fd=0,fd2=0,j=0,i=0,lenargv3=0;	//fd disini merupakan filedescriptor jika kita meng open sebuah file, lenargv3 merupakan panjang dari argv2 yg sudah diberi "/"
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
	int lenargv2=strlen(lsargv2);  ///lenargv2 = panjang lsargv2
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
							char dirku[1]="/"; ////tambah kan argv2 dengan / misalnya /ariqdir -> /ariqdir/
							lenargv2=strlen(lsargv2);
        						memmove(lsargv2+lenargv2,dirku,sizeof(dirku));
							lenargv2=strlen(lsargv2);
							if(globalkhusus!=1){lenargv3=lenargv2;globalkhusus=1;} //lalu panjang dari /ariqdir/ kita simpan ke lenargv3, utk 1 kali saja jika tidak begini nanti error
							memmove(lsargv2+lenargv3,temp,size);/// pindahkan nama file ke lsargv2 /ariqdir/ -> /ariqdir/namafile.txt
							 printf(1,"argv1 = %s lsargv2 = %s globalargv2 = %s\n",temp , lsargv2, globalargv2); //pengecekan apakah yg dikirim benar
      							 link(temp,lsargv2);///proses pemindahan
						       	 unlink(temp);
							close(fd2);						
									     }	

								}
			           }	
				
			  }
	}
    i=0;j=0;lenargv2=0;
    }
    
  close(fd);
}





int main (int argc, char *argv[]){
  char wadahargv1[30];////wadah utk argv1
  char wadahargv2[50];////wadah utk argv2
  strcpy(wadahargv1,argv[1]);
  strcpy(wadahargv2,argv[2]);
  strcpy(globalargv2,argv[2]);////memindahkan argv2 ke global agar bs digunakan fungsi lain
  int fd,len=strlen(argv[1]),i=0,j=0;
  int len2=len;
  strcpy(temp3[1],argv[2]);
  struct stat st;
 char namafile[20][len2]; ///ambil namafile saja, in case /home/ariq/documents/hehe/wkwk/file.txt maka kita ambil file.txt saja
 char namafile2[20][len];

  if (argc != 3){
    printf(2, "Usage: mv oldname newname\n");
    exit();
  }
  for(i=0;i<len;i++){
	if(argv[1][i]=='*'){  ///incase ada wildcard (*) maka passsing ke fungsi ls, dan ambil ekstensinya dulu
        i++;
        for(i=i;i<len;i++){
	extension[j]=argv[1][i];
	j++;
	}
	ls(".");
	exit();}


  }
  if ( (fd=open(argv[2] , 0)) > 0 ){ //cek apakah argv2 ada
 fstat(fd,&st);
if(st.type == T_DIR){////jika argv 2 directory berarti file -> directory moving
//	printf(1,"%s\n",argv[1]);
 	len=strlen(argv[1]);
	i=0;
	while(argv[1][len2-1]!='/'){  //// proses pengambilan nama file
	namafile[1][i]=argv[1][len2-1];
	len2--;i++;




	}  
	len2=strlen(namafile[1]);
	j=len2;
	for(i=0;i<len2;i++){
	namafile2[1][i]=namafile[1][j-1];
	j--;				////nama file sudah didapat

	}


	char dirku[1]="/";
	int lenargv2=strlen(wadahargv2);
	memmove(wadahargv2+lenargv2,dirku,sizeof(dirku)); /////nama directory menjadi directory/
	lenargv2=strlen(wadahargv2);

  	memmove(wadahargv2+lenargv2,namafile2[1],sizeof(namafile2[1]));//// menjadi directory/namafile
	printf(1,"argv1 = %s argv2 = %s",wadahargv1 , wadahargv2);
	link(wadahargv1,wadahargv2);  ////proses pmindahan
	unlink(wadahargv1);

		}

else {
	
	link(wadahargv1,argv[2]); ///jika bukan directory tetapi ada file nya, karna telah diopen maka tetap rename
	unlink(wadahargv1);		

	

	 }
close(fd);
exit();
}

if ((link(argv[1], argv[2]) < 0) || (unlink(argv[1]) < 0)){ ///in case rename diatas gagal masuk kesini tetap di rename

    printf(2, "mv %s to %s failed\n", argv[1], argv[2]);
	exit();
}
  exit();
}
