#ifndef _hexfile_class_hpp_
#define _hexfile_class_hpp_

#define			UINT		unsigned int
#define			BYTE		  char

#define			_lTextBufLen_			(1024*1024)	//                最大文本缓冲长度为1M
enum
{
  SUCCESS = 0,
  FALSE = 1,
};
typedef struct
{
  BYTE data[16];		//数据  
  BYTE len;			//数据长度  
  UINT pos;			//偏移地址  
  BYTE type;			//类型  
} HexLinData;

struct STLINEFIRST
{
  unsigned char cFirstChar;
  unsigned char sLineLen[2];
  unsigned char sAddr[4];
  unsigned char sType[2];
  char sData[128];
};
typedef struct
{
  int len;			//bin文件大小  
  UINT startAddress;		//刷写的起始地址  
  BYTE *pContent;		//转化后的内容  
} HexToBinData;
enum
{
  _Data_Record_ = 0,		//   '00' Data Record//数据记录
  _End_of_File_Record_ = 1,	//'01' End of File Record//文件结束记录
  _Extended_Segment_Address_Record_ = 02,	// '02' Extended Segment Address Record//扩展段地址记录
  _Start_Segment_Address_Record_ = 03,	//'03' Start Segment Address Record//开始段地址记录
  _Extended_Linear_Address_Record_ = 04,	//'04' Extended Linear Address Record//扩展线性地址记录
  _Start_Linear_Address_Record_ = 05,	//'05' Start Linear Address Record//开始线性地址记录
};

struct STDATAEXPALIN
{
  char *sp;			//        数据指针
  unsigned int iData;		//              长度
  unsigned long lAddr;		//              起始地址
};

struct STFILEDATA
{
  char sbuf[_lTextBufLen_];
  unsigned long lbuflen;	//      缓冲区长度
  unsigned long lsbuflen;	//      实际长度
};

class CLHEXFILEDATA
{

public:
  struct STFILEDATA sttextfiledata;	// 文体文件缓冲区
  struct STFILEDATA stbindata;	// BIN件缓冲区
  struct STDATAEXPALIN stdataplain[8];	//  描述段数
  int segnum;			//               地址描述段数
  char *spBinWork;		//        bin文件工作指针


    CLHEXFILEDATA::CLHEXFILEDATA (void);
  unsigned char CLHEXFILEDATA::HexCharToByte (char c);
  char hexseg_init (unsigned long lAddr);
  char hexseg_inc (unsigned long laddr);
  void hexbinbuf_add (char *datap, unsigned int ilen);
  int hex2formatbuf (const char *str, HexToBinData * pData);
  unsigned char GetFirstByte (const char *str);
  int GetLine (const char *str, char *pBuf);
  int GetHexLineData (const char *line, HexLinData * pData);
  int GetFirstDataLine (const char *str, BYTE type, HexLinData * pData);
  int GetStartAddress (const char *str, UINT * pStartAddress);
};


extern class CLHEXFILEDATA sthexfiledata;

int hex2formatbuf (const char *str, HexToBinData * pData);
#endif
