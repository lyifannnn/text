#include"head.h"

/********************************************************
 *函数名:MyCd
 *参  数:
 *		argc:命令的个数
 *		argv:存放解析后字符串地址的指针数组
 *返回值:
 *		成功返回0
 *		失败返回-1 
 *******************************************************/
int MyCd(int argc,char *argv[])
{
	if(argv[1] != NULL)
	{
		chdir(argv[1]);
	}

	return 0;
}
int MyLs(int argc,char *argv[])
{
	DIR *dp = NULL;
	struct dirent *pp = NULL;
	struct passwd *pwd = NULL;
	struct group *grp = NULL;
	struct stat buf;
	struct tm *ptm = NULL;
	char tmpbuff[1024] = {0};
	int ret = 0;
	char *mon[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug",
	"Sep","Oct","Nov","Dec"};

	dp = opendir(".");

	if(NULL == dp)
	{
		perror("fail to opendir");
		return -1;
	}

	if(1 == argc)
	{
		while((pp = readdir(dp)) != NULL)
		{
			if('.' == *pp->d_name)
			{
				continue;
			}

			printf("%-15s",pp->d_name);
			++ret;
			if(0 == ret % 5)
			{
				putchar('\n');
			}
		}
		if(ret != 5)
		{
			putchar('\n');
		}
	}

	if(2 == argc && !strcmp(argv[1],"-a"))
	{
		while((pp = readdir(dp)) != NULL)
		{
			printf("%-15s",pp->d_name);
			++ret;
			if(0 == ret % 5)
			{
				putchar('\n');
			}
		}
		if(ret != 5)
		{
			putchar('\n');
		}
	}
	
	if(2 == argc && !strcmp(argv[1],"-l"))
	{
		while(1)
		{
			pp = readdir(dp);

			if(NULL == pp)
			{
				break;
			}

			if('.' == pp->d_name[0])
			{
				continue;
			}
			
			ret = lstat(pp->d_name,&buf);

			if(-1 == ret)
			{
				perror("fail to stat");
				return -1;
			}

			switch(buf.st_mode & S_IFMT)
			{
				case S_IFBLK:putchar('b');break;
				case S_IFCHR:putchar('c');break;
				case S_IFDIR:putchar('d');break;
				case S_IFIFO:putchar('p');break;
				case S_IFLNK:putchar('l');break;
				case S_IFREG:putchar('-');break;
				case S_IFSOCK:putchar('s');break;
			}

			buf.st_mode & S_IRUSR ? putchar('r'):putchar('-');
			buf.st_mode & S_IWUSR ? putchar('w'):putchar('-');
			buf.st_mode & S_IXUSR ? putchar('x'):putchar('-');


			buf.st_mode & S_IRGRP ? putchar('r'):putchar('-');
			buf.st_mode & S_IWGRP ? putchar('w'):putchar('-');
			buf.st_mode & S_IXGRP ? putchar('x'):putchar('-');
			
			buf.st_mode & S_IROTH ? putchar('r'):putchar('-');
			buf.st_mode & S_IWOTH ? putchar('w'):putchar('-');
			buf.st_mode & S_IXOTH ? putchar('x'):putchar('-');

			printf(" %ld",buf.st_nlink);

			pwd = getpwuid(buf.st_uid);
			if(NULL == pwd)
			{
				printf(" %d",buf.st_uid);
			}else
			{
				printf(" %s",pwd->pw_name);
			}

			grp = getgrgid(buf.st_gid);
			if(NULL == grp)
			{
				printf(" %d",buf.st_gid);
			}else
			{
				printf(" %s",grp->gr_name);
			}

			printf(" %5ld",buf.st_size);

			ptm = localtime(&buf.st_mtime);

			printf(" %s  %02d %02d:%02d",mon[ptm->tm_mon],ptm->tm_mday,ptm->tm_hour,ptm->tm_min);
			
			printf(" %s",pp->d_name);

			if(S_ISLNK(buf.st_mode))
			{
				readlink(pp->d_name,tmpbuff,sizeof(tmpbuff));
				printf(" -> %s",tmpbuff);
			}
			putchar('\n');
		}
	}

	closedir(dp);

	return 0;
}

int MyTouch(int argc,char *argv[])
{
	FILE *p = NULL;
	int i = 0;
	for(i = 1;i < argc;++i)
	{
		p = fopen(argv[i],"a");
		fclose(p);
	}
	return 0;
}

int MyRm(int argc,char *argv[])
{
	int i = 0;
	for(i = 1;i < argc;++i)
	{
		remove(argv[i]);
	}
	return 0;
}

int MyMkdir(int argc,char *argv[])
{
	int i = 0;
	for(i = 1;i < argc;++i)
	{
		mkdir(argv[i],0777);
	}

	return 0;
}

int MyRmdir(int argc,char *argv[])
{
	int i = 0;
	for(i = 1;i < argc;++i)
	{
		rmdir(argv[i]);
	}

	return 0;
}

int MyCp(int argc,char *argv[])
{
	FILE *p = NULL;
	FILE *q = NULL;
	char ch[4096] = {0};

	p = fopen(argv[1],"r");
	q = fopen(argv[2],"a");

	while(1)
	{
		if(NULL == fgets(ch,sizeof(ch),p))
		{
			break;
		}

		fputs(ch,q);
	}

	fclose(p);
	fclose(q);

	return 0;
}

int MyMv(int argc,char *argv[])
{
	if(0 != rename(argv[1],argv[2]))
	{
		perror("Error");
		return -1;
	}

	return 0;
}

int MyPwd(int argc,char *argv[])
{
	char tmpbuff[4096] = {0};

	getcwd(tmpbuff,sizeof(tmpbuff));
	printf("%s\n",tmpbuff);

	return 0;
}

int MyCat(int argc,char *argv[])
{
	FILE *fp = NULL;
	fp = fopen(argv[1],"r");
	char tmpbuff[4096] = {0};

	if(NULL == fp)
	{
		perror("fail to fopen");
		return 0;
	}

	while(NULL != fgets(tmpbuff,sizeof(tmpbuff),fp))
	{
		printf("%s",tmpbuff);
	}

	fclose(fp);

	return 0;
}

int MyChmod(int argc,char *argv[])
{
	char *fp = NULL;
	char *mode_str = NULL;
	mode_t mode = 0;

	fp = argv[1];
	mode_str = argv[2];

	mode = strtol(mode_str,NULL,8);
	
	chmod(fp,mode);

	return 0;
}

int MyLn(int argc,char *argv[])
{

	link(argv[1],argv[2]);

	return 0;
}

