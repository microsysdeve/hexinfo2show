#ifndef _hexfile_class_hpp_
#define _hexfile_class_hpp_

#define			UINT		unsigned int
#define			BYTE		  char

#define			_lTextBufLen_			(1024*1024)	//                ����ı����峤��Ϊ1M
enum
{
  SUCCESS = 0,
  FALSE = 1,
};
typedef struct
{
  BYTE data[16];		//����  
  BYTE len;			//���ݳ���  
  UINT pos;			//ƫ�Ƶ�ַ  
  BYTE type;			//����  
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
  int len;			//bin�ļ���С  
  UINT startAddress;		//ˢд����ʼ��ַ  
  BYTE *pContent;		//ת���������  
} HexToBinData;
enum
{
  _Data_Record_ = 0,		//   '00' Data Record//���ݼ�¼
  _End_of_File_Record_ = 1,	//'01' End of File Record//�ļ�������¼
  _Extended_Segment_Address_Record_ = 02,	// '02' Extended Segment Address Record//��չ�ε�ַ��¼
  _Start_Segment_Address_Record_ = 03,	//'03' Start Segment Address Record//��ʼ�ε�ַ��¼
  _Extended_Linear_Address_Record_ = 04,	//'04' Extended Linear Address Record//��չ���Ե�ַ��¼
  _Start_Linear_Address_Record_ = 05,	//'05' Start Linear Address Record//��ʼ���Ե�ַ��¼
};

struct STDATAEXPALIN
{
  char *sp;			//        ����ָ��
  unsigned int iData;		//              ����
  unsigned long lAddr;		//              ��ʼ��ַ
};

struct STFILEDATA
{
  char sbuf[_lTextBufLen_];
  unsigned long lbuflen;	//      ����������
  unsigned long lsbuflen;	//      ʵ�ʳ���
};

class CLHEXFILEDATA
{

public:
  struct STFILEDATA sttextfiledata;	// �����ļ�������
  struct STFILEDATA stbindata;	// BIN��������
  struct STDATAEXPALIN stdataplain[8];	//  ��������
  int segnum;			//               ��ַ��������
  char *spBinWork;		//        bin�ļ�����ָ��


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
