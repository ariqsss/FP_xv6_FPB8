#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

static const char b64_table[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
  'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
  'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
  'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
  'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
  'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
  '8', '9', '+', '/'
};

char *b64_encode(const char *, int );
char *b64_decode(const char *, int );

int main(int argc, char *argv[]){
	int i=1;
	char cwd[1024];
	getcwd(cwd,sizeof(cwd));
	if(argc==2){
		printf("%s\n", b64_encode(argv[i],strlen(argv[i])));
	}
	else
	if(!strcmp(argv[i],"-d")){
		i++;
		if(i<argc){
			if(!strcmp(argv[i],"-f")){
				i++;
				if(i<argc){
					sprintf(cwd,"%s/%s",cwd,argv[i]);

					FILE *in=fopen(argv[i],"r");
					char input[1000];
					fgets(input,1000,in);
					fclose(in);

					printf("%s\n",b64_decode(input,strlen(input)));
				}
				else{
					printf("Failed, no argument for open FILE\n");
					return 0;
				}
			}
			else{
				printf("%s\n",b64_decode(argv[i],strlen(argv[i])));
			}
		}
		else{
			printf("Failed, no argument for decode\n");
			return 0;
		}
	}
	else
	if(!strcmp(argv[i],"-f")){
		i++;
		if(i<argc){
			char input[1000],temp[100];
			sprintf(cwd,"%s/%s",cwd,argv[i]);
			int k=0;

			FILE *in=fopen(argv[i],"r");
			fgets(temp,100,in);
			sprintf(input,"%s",temp);
			while(fgets(temp,100,in)!=NULL){
				sprintf(input,"%s\n%s",input,temp);
			}
			fclose(in);
			printf("%s\n",input );

			printf("%s\n", b64_encode(input,strlen(input)));
		}
	}
	else{
		printf("Failed...\n");
		return 0;
	}
	return 0;
}

char *b64_decode(const char *source, int len){
	char tmp[4];
	int s_dec=(int)(len+3)/4;
	s_dec*=3;
	s_dec++;
	char *decode=malloc(s_dec*sizeof(char));
	int i=0,j=0,x=0;
	int a,b;

	while(len--){
		if(*source=='=') break;
		if(!(isalnum(*source) || *source=='+' || *source=='/')) break;

		tmp[i++]=*(source++);
		
		if(i==4){
			for(a=0;a<4;a++){
				for(b=0;b<64;b++){
					if(tmp[a]==b64_table[b]){
						tmp[a]=b;
						break;
					}
				}
			}

			decode[x++]	=
				(tmp[0] << 2)
				+
				((tmp[1] & 0x30 /*00110000*/) >> 4);
			decode[x++]	=
				((tmp[1] & 0x0f /*00001111*/) << 4)
				+
				((tmp[2] & 0x3c /*00111100*/) >> 2);
			decode[x++]	=
				((tmp[2] & 0x03 /*00000011*/) << 6)
				+
				(tmp[3]);

			i=0;
		}

	}
	if(i>0){
		for(j=i;j<4;j++)
			tmp[j]='\0';

		for(a=0;a<4;a++)
			for(b=0;b<64;b++)
				if(tmp[a]==b64_table[b]){
					tmp[a]=b;
					break;
				}

		decode[x++]	=
			(tmp[0] << 2)
			+
			((tmp[1] & 0x30 /*00110000*/) >> 4);
		decode[x++]	=
			((tmp[1] & 0x0f /*00001111*/) << 4)
			+
			((tmp[2] & 0x3c /*00111100*/) >> 2);
		decode[x++]	=
			((tmp[2] & 0x03 /*00000011*/) << 6)
			+
			(tmp[3]);
	}
	decode[x]='\0';
	return decode;
}

char *b64_encode(const char *source, int len){
	char temp[3];
	int s_enc=(int)(len+2)/3;
	s_enc*=4;
	s_enc++;
	char *encode=malloc(s_enc*sizeof(char));
	int i=0,j=0,x=0;

	while(len--){
		temp[i++]=*(source++);

		if(i==3){
		encode[x++]	=b64_table[
			(temp[0] & 0xfc /*11111100*/) >> 2
			];
		encode[x++]	=b64_table[
			((temp[0] & 0x03 /*00000011*/) << 4)
			+
			((temp[1] & 0xf0 /*11110000*/) >> 4)
			];
		encode[x++]	=b64_table[
			((temp[1] & 0x0f /*00001111*/) << 2)
			+
			((temp[2] & 0xc0 /*11000000*/) >> 6)
			];
		encode[x++]	=b64_table[
			(temp[2] & 0x3f /*00111111*/)
			];

			i=0;
		}
	}

	if(i>0){
		for(j=i;j<3;j++)
			temp[j]='\0';

		encode[x++]	=b64_table[
			(temp[0] & 0xfc /*11111100*/) >> 2
			];
		encode[x++]	=b64_table[
			((temp[0] & 0x03 /*00000011*/) << 4)
			+
			((temp[1] & 0xf0 /*11110000*/) >> 4)
			];
		encode[x++]	=b64_table[
			((temp[1] & 0x0f /*00001111*/) << 2)
			+
			((temp[2] & 0xc0 /*11000000*/) >> 6)
			];
		encode[x++]	=b64_table[
			(temp[2] & 0x3f /*00111111*/)
			];
	
		x-=3-i;
		while(i++<3){
			encode[x++]='=';
		}
	}


	encode[x]='\0';

	return encode;
}