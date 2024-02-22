#ifndef __TERMINAL_H__
#define __TERMINAL_H__

extern int ShowTerminal(void); 
extern int GetCommand(char *pcmdbuf,int maxlen);
extern int SplitCommand(char *pcmdbuf,char **parg,int maxlen);
extern int ExecCommand(char **parg,int curlen);


#endif
