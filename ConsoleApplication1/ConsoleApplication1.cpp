// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "meterdef.h"
#include <stdlib.h>
#include "hexfile_class.h"

// progtoencry.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "time.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
class CLHEXFILEDATA clhexfiledata;

#define			_iVer_			30

#define			_iBuflen_		213
#define			_iRand_			2

const char	sVersion[] = "This program Create by microsys@sina.com.CopyRight 2020-07-06\n";
//Addr: = https ://github.com/microsysdeve/hexinfo2show.git\n";

const char sPorgNoLimt[] = "nolimit";
const unsigned long lMaxno = 65533;
const unsigned long lMaxno_nolimt = 65534;



void
message_fail (void)
{
 fprintf(stdout, "%s", sVersion);
  fprintf (stderr, "%s", "The input file error\n");
  fprintf (stderr, "%s", "Example:\n");
  fprintf (stderr, "%s", " hexinfo2show  hexfilename \n");
  getchar ();
  exit (1);
}



class DATAUNIT
{
public:
  char *sp;
  int len;
  char *sMessageHead;
  char *sMessageEnd;
    DATAUNIT (char *sp1, int len1)
  {
    sp = sp1;
    len = len1;
  }
  virtual void dataprintf () = 0;
  void dataout (void);

};

void
DATAUNIT::dataout (void)
{
  if (sMessageHead)
    fprintf (stdout, "$s", sMessageHead);
  dataprintf ();
  if (sMessageEnd)
    fprintf (stdout, "$s\n", sMessageEnd);;
}

class STRSHOW:DATAUNIT
{

  void dataprintf ();
};

void
STRSHOW::dataprintf (void)
{
  int i;
  for (i = 0; i < len; i++)
    fprintf (stdout, "%c", sp[i]);
}
 


FILE *sfp = NULL;
FILE *dfp = NULL;


char
hexfile_session (char *sbuf, short ibuflen)
{
  return NULL;
}

unsigned long
line_2_buf (char *sfilename, char *spdata, unsigned long llen)	// struct               STFILEDATA  *spdata)
{
  unsigned short i;
  unsigned long lNum = 0, ltemp;

  errno_t err;

  err = fopen_s (&sfp, sfilename, "rb");

  if (err)
    {

      message_fail ();

      return NULL;
    }
  fseek (sfp, 0, 0);


  lNum = fread_s (spdata, llen, 1, llen, sfp);
  fclose (sfp);
  return lNum;

}

void
message_success (void)
{
  fprintf (stderr, "%s", "success\n");
  exit (1);
}



void
filemessageout(char *strfilename, struct STVERSION_CRC *stp)
{
	
	fprintf(stdout, "filename:=%s\n", strfilename);
	fprintf(stdout, "project=%s\n", stp->sProjectName);	
	fprintf(stdout, "version=%02d-%02d-%02d_%02d:%02d:%02d\n", stp->sVerion[2], stp->sVerion[1], stp->sVerion[0], stp->sVerion[6], stp->sVerion[5], stp->sVerion[4]);	
	fprintf(stdout, "addr=%s\n", stp->sProjectAddr);
	fprintf(stdout, "%s", sVersion);
}
 
int
_tmain (int argc, char *argv[])
{
	const unsigned long loffsetdef = 0xc800;
	unsigned long loffset;
  char sfilename[256];
  char skey[256];
  char smaxno[256];
  char smode[256];
  char *str;
  unsigned short itemp;
  char cmode = 0;
  char **w =0;

  errno_t err;
  struct   STVERSION_CRC  *stdata;
  
  if (argc < 2)
    {
	  message_fail ();
    }
  memset (sfilename, 0, sizeof (sfilename));
  strncpy_s (sfilename, argv[1], sizeof (sfilename));
  if (argc > 2)
  {
	  loffset = strtol(argv[2],w,0 );
  }
  else
	  loffset = loffsetdef;

  if (loffset < 0x1000)
  {
	  fprintf(stdout, "%s", sVersion);
	  fprintf(stderr, "%s", "offset error\n");
	  fprintf(stderr, "%s", "Example:\n");
	  fprintf(stderr, "%s", " hexinfo2show  hexfilename  0xc800\n");
	  system("pause");
  }
  
  clhexfiledata.sttextfiledata.lsbuflen =
    line_2_buf (sfilename, clhexfiledata.sttextfiledata.sbuf,
		clhexfiledata.sttextfiledata.lbuflen);

  clhexfiledata.hex2formatbuf (clhexfiledata.sttextfiledata.sbuf,
			       (HexToBinData *) smaxno);
  stdata = (struct   STVERSION_CRC *)(clhexfiledata.stbindata.sbuf + loffset);
  filemessageout (sfilename, stdata); 
  system("pause");
  message_success ();

}




char
hextext2binbuf (struct STFILEDATA *spdata)
{
  return NULL;
}
