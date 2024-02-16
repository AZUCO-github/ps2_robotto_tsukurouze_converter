//	PKZIP
#ifndef		_AZU_PKZIP_
#define		_AZU_PKZIP_

class	PKZIP{
public:
	unsigned long	m_search_pkxx(unsigned char,unsigned char *,unsigned long);
	unsigned long	m_search_name(unsigned char *,unsigned long,char *);
	unsigned long	m_extract(	unsigned char *,unsigned long,
								unsigned char *,unsigned long);
};

#define ZSIG	0x00	//SIGnature
#define ZVER	0x04	//VERsion
#define ZGFL	0x06	//Genarate FLug
#define ZMTD	0x08	//MeTHod
#define ZTIM	0x0a	//TIMe
#define ZDAY	0x0c	//date
#define ZCRC	0x0e	//CRC32
#define ZZLN	0x12	//compress LeNgth
#define ZULN	0x16	//uncompress LeNgth
#define ZFLN	0x1a	//File name LeNgth
#define ZXLN	0x1c	//eXtra LeNgth
#define ZNAM	0x1e	//NAMe

#endif		_AZU_PKZIP_
