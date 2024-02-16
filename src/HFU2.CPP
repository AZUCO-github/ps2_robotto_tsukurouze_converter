///////////////////////////////////////////////////////////////////////////////
//	PS2 Hunex converter
//		HFU2 format
//			by	AZUCO
///////////////////////////////////////////////////////////////////////////////

#include	<windows.h>
#include	<stdio.h>

/*****メモ*****HFU2 フォーマット***********************************************
ヘッダ部 
+00 magic 'HFU2' 
+04 全アイテム数+1 
+08 アイテム格納場所offset 
+0c ? 

アイテムテーブル(16byte size) 
+00 ヘッダ部+08のoffsetを足したのが、ファイル先頭よりの位置 
+04 アイテムの圧縮された状態での長さ 
+08 アイテムの（多分）展開された時の長さ 
+0c チェックサム？暗号化キー？よくわからん 
******************************************************************************/

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);



void	decode_hfu2(HANDLE hndl,char *file)
{
	char			name[0x100];	//dst filename
	char			ITB[0x20];		//Item Table Buffer
	unsigned long	IMX;			//Item MAX NO.
	unsigned long	ITA;			//Item Table Addr
	unsigned long	INO;			//Item NO.
	unsigned long	IDA;			//Item Data Address
	unsigned long	ILN;			//Item LeNgth
	unsigned long	tmp;
	unsigned char	*bdst;
	HANDLE			hdst;

	SetFilePointer(hndl,0,0,FILE_BEGIN);
	ReadFile(hndl,ITB,0x10,&tmp,NULL);
	if(	(ITB[0]!='H')	||		//magic check
		(ITB[1]!='F')	||
		(ITB[2]!='U')	||
		(ITB[3]!='2')		)	return;
	IMX=*(unsigned long*)(ITB+0x04);
	ITA=*(unsigned long*)(ITB+0x08);

	for(INO=1;IMX!=INO;INO++){
		SetFilePointer(hndl,INO*0x10,0,FILE_BEGIN);
		ReadFile(hndl,ITB,0x10,&tmp,NULL);
		IDA=*(unsigned long*)(ITB+0x00);
		ILN=*(unsigned long*)(ITB+0x04);

		bdst=new unsigned char[ILN];
		SetFilePointer(hndl,ITA+IDA,0,FILE_BEGIN);
		ReadFile(hndl,bdst,ILN,&tmp,NULL);
		if(	(bdst[0]=='U')	&&
			(bdst[1]=='F')	&&
			(bdst[2]=='F')	&&
			(bdst[3]=='A')		)
			sprintf(name,"%s_%04X.UFA",file,INO);
		else
			sprintf(name,"%s_%04X.%c%c%c",file,INO,bdst[0],bdst[1],bdst[2]);
printf("%s\n",name);
		hdst=NonOverWriteCreateFile((LPCSTR)name);
		WriteFile(hdst,bdst,ILN,&tmp,NULL);
		CloseHandle(hdst);
		delete[]	bdst;
	}
}
