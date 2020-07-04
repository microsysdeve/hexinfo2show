



typedef unsigned int GBit;	// bit variable
typedef long s32;
typedef short s16;
typedef signed char s8;

typedef unsigned long u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef unsigned long const uc32;	/* Read Only */
typedef unsigned short const uc16;	/* Read Only */
typedef unsigned char const uc8;	/* Read Only */
typedef const unsigned char ucode;	//Code Data

typedef volatile unsigned long vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char vu8;

typedef volatile unsigned long const vuc32;	/* Read Only */
typedef volatile unsigned short const vuc16;	/* Read Only */
typedef volatile unsigned char const vuc8;	/* Read Only */

#define 		_cIMype_Len_    	10
#define 		_cSoftVer_Len_    	32
#define 		_cHardVer_Len_    	32

struct STMETER_CONFIG
{
  char ctemp;
  char cMeter_Type;		//      enum    ENUMMETERCONFIG                 bMeter_Type:1;                                  // 远程表和本地表区分
  char cMeter_ComType;		//      enum    ENUMMETER_COMCONFIG             bMeter_ComType:1;                               //      载波表和485表区分
  char cMeter_JDMODE;		//      enum    ENUMMETER_JDMODE                bMeter_JDMODE:1;                                //      闸类型区分

};

union UNMETERCONFIG
{
  unsigned char cMeterConfig[4];	//      表类型描述参数
  struct STMETER_CONFIG stmeter_config;
};



#pragma pack(1)
//struct     __attribute__((__packed__))   STMEMTER_STATU
struct STMEMTER_STATU
{
  u8 IMType[_cIMype_Len_];	//电表类型(F12F)
  u8 SoftVer[_cSoftVer_Len_];	//软件版本号(F13F)
  u8 HardVer[_cHardVer_Len_];	//硬件版本号(F13F)
};

 

 


enum ENUMMETERCONFIG
{
  _bMETTER_LOCAL_ = 0x00,
  _bMETTER_REMOTE_ = 0x01
};

enum ENUMDATACONFIG
{
  _bData_Loc_ = (1 << _bMETTER_LOCAL_),
  _bData_Far_ = (1 << _bMETTER_REMOTE_),
  _bData_All_ = ((_bData_Loc_) | (_bData_Far_)),
};

enum ENUMMETER_COMCONFIG
{
  _bMETER_ZB_ = 0x33,
  _bMETER_485_ = 0x44
};

enum ENUMMETER_JDMODE
{
  _bMeter_JD_IN_ = 0x55,
  _bMeter_JD_OUT_ = 0x66
};

struct  STVERSION_CRC
{
	char	sProjectName[32];
	char sVerion[32];
	unsigned long lCodeLen;
	unsigned long lCrc32;
	unsigned long lSign;
	char 	sProjectAddr[256];
};
