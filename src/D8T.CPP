/******************************************************************************
	PS2 8bit tile decoding
******************************************************************************/
#include	<windows.h>
#include	<stdio.h>

void	decode_ps2_d8t(
	unsigned char		*src,
	unsigned long		sx,
	unsigned long		sy		)
{	unsigned long		sz=sx*sy;
	unsigned long		cx,cy,cz;
	unsigned char		*ba;
	unsigned char		*bb;

	ba=new unsigned char[sx*sy*4];
	bb=new unsigned char[sx*sy*4];
	memset(ba,0x00,sx*sy*4);
	memcpy(bb,src ,sx*sy*4);

	for(cx=0;cx<sz;cx+=16){
		for(cz=0;cz<4;cz++){
		memcpy(ba+(cx+cz*4+ 0)*4,bb+(cx+cz+ 0)*4,4);
		memcpy(ba+(cx+cz*4+ 1)*4,bb+(cx+cz+ 4)*4,4);
		memcpy(ba+(cx+cz*4+ 2)*4,bb+(cx+cz+ 8)*4,4);
		memcpy(ba+(cx+cz*4+ 3)*4,bb+(cx+cz+12)*4,4);
	}	}

	for(cy=0;cy<sz;cy+=sx*2){
		if(!(cy&(sx*4)))
			for(cx=0;cx<(sx*2);cx+=8){
				memcpy(bb+(cy+cx+0)*4,ba+(cy+cx+4)*4,16);
				memcpy(bb+(cy+cx+4)*4,ba+(cy+cx+0)*4,16);	}
		else	memcpy(bb+(cy     )*4,ba+(cy     )*4,sx*8);	}

	for(cy=0;cy<sz;cy+=sx*2){
		for(cx=0;cx<sx*2;cx+=0x80){
			memcpy(ba+(cy+cx+(0x00<<2))*4,bb+(cy+cx+(0x04<<2))*4,16);
			memcpy(ba+(cy+cx+(0x01<<2))*4,bb+(cy+cx+(0x05<<2))*4,16);
			memcpy(ba+(cy+cx+(0x02<<2))*4,bb+(cy+cx+(0x06<<2))*4,16);
			memcpy(ba+(cy+cx+(0x03<<2))*4,bb+(cy+cx+(0x07<<2))*4,16);

			memcpy(ba+(cy+cx+(0x04<<2))*4,bb+(cy+cx+(0x01<<2))*4,16);
			memcpy(ba+(cy+cx+(0x05<<2))*4,bb+(cy+cx+(0x00<<2))*4,16);
			memcpy(ba+(cy+cx+(0x06<<2))*4,bb+(cy+cx+(0x03<<2))*4,16);
			memcpy(ba+(cy+cx+(0x07<<2))*4,bb+(cy+cx+(0x02<<2))*4,16);

			memcpy(ba+(cy+cx+(0x08<<2))*4,bb+(cy+cx+(0x0c<<2))*4,16);
			memcpy(ba+(cy+cx+(0x09<<2))*4,bb+(cy+cx+(0x0d<<2))*4,16);
			memcpy(ba+(cy+cx+(0x0a<<2))*4,bb+(cy+cx+(0x0e<<2))*4,16);
			memcpy(ba+(cy+cx+(0x0b<<2))*4,bb+(cy+cx+(0x0f<<2))*4,16);

			memcpy(ba+(cy+cx+(0x0c<<2))*4,bb+(cy+cx+(0x09<<2))*4,16);
			memcpy(ba+(cy+cx+(0x0d<<2))*4,bb+(cy+cx+(0x08<<2))*4,16);
			memcpy(ba+(cy+cx+(0x0e<<2))*4,bb+(cy+cx+(0x0b<<2))*4,16);
			memcpy(ba+(cy+cx+(0x0f<<2))*4,bb+(cy+cx+(0x0a<<2))*4,16);

			memcpy(ba+(cy+cx+(0x10<<2))*4,bb+(cy+cx+(0x14<<2))*4,16);
			memcpy(ba+(cy+cx+(0x11<<2))*4,bb+(cy+cx+(0x15<<2))*4,16);
			memcpy(ba+(cy+cx+(0x12<<2))*4,bb+(cy+cx+(0x16<<2))*4,16);
			memcpy(ba+(cy+cx+(0x13<<2))*4,bb+(cy+cx+(0x17<<2))*4,16);

			memcpy(ba+(cy+cx+(0x14<<2))*4,bb+(cy+cx+(0x11<<2))*4,16);
			memcpy(ba+(cy+cx+(0x15<<2))*4,bb+(cy+cx+(0x10<<2))*4,16);
			memcpy(ba+(cy+cx+(0x16<<2))*4,bb+(cy+cx+(0x13<<2))*4,16);
			memcpy(ba+(cy+cx+(0x17<<2))*4,bb+(cy+cx+(0x12<<2))*4,16);

			memcpy(ba+(cy+cx+(0x18<<2))*4,bb+(cy+cx+(0x1c<<2))*4,16);
			memcpy(ba+(cy+cx+(0x19<<2))*4,bb+(cy+cx+(0x1d<<2))*4,16);
			memcpy(ba+(cy+cx+(0x1a<<2))*4,bb+(cy+cx+(0x1e<<2))*4,16);
			memcpy(ba+(cy+cx+(0x1b<<2))*4,bb+(cy+cx+(0x1f<<2))*4,16);

			memcpy(ba+(cy+cx+(0x1c<<2))*4,bb+(cy+cx+(0x19<<2))*4,16);
			memcpy(ba+(cy+cx+(0x1d<<2))*4,bb+(cy+cx+(0x18<<2))*4,16);
			memcpy(ba+(cy+cx+(0x1e<<2))*4,bb+(cy+cx+(0x1b<<2))*4,16);
			memcpy(ba+(cy+cx+(0x1f<<2))*4,bb+(cy+cx+(0x1a<<2))*4,16);
		}
	}

	for(cy=0;cy<sz;cy+=sx*2){
		for(cx=0;cx<sx*2;cx+=0x20){
			memcpy(bb+(cy+ 0+(cx>>1))*4,ba+(cy+ 0+cx+0x00)*4,0x40);
			memcpy(bb+(cy+sx+(cx>>1))*4,ba+(cy+ 0+cx+0x10)*4,0x40);	}	}

	for(cy=0;cy<sz;cy+=sx*2){
		for(cx=0;cx<sx;cx+=8){
			memcpy(ba+(cy+ 0+cx+0)*4,bb+(cy+sx+cx+0)*4,16);
			memcpy(ba+(cy+sx+cx+0)*4,bb+(cy+ 0+cx+0)*4,16);
			memcpy(ba+(cy+ 0+cx+4)*4,bb+(cy+ 0+cx+4)*4,16);
			memcpy(ba+(cy+sx+cx+4)*4,bb+(cy+sx+cx+4)*4,16);	}	}

	for(cx=0;cx<sz;cx+=sx*8){
		memcpy(src+(cx+sx*0)*4,ba+(cx+sx*0)*4,sx*4);
		memcpy(src+(cx+sx*1)*4,ba+(cx+sx*2)*4,sx*4);
		memcpy(src+(cx+sx*2)*4,ba+(cx+sx*1)*4,sx*4);
		memcpy(src+(cx+sx*3)*4,ba+(cx+sx*3)*4,sx*4);

		memcpy(src+(cx+sx*4)*4,ba+(cx+sx*5)*4,sx*4);
		memcpy(src+(cx+sx*5)*4,ba+(cx+sx*7)*4,sx*4);
		memcpy(src+(cx+sx*6)*4,ba+(cx+sx*4)*4,sx*4);
		memcpy(src+(cx+sx*7)*4,ba+(cx+sx*6)*4,sx*4);	}

	delete[]	ba;
	delete[]	bb;
}
