#include "head.h"
#include "terminal.h"
#include "record.h"

int main(void)
{
	char command[1024] = {0};
	char *parg[10] = {NULL};
	int curcmdlen = 0;
	
	InitRecord();

	while(1)
	{
		ShowTerminal();
		GetCommand(command,1024);
		if(!strcmp(command,"exit"))
		{
			break;
		}
		RecordCommand(command);
		curcmdlen = SplitCommand(command,parg,10);
		ExecCommand(parg,curcmdlen);
	}
	

	return 0;
}
