///////////////////////////////////////////////////////////////////////////////
//	PS2 “ª•¶ŽšD Special Stage
//		Palette decode
//			030909
//				by	AZUCO
///////////////////////////////////////////////////////////////////////////////

#include	<windows.h>
#include	<stdio.h>

void	decode_palette_8bit(unsigned char *src);
void	decode_palette_4bit(unsigned char *src);



void	decode_palette_8bit(unsigned char *src)
{
	unsigned long	z;
	unsigned char	tmp[16];

	for(z=0;z<0x100;z+=32){
		memcpy(tmp,				src+(z+8)*4,	16);
		memcpy(src+(z+8)*4,		src+(z+16)*4,	16);
		memcpy(src+(z+16)*4,	tmp,			16);

		memcpy(tmp,				src+(z+12)*4,	16);
		memcpy(src+(z+12)*4,	src+(z+20)*4,	16);
		memcpy(src+(z+20)*4,	tmp,			16);
	}

//	for(z=0;z<0x400;z+=4){
//		tmp[0  ]=src[z+2];
//		src[z+2]=src[z+0];
//		src[z+0]=tmp[0  ];	}
}



void	decode_palette_4bit(unsigned char *src)
{
	unsigned long	z;
	unsigned char	tmp[16];

	for(z=0;z<0x100;z+=32){
		memcpy(tmp,				src+(z+8)*4,	16);
		memcpy(src+(z+8)*4,		src+(z+16)*4,	16);
		memcpy(src+(z+16)*4,	tmp,			16);

		memcpy(tmp,				src+(z+12)*4,	16);
		memcpy(src+(z+12)*4,	src+(z+20)*4,	16);
		memcpy(src+(z+20)*4,	tmp,			16);
	}

//	for(z=0;z<0x400;z+=4){
//		tmp[0  ]=src[z+2];
//		src[z+2]=src[z+0];
//		src[z+0]=tmp[0  ];	}
}



