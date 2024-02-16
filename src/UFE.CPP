#include	<windows.h>
#include	<stdio.h>
#include	<ctype.h>

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);
		void	decode_ufe(unsigned char *,char *);



/*****メモ*****UFE フォーマット************************************************
ヘッダ部 
+00 全アイテム数*2
+04 アイテム格納場所アドレス 
+08 アイテム長さ
******************************************************************************/

void	decode_ufe(unsigned char *borg,char *fname)
{
	unsigned long	IMX=*(unsigned long*)(borg+0x00)>>1;	//Item MAX NO.
	unsigned long	IOF=*(unsigned long*)(borg+0x04);		//Item OFfset
	unsigned long	INO;									//Item NO.
	unsigned long	ITA;									//Item Table Addr
	unsigned long	ILN;									//Item LeNgth
	char			name[0x100];							//dst filename
	char			ext[3];									//dst filename.ext
	HANDLE			hdst;
	unsigned long	tmp;

	if(IMX>=0x20){
		printf("%s.ufe invalid file ? %08X\n",fname,IMX);
		return;
	}

		ITA=*(unsigned long*)(borg+0x04)+ *(unsigned long*)(borg+0x08);
		ILN=*(unsigned long*)(borg+0x0c)-ITA;
	for(INO=0;INO<IMX;INO++){
						ext[0]=borg[ITA+0];
						ext[1]=borg[ITA+1];
						ext[2]=borg[ITA+2];
		if(	(!isalpha(	ext[0]))||
			(!isalpha(	ext[1]))||
			(!isalpha(	ext[2]))	){
						ext[0]='b';
						ext[1]='i';
						ext[2]='n';	}
		sprintf(name,"%s_%02X.%c%c%c",fname,INO,ext[0],ext[1],ext[2]);
		printf("%s\n",name);

		hdst=NonOverWriteCreateFile((LPCSTR)name);
		WriteFile(hdst,borg+ITA,ILN,&tmp,NULL);
		CloseHandle(hdst);

		ITA=*(unsigned long*)(borg+0x0c+0x04* INO);
		ILN=*(unsigned long*)(borg+0x0c+0x04*(INO+1))-ITA;
	}
}
