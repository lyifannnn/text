#include "head.h"
#include "record.h"

FILE *fp = NULL;

/********************************************************
 *函数名:InitRecord
 *参  数:
 *		缺省 void
 *返回值:
 *		成功返回0
 *		失败返回-1
 *******************************************************/
int InitRecord(void)
{
	fp = fopen(RECORD_PATH,"a");
	if(NULL == fp)
	{
		perror("fail to fopen");
		return -1;
	}

	return 0;
}

/********************************************************
 *函数名:RecordCommand
 *参  数:
 *		pcmdbuf 命令字符串首地址
 *返回值:
 *		成功返回0
 *		失败返回-1
 *******************************************************/
int RecordCommand(char *pcmdbuf)
{
	time_t t;
	struct tm *ptm = NULL;

	time(&t);
	ptm = localtime(&t);

	fprintf(fp,"[%04d-%02d-%02d %02d:%02d:%02d]%s\n",ptm->tm_year+1900,
			ptm->tm_mon+1,ptm->tm_mday,ptm->tm_hour,ptm->tm_min,ptm->tm_sec,pcmdbuf);
	fflush(fp);

	return 0;
}

/********************************************************
 *函数名:DeInitRecord
 *参  数:
 *		缺省 void
 *返回值:
 *		成功返回0
 *		失败返回-1
 *******************************************************/
int DeInitRecord(void)
{
	if(fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}

	return 0;
}




















