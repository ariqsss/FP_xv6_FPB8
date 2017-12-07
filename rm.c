#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"


char globalargv1[100];
char str_cpy[100][512];
char str_cpy2[100][512];
int n;
char stbuf[512];
int depth;
char cpy[4]="../";


char *fmtname(char *path)					////
{								////
  static char buf[DIRSIZ+1];					////	Fungsi Fmtname dan ls mengambil dari
  char *p;							////	fungsi ls.c yg sudah ada dari sananya
								////	lalu kita modifikasi untuk fungsi mv*
  // Find first character after last slash.			////
  for(p=path+strlen(path); p >= path && *p != '/'; p--)		////	kami menyediakan rm file
    ;								////	
  p++;								////	rm -rf : directory beserta isinya
								////
  // Return blank-padded name.					////	
  if(strlen(p) >= DIRSIZ)					////
    return p;							////
  memmove(buf, p, strlen(p));					////
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));			////
  return buf;							////
}			





void recursive(char *path){
	printf(1,"Masuk\n");
 	char buf[512], *p;            ///buf dan p untuk mengambil nama2 file dan folder dr fmtname
  	char temp[512];            ///temp disini untuk wadah nama file yg diambil dgn fungsi ls
  	int fd=0;      //fd disini merupakan filedescriptor jika kita meng open sebuah file, lenargv3 merupakan panjang dari argv2 yg sudah diberi "/"
  	struct dirent de;
  	struct stat st;
	char depth_counter[100];
	strcpy(depth_counter,"./");
	int depth_len=strlen(depth_counter);
	for (int i=0; i< depth ; ++i){
		for (int j=0; j<3 ; ++j){
		 depth_counter[depth_len++] = cpy[j];
		}
	}
	char target_str[512];
//	int t_str_len;

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
      	 if(stat(buf, &st) < 0){
         printf(1, "ls: cannot stat %s\n", buf);
         continue;
     	 }

	target_str[0]='\0';
	strcpy(target_str,depth_counter);
//	t_str_len=strlen(target_str);

	printf(1, "%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
 	strcpy(temp,fmtname(buf));////////Proses pengkopian dimulai disini
	int t_len=0;
	for (int i=0; temp[i]!=' '; ++i) ++t_len; temp[t_len]='\0';


	if ((strlen(temp)==1 && temp[0]=='.') || (strlen(temp)==2 && temp[0]=='.' && temp[1]=='.')) continue;
	else{
		if (st.type==1){  //Jika file yg didapat berbentuk direktori maka mkdir di tempat target sesuai di tempat asal
			chdir(path);
			printf(1,"Masuk ke ->  %s\n",fmtname(buf));
			 for (int i=0; temp[i]!=' '; ++i) ++t_len; temp[t_len]='\0';

        		++depth;

			recursive(temp);
			chdir("..");
			--depth;
			printf(1,"Keluar dari dir -> %s\n",fmtname(buf));
  		}
		else {//jika berbentuk file maka langsung di copy di direktori target

			chdir(path);printf(1,"%s\n",path);
			unlink(temp);printf(1,"%s\n",temp);

			chdir("..");
		}
	 }
	} //end while
 close(fd);

}



int
main(int argc, char *argv[])
{
  int i;
  strcpy(globalargv1,argv[1]);

  if(argc < 2){
    printf(2, "Usage: rm files...\n");
    exit();
  }
  if (argc==3){
  for( i=0;i<strlen(argv[1]);i++){
	if( ( (argv[1][i]=='-')&&(argv[1][i+1]=='r')&&(argv[1][i+2]=='f' ) )  ){
	depth=1;
	recursive(argv[2]);

	}
  }
exit();
}



  for(i = 1; i < argc; i++){
    if(unlink(argv[i]) < 0){
      printf(2, "rm: %s failed to delete\n", argv[i]);
      break;
    }
  }

  exit();
}
