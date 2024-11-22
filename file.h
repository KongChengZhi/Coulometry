#ifndef _FILE
#define _FILE
#include "global.h"

/*从文件中加载住户信息*/
int readRecordFile(Record* rec);

/*在文件中保存住户信息*/
void saveFile(Record* rec, int count);

#endif