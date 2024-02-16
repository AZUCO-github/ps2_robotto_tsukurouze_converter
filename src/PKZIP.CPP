//	PKZIP
#include	<string.h>
#include	<zlib.h>
#include	"pkzip.h"



unsigned long	PKZIP::m_search_pkxx(
	unsigned char sel,
	unsigned char *buf,
	unsigned long len				)
{
	unsigned char	pk[4];
	unsigned long	x;

								pk[0]='P';	pk[1]='K';
	switch(sel){
					case	1:	pk[2]=0x01;	pk[3]=0x02;	break;
					default:
					case	3:	pk[2]=0x03;	pk[3]=0x04;	break;
					case	5:	pk[2]=0x05;	pk[3]=0x06;	break;	}
	len-=4;
	for(x=0;x<len;x++)
		if(memcmp(buf+x,pk,4)==0)	return(x);
	return(0xffffffff);
}



unsigned long	PKZIP::m_search_name(
	unsigned	char	*buf,
	unsigned	long	len,
				char	*name)
{	unsigned long	off1,off2;

	for(off1=0;;){
		off2=m_search_pkxx(3,buf+off1,len-off1);
		if(off2>(len-4))	return(0xffffffff);			//not found
		off1+=off2;
		if(_strnicmp((char *)buf+off1+ZNAM,name,strlen(name))==0)
							return(off1);
		off1+=*(unsigned long *)(buf+off1+ZZLN)+ZNAM;	//skip
	}
}



unsigned long	PKZIP::m_extract(
	unsigned char *b_in,
	unsigned long l_in,
	unsigned char *b_out,
	unsigned long l_out			)
{
	z_stream		z;
	unsigned long	tul;

	z.zalloc	=Z_NULL;
	z.zfree		=Z_NULL;
	z.opaque	=Z_NULL;

	z.next_in	=Z_NULL;
	z.avail_in	=0;
	inflateInit2(&z,-MAX_WBITS);

	z.next_in	=b_in;
	z.avail_in	=l_in;
	z.next_out	=b_out;
	z.avail_out	=l_out;
	tul=inflate(&z,Z_NO_FLUSH);

	inflateEnd(&z);
//	return(tul);				//–{—ˆ‚Í‚±‚¿‚ç
	return(z.total_out);
}
