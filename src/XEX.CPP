#include	<windows.h>
#include	<stdio.h>
#include	<ctype.h>
#include	"le.h"

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);
		void	decode_xex(unsigned char *,char *,unsigned long);



void	decode_xex(unsigned char *bsrc,char *fname,unsigned long ssrc)
{
	HANDLE			hdst;
	char			fdst[0x100];
	unsigned char	cc;
	unsigned long	cx;

	for(cx=0;cx<ssrc;cx+=2){
		cc=	*(bsrc+cx);
			*(bsrc+cx)=	*(bsrc+cx+1);
						*(bsrc+cx+1)=	cc;
	}

	sprintf(fdst,"%s.xez",fname);
	hdst=NonOverWriteCreateFile((LPCSTR)fdst);
	WriteFile(hdst,bsrc,ssrc,&cx,NULL);

	CloseHandle(hdst);
}
