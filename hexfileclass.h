
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



enum   _FILEHEX_
{
	_Data_Record_ = 0,//'00' Data Record//���ݼ�¼
	_End_of_File_Record_ = 01,// End of File Record//�ļ�������¼
	_Extended_Segment_Address_Record_ = 02,// Extended Segment Address Record//��չ�ε�ַ��¼
	_Start_Segment_Address_Record_ = 03,//Start Segment Address Record//��ʼ�ε�ַ��¼
	_Extended_Linear_Address_Record_ = 04,//Extended Linear Address Record//��չ���Ե�ַ��¼
	_Start_Linear_Address_Record_ = 05,//Start Linear Address Record//��ʼ���Ե�ַ��¼
};

class  STHEXFILEFORMAT
{
	unsigned long lAddr;
	char	CheckLine_xj(char *sbuf, int len);			//		�����У��,sbuf ָ�벻������ʼ����len ���Ȱ���У�����ֽ�
};