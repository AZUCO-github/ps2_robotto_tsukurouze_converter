///////////////////////////////////////////////////////////////////////////////
//	PS2 Hunex converter
//		061010
//			by	AZUCO
///////////////////////////////////////////////////////////////////////////////

#include	<windows.h>
#include	<stdio.h>

extern	void	decode_hfu2(HANDLE,char *);
extern	void	decode_ufa(unsigned char *,char *);
extern	void	decode_ufe(unsigned char *,char *);
extern	void	decode_aic(unsigned char *,char *);
extern	void	decode_xex(unsigned char *,char *,unsigned long);



void	main(void)
{	char			file[_MAX_PATH];
	char			*tfpa;
	char			*tfpb;
	HANDLE			hndl;
	unsigned char	*buff=0;
	unsigned long	size;
	char			drive[MAX_PATH];
	char			dir[MAX_PATH];
	char			fname[MAX_PATH];
	char			ext[MAX_PATH];
	unsigned long	tmp;

	printf("PS2 Hunex Converter\n");
	printf("\t\tProg. By AZUCO\n\n");



	strcpy(file,GetCommandLine());				//コマンドラインをコピーする

	tfpa=strrchr(file,' ');		//一番最後のスペース以降をファイル名と見なす
	tfpa++;

	tfpb=strrchr(tfpa,'"');		//ダブルクオートありの場合
	if(tfpb!=NULL)	*tfpb=0;

	tfpb=strrchr(tfpa,'>');		//リダイレクトの場合
	if(tfpb!=NULL)	*tfpb=0;



	tfpb=&file[0];
loop:
	if(*tfpa=='\\'){	*(tfpb+0)='\\';
						*(tfpb+1)='\\';
						tfpa++;
						tfpb+=2;
						goto loop;		}
	if(*tfpa>=0x20){	*tfpb=*tfpa;
						tfpa++;
						tfpb++;
						goto loop;		}
						*tfpb=0;



//strcpy(file,"E:\\TMP\\I100\\ETC\\K.NBP");

	hndl=CreateFile(file,
					GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if(hndl==(HANDLE)-1){
		printf("Hunex <data file>\n");
		printf("\tError\tsource file not found\n");
		exit(-1);	}

	_splitpath(file,drive,dir,fname,ext);
	if(	strcmp(_strlwr(ext),".bin")==0)		decode_hfu2(hndl,fname);
	else{
		size=GetFileSize(hndl,NULL);
		buff=new unsigned char[size];
		ReadFile(hndl,buff,size,&tmp,NULL);	}
	CloseHandle(hndl);

	if(	strcmp(_strlwr(ext),".ufa")==0)		decode_ufa(buff,fname);
	if(	strcmp(_strlwr(ext),".ufe")==0)		decode_ufe(buff,fname);
	if(	strcmp(_strlwr(ext),".aic")==0)		decode_aic(buff,fname);
	if(	strcmp(_strlwr(ext),".xex")==0)		decode_xex(buff,fname,size);
	if(buff!=0)	delete[]	buff;

	
	CloseHandle(hndl);
}
