#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "global.h"



int readRecordFile(Record* rec) {

	FILE* fp = fopen("D:/record/record.txt", "r");
	if (!fp) {
		perror("文件打开失败");
		return -1;
	}

	int i = 0;
	while (i < QUEUE_SIZE &&
		   fscanf_s(fp, "%d %24s %24s %d %d %d %lf %lf %lf %lf %d %d %d",
					&rec[i].id, rec[i].name, MAX_NAME_LEN,
					rec[i].community, MAX_COMMUNITY_LEN,
					&rec[i].peopleNum, &rec[i].year,
					&rec[i].month, &rec[i].peakUsage,
					&rec[i].valleyUsage, &rec[i].totalUsage,
					&rec[i].price, &rec[i].isJoined,
					&rec[i].isListed, &rec[i].isCounted) == 13) {
		i++;
					}

	fclose(fp);
	return i;
}

void saveFile(Record* rec, int count)
{
	FILE* fp = fopen("D:\\record\\record.txt", "w");
	if (!fp) {
		perror("写文件失败！");
		exit(1);
	}

	for (int i = 0; i < count; ++i) {
		fprintf(fp, "%d %s %s %d %d %d %d %d %.2lf %.2lf %.2lf %.2lf %d\n",
			rec[i].id, rec[i].name, rec[i].community,
			rec[i].year, rec[i].month, rec[i].peopleNum,
			rec[i].isJoined, rec[i].isListed,
			rec[i].peakUsage, rec[i].valleyUsage,
			rec[i].totalUsage, rec[i].price,
			rec[i].isCounted);
	}

	fclose(fp);
}
