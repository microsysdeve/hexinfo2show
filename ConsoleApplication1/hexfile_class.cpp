#include "stdafx.h"
#include "hexfile_class.h"

//class CLHEXFILEDATA  clhexfiledata;

#define		ASSERT		//


CLHEXFILEDATA::CLHEXFILEDATA (void)
{
  CLHEXFILEDATA::sttextfiledata.lbuflen =
    sizeof (CLHEXFILEDATA::sttextfiledata.sbuf);
  CLHEXFILEDATA::sttextfiledata.lsbuflen = 0;
}

char
CLHEXFILEDATA::hexseg_init (unsigned long lAddr)
{

  memset (stdataplain, 0, sizeof (stdataplain));
  spBinWork = stbindata.sbuf;

  return SUCCESS;
}

char
CLHEXFILEDATA::hexseg_inc (unsigned long laddr)
{
  segnum++;
  if (segnum >= (sizeof (stdataplain) / (sizeof (stdataplain[0]))))
    return FALSE;

  if (0 == segnum)
    hexseg_init (laddr);

  stdataplain[segnum].lAddr = laddr;
  stdataplain[segnum].sp = spBinWork;
  return SUCCESS;
}


void
CLHEXFILEDATA::hexbinbuf_add (char *datap, unsigned int ilen)
{
  memcpy (spBinWork, datap, ilen);
  spBinWork += ilen;
}

char *line_2_buf (char *sfilename, struct STFILEDATA *spdata);
unsigned char
CLHEXFILEDATA::HexCharToByte (char c)
{
  if (c >= '0' && c <= '9')
    return c - '0';
  else if (c >= 'a' && c <= 'f')
    return c - 'a' + 0x0a;
  else if (c >= 'A' && c <= 'F')
    return c - 'A' + 0x0a;

  return -1;
}

unsigned char
CLHEXFILEDATA::GetFirstByte (const char *str)
{
  ASSERT (str != NULL);

  BYTE tmp = 0;
  tmp = HexCharToByte (str[0]);
  tmp <<= 4;
  tmp += HexCharToByte (str[1]);

  return tmp;
}

//从字符串中获取一行  
int
CLHEXFILEDATA::GetLine (const char *str, char *pBuf)
{
  ASSERT (str != NULL);
  ASSERT (pBuf != NULL);

  char *start = strchr ((char *) str, ':');
  if (NULL == start)
    {
      return -1;
    }

  char *end = strstr (start, "\r\n");
  char *p = start;
  char *p2 = pBuf;
  int len = 0;
  for (; p < end + 2; p++, p2++)
    {
      if (*p == '\0')
	break;
      *p2 = *p;
      len++;
    }
  *p2 = '\0';

  return len;
}

//获取一行的数据  
int
CLHEXFILEDATA::GetHexLineData (const char *line, HexLinData * pData)
{
  ASSERT (line != NULL);
  ASSERT (pData != NULL);
  struct STLINEFIRST *stp = (struct STLINEFIRST *) line;
  if (':' != stp->cFirstChar)
    return -1;
  int i = 1;
  pData->len = GetFirstByte ((const char *) stp->sLineLen);
  pData->pos = GetFirstByte ((const char *) stp->sAddr);
  pData->pos <<= 8;
  pData->pos += GetFirstByte ((const char *) &(stp->sAddr[2]));
  pData->type = GetFirstByte ((const char *) stp->sType);
  for (int j = 0, i = 0; j < pData->len; i += 2, j++)
    {
      pData->data[j] = GetFirstByte (&(stp->sData[i]));
    }
  return 0;
}

//获取第一行指定类型的数据  
int
CLHEXFILEDATA::GetFirstDataLine (const char *str, BYTE type,
				 HexLinData * pData)
{

  ASSERT (str != NULL);
  ASSERT (pData != NULL);

  char *p = (char *) str;
  char line[128];
  HexLinData data = { 0 };
  int len = strlen (str);
  int dataLen = 0;

  for (; p < str + len; p += dataLen)
    {
      memset (line, 0, 128);
      dataLen = GetLine (p, line);
      if (dataLen < 0)
	return -1;
      memset (&data, 0x00, sizeof (HexLinData));
      if (0 != GetHexLineData (line, &data))
	return -1;

      if (data.type == type)
	{
	  memcpy (pData, &data, sizeof (HexLinData));
	  return 0;
	}
    }
  return -1;
}

int
CLHEXFILEDATA::GetStartAddress (const char *str, UINT * pStartAddress)
{
  HexLinData data = { 0 };
  UINT basePos = 0;
  UINT pos;

  if (0 != GetFirstDataLine (str, 4, &data))
    return -1;
  for (int i = 0; i < data.len; i++)
    {
      basePos <<= 8;
      basePos += data.data[i];
    }



  memset (&data, 0x00, sizeof (HexLinData));
  if (0 != GetFirstDataLine (str, 0, &data))
    return -1;
  pos = data.pos;

  *pStartAddress = (basePos << 16) + pos;

  return 0;
}

int
CLHEXFILEDATA::hex2formatbuf (const char *str, HexToBinData * pData)
{
  ASSERT (str != NULL);
  ASSERT (pData != NULL);

  int size = strlen (str);

  UINT startAddress = 0;
  char line[128] = { 0 };
  HexLinData data = { 0 };

  char *p = (char *) str;
  int binLen = 0;
  int len = 0;
  segnum = -1;

  for (binLen = 0; p < str + size; p += len)
    {
      memset (line, 0, 128);
      len = GetLine (p, line);
      if (len < 0)
	break;

      memset (&data, 0x00, sizeof (HexLinData));
      if (0 != GetHexLineData (line, &data))
	return -1;
      switch (data.type)
	{
	case _Data_Record_:	// = 0,//   '00' Data Record//数据记录
	  binLen += data.len;
	  hexbinbuf_add (data.data, data.len);
	  break;
	case _End_of_File_Record_:	//=/ 1,//'01' End of File Record//文件结束记录
	  return 0;

	case _Extended_Segment_Address_Record_:	//= 02,// '02' Extended Segment Address Record//扩展段地址记录
	case _Start_Segment_Address_Record_:	//= 03,//'03' Start Segment Address Record//开始段地址记录
	case _Extended_Linear_Address_Record_:	//= 04,//'04' Extended Linear Address Record//扩展线性地址记录
	  if (0 != GetStartAddress (p, &startAddress))
	    return -1;
	  hexseg_inc (startAddress);
	  break;
	case _Start_Linear_Address_Record_:	//= 05,//'05' St
	  break;
	}

    }

}
