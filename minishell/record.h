#ifndef __RECORD_H__
#define __RECORD_H__

#define RECORD_PATH "./record.txt"

extern int InitRecord(void);
extern int RecordCommand(char *pcmdbuf);
extern int DeInitRecord(void);

#endif
