#include	<windows.h>
#include	<stdio.h>
#include	<ctype.h>
#include	"le.h"

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);
extern	void	decode_ps2_d8t(unsigned char*,unsigned long,unsigned long);
extern	void	decode_palette_8bit(unsigned char *);
		void	decode_aic(unsigned char *,char *);



/*****メモ*****AIC フォーマット************************************************
AICヘッダ部 
+00 magic 'AIC'
+04 ATT
+08 IMG
+0c CLU

ATTヘッダ部 
+00 magic 'ATT'
+16 X size / 0x10
+17 Y size / 0x10

IMAヘッダ部 
+00 magic 'IMA'
+10 data
******************************************************************************/

void	decode_aic(unsigned char *borg,char *fname)
{	unsigned char	*pATT;
	unsigned char	*pIMA;
	unsigned char	*pCLU;
	unsigned long	sx,sy;
	unsigned char	*bufa;
	unsigned char	*bufb;
	HANDLE			hdst;
	char			fdst[0x100];
	unsigned long	cx,cy,cz;
	unsigned long	tx,ty,tz;
	BITMAPFILEHEADER	bf;
	BITMAPINFOHEADER	bi;

	pATT=borg+*(unsigned long *)(borg+0x04);
	pIMA=borg+*(unsigned long *)(borg+0x08);
	pCLU=borg+*(unsigned long *)(borg+0x0c);

	sx=*(pATT+0x16)*0x10;
	sy=*(pATT+0x17)*0x10;

	bufa=new unsigned char[sx*sy*4];
	bufb=new unsigned char[sx*sy*4];
	memset(&bf,0x00,sizeof(BITMAPFILEHEADER));
	memset(&bi,0x00,sizeof(BITMAPINFOHEADER));

//printf("borg=%08p\n",borg);
//printf("pATT=%08p\n",pATT);
//printf("pIMA=%08p\n",pIMA);
//printf("pCLU=%08p\n",pCLU);
//printf("X   =%08X\n",sx);
//printf("Y   =%08X\n",sy);

	for(cx=0;cx<0x400;cx+=4){						//pCLU変換
		tx			=ler4(pCLU+0x10+cx);
		*(pCLU+cx+0x10+0)	=(unsigned char)(tx>> 8);		//B
		*(pCLU+cx+0x10+1)	=(unsigned char)(tx>>16);		//G
		*(pCLU+cx+0x10+2)	=(unsigned char)(tx>>24);		//R
		*(pCLU+cx+0x10+3)	=(unsigned char)(tx>> 0);	}	//X
	decode_palette_8bit(pCLU+0x10);

	for(cy=0;cy<sy;cy++)
		for(cx=0;cx<sx;cx++)
			memcpy(	bufa+(cy*sx+cx)*4,		//decode前なので上下入れ替え無し
					pCLU+0x10+*(
					pIMA+0x10+cy*sx+cx)*4,4);

	decode_ps2_d8t(bufa,sx,sy);

	sprintf(fdst,"%s.bmp",fname);
	hdst=NonOverWriteCreateFile((LPCSTR)fdst);

	*((char *)&bf.bfType+0)='B';
	*((char *)&bf.bfType+1)='M';
	bf.bfSize=			sizeof(BITMAPFILEHEADER)+
						sizeof(BITMAPINFOHEADER)+
						sx*sy;								//image
	bf.bfOffBits=		sizeof(BITMAPFILEHEADER)+
						sizeof(BITMAPINFOHEADER);
	bi.biSize=			sizeof(BITMAPINFOHEADER);
	bi.biWidth=			sx;
	bi.biHeight=		sy;
	bi.biPlanes=		1;
	bi.biBitCount=		32;
	WriteFile(hdst,&bf,sizeof(BITMAPFILEHEADER),&tx,NULL);
	WriteFile(hdst,&bi,sizeof(BITMAPINFOHEADER),&tx,NULL);

	for(cy=0;cy<sy;cy++)
		WriteFile(hdst,bufa+sx*(sy-cy-1)*4,sx*4,&tx,NULL);

	CloseHandle(hdst);
	delete[]	bufa;
	delete[]	bufb;
}
