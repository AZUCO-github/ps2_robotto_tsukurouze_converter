#include	<windows.h>
#include	<stdio.h>

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);



void	tim2_uncompress(	unsigned char *sbuf,
							unsigned char *dbuf,
							unsigned long slen,
							unsigned long dlen	)
{	unsigned long	fv,fc;
	unsigned long	sa,sl,sc,el,dd;
	unsigned long	sp=0;
	unsigned long	dp=0;

	memset(dbuf,0x00,dlen);
	for(;;){
		fv=*(sbuf+sp);
		sp++;
		for(fc=0;fc<8;fc++){
			if((fv&1)==0){
				sl=3+(0x0f&*(sbuf+sp+1));
				sa=(((*(sbuf+sp+1))<<4)&0xf00)|(*(sbuf+sp));

									sc=(dp-sa-0x12)&0xfffff000;
				if(sc&0x80000000)	sc=0;

				if(dp>(sc+sa+18))
					if((dp-(sc+sa+18))>sl)	el=sl;
					else					el=dp-(sc+sa+18);
				else						el=1;

				for(dd=0;dd<sl;dd+=el)
					memcpy(dbuf+dp+dd,dbuf+sc+sa+18,el);
				sp+=2;	dp+=sl;
			}else{
				dbuf[dp]=sbuf[sp];
				sp++;	dp++;
			}
			fv>>=1;

			if(sp>=slen)	return;
			if(dp>=dlen)	return;
		}
	}
}
