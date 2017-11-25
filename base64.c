#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main(int argc, char *argv[]){
	printf("%s\n", b64_encode(argv[1],strlen(argv[1])));
	return 0;
}

char *b64_encode(const char *source, int len){
	char temp[3];
	int s_enc=(int)(len+2)/3;
	s_enc++;
	char *encode=malloc(s_enc*sizeof(char));
	int i=0,j=0,x=0;

	while(len--){
		temp[i++]=*(source++);

		if(i==3){
			encode[x++]	=b64_table[(temp[0] & 0xfc /*11111100*/) >> 2];
			encode[x++]	=b64_table[((temp[0] & 0x03 /*00000011*/) << 4)
			+
			((temp[1] & 0xf0 /*11110000*/) >> 4)];
			encode[x++]	=b64_table[((temp[1] & 0x0f /*00001111*/) << 2)
			+
			((temp[2] & 0xc0 /*11000000*/) >> 6)];
			encode[x++]	=b64_table[(temp[2] & 0x3f /*00111111*/)];

			i=0;
		}
	}

	if(i>0){
		for(j=i;j<3;j++)
			temp[j]='\0';

		encode[x++]	=b64_table[(temp[0] & 0xfc /*11111100*/) >> 2];
		encode[x++]	=b64_table[((temp[0] & 0x03 /*00000011*/) << 4)
		+
		((temp[1] & 0xf0 /*11110000*/) >> 4)];
		encode[x++]	=b64_table[((temp[1] & 0x0f /*00001111*/) << 2)
		+
		((temp[2] & 0xc0 /*11000000*/) >> 6)];
		encode[x++]	=b64_table[(temp[2] & 0x3f /*00111111*/)];
	}

	x-=3-i;
	while(i++<3){
		encode[x++]='=';
	}

	encode[x]='\0';

	return encode;
}