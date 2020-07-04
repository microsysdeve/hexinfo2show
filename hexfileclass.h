
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



enum   _FILEHEX_
{
	_Data_Record_ = 0,//'00' Data Record//数据记录
	_End_of_File_Record_ = 01,// End of File Record//文件结束记录
	_Extended_Segment_Address_Record_ = 02,// Extended Segment Address Record//扩展段地址记录
	_Start_Segment_Address_Record_ = 03,//Start Segment Address Record//开始段地址记录
	_Extended_Linear_Address_Record_ = 04,//Extended Linear Address Record//扩展线性地址记录
	_Start_Linear_Address_Record_ = 05,//Start Linear Address Record//开始线性地址记录
};

class  STHEXFILEFORMAT
{
	unsigned long lAddr;
	char	CheckLine_xj(char *sbuf, int len);			//		检测行校码,sbuf 指针不包含起始：，len 长度包含校验码字节
};