#include"head.h"
#include "command.h"
/*********************************
*xianshi terminal
********************************/
int ShowTerminal(void)
{
	char tmpbuff[1024] = {0};
	char *ptmp = NULL;
	getcwd(tmpbuff,sizeof(tmpbuff));
	/*获得路径中最后一段目录文件名*/
	ptmp = tmpbuff + strlen(tmpbuff);

	while(*ptmp != '/')
	{
		--ptmp;
	}

	if(strcmp(tmpbuff,"/"))
	{
		++ptmp;
	}

	printf("[linux@linux:%s]:",ptmp);

	return 0;
}

/********************************************************
 *函数名:GetCommand
 *参  数:
 *		pcmdbuf:存放命令空间首地址
 *		maxlen:最大存放字符串个数
 *返回值:
 *		成功返回0
 *		失败返回-1
 *******************************************************/
int GetCommand(char *pcmdbuf,int maxlen)
{
	fgets(pcmdbuf,maxlen,stdin);
	pcmdbuf[strlen(pcmdbuf)-1] = '\0';
	return 0;
}

/********************************************************
 *函数名:SplitCommand
 *参  数:
 *		pcmdbuf:存放命令空间首地址
 *		parg:存放解析后字符串地址的指针数组
 *		maxlen:最多解析命令的个数
 *返回值:
 *		成功返回解析到命令的个数
 *		失败返回-1
 *******************************************************/
int SplitCommand(char *pcmdbuf,char **parg,int maxlen)
{
	char *ptmp = NULL;
	int cnt = 0;

	ptmp = pcmdbuf;

		parg[cnt] = strtok(ptmp," ");
		cnt++;
		while(1)
		{
			parg[cnt] = strtok(NULL," ");
			if(NULL == parg[cnt])
			{
				break;
			}
			cnt++;
		}
	return cnt;
}

/********************************************************
 *函数名:ExecCommand
 *参  数:
 *		parg:存放解析后字符串地址的指针数组
 *		curlen:命令的个数
 *返回值:
 *		成功返回0
 *		失败返回-1
 *******************************************************/
int ExecCommand(char **parg,int curlen)
{
	if(!strcmp(parg[0],"ls"))
	{
		MyLs(curlen,parg);
	}else if(!strcmp(parg[0],"cd"))
	{
		MyCd(curlen,parg);
	}else if(!strcmp(parg[0],"touch"))
	{
		MyTouch(curlen,parg);
	}else if(!strcmp(parg[0],"rm"))
	{
		MyRm(curlen,parg);
	}else if(!strcmp(parg[0],"mkdir"))
	{
		MyMkdir(curlen,parg);
	}else if(!strcmp(parg[0],"rmdir"))
	{
		MyRmdir(curlen,parg);
	}else if(!strcmp(parg[0],"cp"))
	{
		MyCp(curlen,parg);
	}else if(!strcmp(parg[0],"mv"))
	{
		MyMv(curlen,parg);
	}else if(!strcmp(parg[0],"pwd"))
	{
		MyPwd(curlen,parg);
	}else if(!strcmp(parg[0],"cat"))
	{
		MyCat(curlen,parg);
	}else if(!strcmp(parg[0],"chmod"))
	{
		MyChmod(curlen,parg);
	}else if(!strcmp(parg[0],"ln"))
	{
		MyLn(curlen,parg);
	}

	return 0;
}
