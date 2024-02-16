#include	<windows.h>
#include	<stdio.h>

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);
		void	decode_ufa(unsigned char *,char *);
extern	void	tim2_uncompress(unsigned char*,unsigned char*,unsigned long,unsigned long);


void	decode_ufa(unsigned char *borg,char *fname)
{
	unsigned char	*bsrc=borg+0x10;
	unsigned char	*bdst=new unsigned char[*(unsigned long*)(borg+0x08)+0x1000];

	char			fdst[0x100];
	char			ext[3];									//dst filename.ext
	HANDLE			hdst;
	unsigned long	tx;

	tim2_uncompress(bsrc,bdst,*(unsigned long*)(borg+0x04),*(unsigned long*)(borg+0x08));

					ext[0]=bdst[0];
					ext[1]=bdst[1];
					ext[2]=bdst[2];
	if(	(!isalpha(	ext[0]))||
		(!isalpha(	ext[1]))||
		(!isalpha(	ext[2]))	){
					ext[0]='U';
					ext[1]='F';
					ext[2]='E';	}
	sprintf(fdst,"%s.%c%c%c",fname,ext[0],ext[1],ext[2]);
printf("%s\n",fdst);

	hdst=NonOverWriteCreateFile((LPCSTR)fdst);
	WriteFile(hdst,bdst,*(unsigned long*)(borg+0x08),&tx,NULL);
	CloseHandle(hdst);
	delete[]	bdst;
}
