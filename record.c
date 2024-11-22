//
// Created by singsky on 24-11-19.
//

#include <stdio.h>
#include <string.h>
#include "record.h"
#include "global.h"
#include "menu.h"

//TODO 修改检验逻辑，禁止输入特殊字符 （预计使用ASCII码检验）
//TODO 回调
//TODO 加入已登记过的属性，统计整个小区用
/**
 *查找指定住户个人电费记录信息
 */
void findRecord() {
    printf("           按户号查找电费记录信息\n");
    do {
        printf("           输入户号：");
        scanf_s("%d", &id);
        if (id < MIN_RECORDS || id >= MAX_RECORDS+1) {
            printf("           请输入小于八位的ID\n");
        }
    } while( id < MIN_RECORDS || id >= MAX_RECORDS+1);
    //获得对应用户在队列中的序号
    int serial = findRecordByID(rec, id);
    int i = serial;
    if(i == -1) {
        printf("           住户信息中未找到该住户\n");
    } else {
        int months = 0;
        double price = 0.0;
        double total = 0.0;
        double valley = 0.0;
        double peak = 0.0;
        //   printf("           1为参加、已扩容，0为未扩容、不参加\n");
        printf("           找到相关住户信息\n");
        displaySame(serial);
        displayDifferentTitle();
        while (i <= count) {
            if (rec[i].id == id) {
                displayDifferent(i);
                peak += rec[i].peakUsage;
                valley += rec[i].valleyUsage;
                total += rec[i].totalUsage;
                price += rec[i].price;
                months++;
                i++;
            }
            else {
                i++;
            }
        }
        printf("%-16s", "          总");
        printf("          ");
        printf("%-16lf", peak);
        printf("%-16lf", valley);
        printf("%-16lf", total);
        printf("%-16lf", price);
        printf("\n");
        printf("%-16s", "          月均");
        printf("          ");
        printf("%-16lf", (peak / months));
        printf("%-16lf", (valley / months));
        printf("%-16lf", (total / months));
        printf("%-16lf", (price / months));
        printf("\n");
    }
    id = 0;
}


/**
 * 从记录列表中搜索指定用户的列表
 * TODO 修改查找逻辑 是否定义为全局变量
 */

/*通过户号查找用户*/
int findRecordByID(Record* rec, int id) {
    for (int i = 0; i < count; i++) {
        if (rec[i].id == id) {
            return i;
        }
    }  // Warn
    return -1; // 未找到时返回 -1 而不是 0
}

/*通过户号和日期查找*/
int findRecordByIDDate(Record* rec, int id, int year, int month) {
    int i = 0;
    while (i <= count) {
        if ((rec[i].id == id) && (rec[i].year == year) && (rec[i].month == month)) {
            return i;
        }
        i++;
    }
    return -1;
}

/*通过小区名查找*/
int findRecordByCommunityName(Record* rec, char* com) {
    int i = 0;
    while (i <= count) {
        if ((strcmp(rec[i].community, com) == 0) && !rec[i].isCounted) {
            return i;
        }
        i++;
    }
    return -1;
}
/**
 * 标题展示
 */
void displaySameTitle() {
    printf("%-8s", "          户号");
    printf("%-8s", "      户名");
    printf("%-8s", "    小区");
    printf("%-8s", "  人数");
    printf("%-16s", "是否参与峰谷计价");
    printf("%-16s", " 该小区是否已扩容");
    printf("\n");
}

void displayDifferentTitle() {
    printf("%-8s", "          年份");
    printf("%-8s", "    月份    ");
    printf("%-16s", "峰时电量");
    printf("%-16s", "谷时电量");
    printf("%-16s", "总电量");
    printf("%-16s", "电费");
    printf("\n");
}

/**
 * 展示信息
 */
void displaySame(int n) {
    printf("          ");
    printf("%08d", rec[n].id);
    printf("  %-8s", rec[n].name);
    printf("%-8s", rec[n].community);
    printf("%-10d", rec[n].peopleNum);
    printf("%-20d", rec[n].isJoined);
    printf("%-20d", rec[n].isListed);
    printf("\n");
}

void displayDifferent(int n) {
    printf("          ");
    printf("%-8d", rec[n].year);
    printf("%-8d", rec[n].month);
    printf("%-16lf", rec[n].peakUsage);
    printf("%-16lf", rec[n].valleyUsage);
    printf("%-16lf", rec[n].totalUsage);
    printf("%-16lf", rec[n].price);
    printf("\n");
}

/*按日期显示小区信息*/;
void displayCommunityByDate() {
    char com[MAX_COMMUNITY_LEN] = { 0 };
    printf("           输入小区名：");
    scanf_s("%s", com, MAX_COMMUNITY_LEN);
    change = findRecordByCommunityName(rec, com);
    if (change) {
        printf("           按日期显示小区电费记录信息\n");
        printf("           1为已扩容，0为未扩容\n");
        printf("           小区名：是否扩容：\n");
        printf("           ");
        printf("%-8s", rec[change].community);
        printf("%-8d", rec[change].isListed);
        printf("\n");
        printf("           年份:   月份：  峰时：          谷时：          总用电量：      电费：\n");
        int n = change;
        while (n != -1) {
            int i = n;
            double price = 0.0;
            double total = 0.0;
            double valley = 0.0;
            double peak = 0.0;
            while (i <= count) {
                if ((strcmp(rec[i].community, com) == 0) && rec[n].year == rec[i].year && rec[n].month == rec[i].month && !rec[n].isCounted) {
                    //TODO 状态只能存一次
                    rec[i].isCounted = 1;
                    peak += rec[i].peakUsage;
                    valley += rec[i].valleyUsage;
                    total += rec[i].totalUsage;
                    price += rec[i].price;
                    i++;
                } else {
                    i++;
                }
            }
            printf("           ");
            printf("%-8d", rec[n].year);
            printf("%-8d", rec[n].month);
            printf("%-16lf", peak);
            printf("%-16lf", valley);
            printf("%-16lf", total);
            printf("%-16lf", price);
            printf("\n");
            n = findRecordByCommunityName(rec, com);
        }
    } else {
        printf("          住户信息中未找到该小区\n");
    }
    change = -1;
    id = 0;
}

/*按户号显示小区信息*/
void displayCommunityByID() {
    char com[MAX_COMMUNITY_LEN] = { 0 };
    printf("           输入小区名：");
    scanf_s("%s", com, MAX_COMMUNITY_LEN);
    change = findRecordByCommunityName(rec, com);
    if (change != -1) {
        printf("           按日期显示小区电费记录信息\n");
        printf("           1为已扩容，0为未扩容\n");
        printf("           小区名：是否扩容：\n");
        printf("           ");
        printf("%-8s", rec[change].community);
        printf("%-8d", rec[change].isListed);
        printf("\n");
        printf("           户号:   户名：  峰时：          谷时：          总用电量：      电费：\n");
        int n = change;
        while (n != -1) {
            int i = n;
            id = rec[n].id;
            double price = 0.0;
            double total = 0.0;
            double valley = 0.0;
            double peak = 0.0;
            while (i <= count) {
                if (id == rec[i].id && !rec[i].isCounted) {
                    rec[i].isCounted = 1;
                    peak += rec[i].peakUsage;
                    valley += rec[i].valleyUsage;
                    total += rec[i].totalUsage;
                    price += rec[i].price;
                    i++;
                } else {
                    i++;
                }
            }
            printf("           ");
            printf("%08d", rec[n].id);
            printf("%-8s", rec[n].name);
            printf("%-16lf", peak);
            printf("%-16lf", valley);
            printf("%-16lf", total);
            printf("%-16lf", price);
            printf("\n");
            n = findRecordByCommunityName(rec, com);
        }
    } else {
        printf("           住户信息中未找到该小区\n");
    }
    change = -1;
    id = 0;
}


/*显示未扩容小区名单*/
void displayUnlisted() {
    int n = 1;
    int i = 1;
    if (findUnlisted()) {
        printf("             未扩容小区名单：\n");
        while (n <= count) {
            if (findRecordByCommunityName(rec, rec[n].community) != -1 && rec[n].isListed == 0) {
                printf("%-8s\n", rec[n].community);
                i = n;
                while (i) {
                    i = findRecordByCommunityName(rec, rec[n].community);
                }
                n++;
            } else {
                n++;
            }
        }
    } else {
        printf("             住户信息中未找到未扩容小区\n");
    }
}

/*显示已扩容小区名单*/
void displayListed() {
    int n = 1;
    int i = 1;
    if (findUnlisted()) {
        printf("             已扩容小区名单：\n");
        while (n <= count) {
            if (findRecordByCommunityName(rec, rec[n].community) != -1 && rec[n].isListed == 1) {
                printf("%-8s\n", rec[n].community);
                i = n;
                while (i) {
                    i = findRecordByCommunityName(rec, rec[n].community);
                }
                n++;
            } else {
                n++;
            }
        }
    } else {
        printf("             住户信息中未找到已扩容小区\n");
    }
}

/*急需扩容小区名单*/
void displayUrgent() {
    /*由于a,b相除得到的结果是一个小数，所以a,b定义为double而不是int*/
    int i = 1;
    int x = 0;
    double b = 0.0;
    double a = 0.0;
    int n = findUnlisted();
    int c = n;
    if (n) {
        printf("             急需扩容小区名单：\n");
        while (n) {
            while (c) {
                double all = 0.0;
                i = c;
                id = rec[c].id;
                while (i <= count) {
                    if (id == rec[i].id && !rec[i].isCounted) {
                        rec[i].isCounted = 1;
                        all += rec[i].totalUsage;
                        i++;
                        x++;
                    } else {
                        i++;
                    }
                }
                if ((all / x) >= 330) {
                    a++;
                    b++;
                } else {
                    b++;
                }
                c = findRecordByCommunityName(rec, rec[n].community);
            }
            if ((a / b) >= 0.6) {
                printf("%-8s\n", rec[n].community);
            }
            a = 0.0;
            b = 0.0;
            x = 0;
            n = findUnlisted();
            c = findRecordByCommunityName(rec, rec[n].community);
        }
    }
    else
    {
        printf("             住户信息中未找到未扩容小区\n");
    }
}


/**
 *修改住户信息
 */

/*修改某月用户信息，总入口*/
void modifyRecord() {
    int year = 0;
    int month = 0;
    do {
        printf("             输入户号：");
        scanf_s("%d", &id);
        if (id < MIN_RECORDS || id >= MAX_RECORDS+1) {
            printf("             请输入小于八位的ID\n");
        }
    } while (id < MIN_RECORDS || id >= MAX_RECORDS+1);
    do {
        printf("             输入年份：");
        scanf_s("%d", &year);
        if (year < 2000 || year > 2024) {
            printf("             请输入2000至2024之间的年份\n");
        }
    } while (year < 2000 || year > 2024);
    do {
        printf("             输入月份：");
        scanf_s("%d", &month);
        if (month < 1 || month > 12) {
            printf("             请输入正确的月份\n");
        }
    } while (month < 1 || month > 12);
    change = findRecordByIDDate(rec, id, year, month);
    if (change != -1) {
        printf("             找到以下住户信息 \n");
        displaySameTitle();
        displaySame(change);
        displayDifferentTitle();
        displayDifferent(change);
        askfg();
        change = -1;
        printf("             修改成功\n");
    }
    else {
        printf("            住户信息中未找到该住户\n");
    }
}

/*添加住户信息*/
void addRecord() {
	printf("            添加住户信息\n");
	printf("            正在录入住户信息……\n");
    do {
        printf("             输入户号：");
        scanf_s("%d", &id);
        if (id < MIN_RECORDS || id >= MAX_RECORDS+1) {
            printf("             请输入小于八位的ID\n");
        }
    } while (id < MIN_RECORDS || id >= MAX_RECORDS+1);
	change = findRecordByID(rec, rec[count].id);     /*寻找是否已有相同的户号*/
	if (change)
	{
		printf("            已有该用户信息：\n");             /*输出相同的信息*/
		displaySameTitle();
		displaySame(change);
		memcpy(rec[count].name, rec[change].name, QUEUE_SIZE);
		memcpy(rec[count].community, rec[change].community, QUEUE_SIZE);
		rec[count].peopleNum = rec[change].peopleNum;
		rec[count].isJoined = rec[change].isJoined;
		rec[count].isListed = rec[change].isListed;
		addTOU();
		rec[count].totalUsage = rec[count].peakUsage + rec[count].valleyUsage;
		rec[count].price = calculateBill(rec[count].peakUsage, rec[count].valleyUsage, rec[count].totalUsage, rec[count].peopleNum, rec[change].isJoined);
		change = 0;                                /*把change改为0*/
	}
	else
	{
		printf("            户名：");
		scanf_s("%s", rec[count].name, QUEUE_SIZE);
		printf("            小区：");
		scanf_s("%s", rec[count].community, QUEUE_SIZE);
		addTOU();
		printf("            人数：");
		scanf_s("%d", &rec[count].peopleNum);
		do
		{
			printf("            是否参加峰谷计费?\n");
			printf("            1为参加，0为不参加\n");
			printf("            ");
			scanf_s("%d", &rec[count].isJoined);
			if (rec[count].isJoined < 0 || rec[count].isJoined > 1)
			{
				printf("            请输入0或1\n");
			}
		} while (0 > rec[count].isJoined || 1 < rec[count].isJoined);
		int n = findRecordByCommunityName(rec, rec[count].community);
		if (n)
		{
			rec[count].isListed = rec[n].isListed;
			rec[count].totalUsage = rec[count].peakUsage + rec[count].valleyUsage;
			rec[count].price = calculateBill(rec[count].peakUsage, rec[count].valleyUsage, rec[count].totalUsage, rec[count].peopleNum, rec[count].isJoined);
		}
		else
		{
			do
			{
				printf("            该小区是否扩容?\n");
				printf("            1为已扩容，0为未扩容\n");
				printf("            ");
				scanf_s("%d", &rec[count].isListed);
				if (0 >rec[count].isListed || 1 < rec[count].isListed)
				{
					printf("            请输入0或1\n");
				}
			} while (0 > rec[count].isListed || 1 < rec[count].isListed);
			rec[count].totalUsage = rec[count].peakUsage + rec[count].valleyUsage;
			rec[count].price = calculateBill(rec[count].peakUsage, rec[count].valleyUsage, rec[count].totalUsage, rec[count].peopleNum, rec[count].isJoined);
		}
	}
	printf("           成功添加住户！\n\n");
}
/*输入年月峰谷信息*/
void addTOU() {
    do {
        printf("            年份：");
        scanf_s("%d", &rec[count].year);
        if (rec[count].year < 2000 || rec[count].year > 2024) {
            printf("            请输入2000至2024之间的年份\n");
        }
    } while (rec[count].year < 2000 || rec[count].year > 2024);
    do {
        printf("            月份：");
        scanf_s("%d", &rec[count].month);
        if (1 > rec[count].month || rec[count].month > 12) {
            printf("            请输入正确的月份\n");
        }
    } while (1 > rec[count].month || rec[count].month > 12);
    printf("            峰时电量：");
    scanf_s("%lf", &rec[count].peakUsage);
    printf("            谷时电量：");
    scanf_s("%lf", &rec[count].valleyUsage);
  // TODO 根据实际需求决定是否添加"是否统计过"的标签  rec[count].count = 1;
}

/*删除住户信息*/
void removeRecord() {
    int id = 0;
    int year = 0;
    int month = 0;
    printf("             输入户号和日期查找要删除的电费记录信息 \n");
    do {
        printf("             输入户号：");
        scanf_s("%d", &id);
        if (id < MIN_RECORDS || id >= MAX_RECORDS+1) {
            printf("             请输入小于八位的ID\n");
        }
    } while (id < MIN_RECORDS || id >= MAX_RECORDS+1);
    do {
        printf("             输入年份：");
        scanf_s("%d", &year);
        if (year < 2000 || year > 2024) {
            printf("             请输入2000至2024之间的年份\n");
        }
    } while (year < 2000 || year > 2024);
    do {
        printf("             输入月份：");
        scanf_s("%d", &month);
        if (month < 1 || month > 12) {
            printf("             请输入正确的月份\n");
        }
    } while (month < 1 || month > 12);
    int n = findRecordByIDDate(rec, id, year, month);
    if (n != -1) {
        while (n < count) {
            rec[n] = rec[++n];            /*用后一个数组覆盖前一个数组*/
        }
        count--;
        printf("\n            已删除该条信息\n\n");
    }
    else {
        printf("            住户信息中未找到该住户\n");
    }
}


/*更改峰时电量*/
void changePeak() {
    printf("              峰时电量：");
    scanf_s("%lf", &rec[change].peakUsage);
    rec[count].totalUsage = rec[count].peakUsage + rec[count].valleyUsage;
    rec[count].price = calculateBill(rec[count].peakUsage, rec[count].valleyUsage, rec[count].totalUsage, rec[count].peopleNum, rec[count].isJoined);
}

/*更改谷时电量*/
void changeValley() {
    printf("              谷时电量：");
    scanf_s("%lf", &rec[change].peakUsage);
    rec[count].totalUsage = rec[count].peakUsage + rec[count].valleyUsage;
    rec[count].price = calculateBill(rec[count].peakUsage, rec[count].valleyUsage, rec[count].totalUsage, rec[count].peopleNum, rec[count].isJoined);
}

/*修改是否参加峰谷计费*/
void modifyIsJoined() {
    do {
        printf("             输入户号：");
        scanf_s("%d", &id);
        if (id < MIN_RECORDS || id >= MAX_RECORDS+1) {
            printf("             请输入小于八位的ID\n");
        }
    } while (id < MIN_RECORDS || id >= MAX_RECORDS+1);
    change = findRecordByID(rec, id);
    if (!change) {
        printf("            住户信息中未找到该住户\n");
    } else {
        do {
            printf("             1为参加，0为不参加\n");
            printf("             是否参加峰谷计费：\n ");
            scanf_s("%d", &rec[change].isJoined);
            if (0 > rec[change].isJoined || 1 <  rec[change].isJoined) {
                printf("             请输入0或1\n");
            }
        } while (0 > rec[change].isJoined || 1 < rec[change].isJoined);
        int i = change;
        while (i <= count) {
            if (rec[i].id == id) {
                rec[i].price = calculateBill(rec[i].peakUsage, rec[i].valleyUsage, rec[i].totalUsage, rec[i].peopleNum, rec[change].isJoined);
                i++;
            }
            else {
                i++;
            }
        }
        printf("             修改成功\n");
    }
}

// TODO 将根据ID查找户号封装为函数
/*修改住户人数*/
void modifyPeopleNum() {
    do {
        printf("             输入户号：");
        scanf_s("%d", &id);
        if (id < MIN_RECORDS || id >= MAX_RECORDS+1) {
            printf("             请输入小于八位的ID\n");
        }
    } while (id < MIN_RECORDS || id >= MAX_RECORDS+1);
    change = findRecordByID(rec, id);
    if (!change) {
        printf("            住户信息中未找到该住户\n");
    } else
    {
        printf("             请输入住户人数：");
        scanf_s("%d", &rec[change].peopleNum);
        int i = change;
        while (i <= count)
        {
            if (rec[i].id == id)
            {
                rec[i].price = calculateBill(rec[i].peakUsage, rec[i].valleyUsage, rec[i].totalUsage, rec[i].peopleNum, rec[change].isJoined);
                i++;
            }
            else
            {
                i++;
            }
        }
        printf("             修改成功\n");
    }
}

/*修改住户所在小区*/
void modifyCommunityName() {
    do {
        printf("             输入户号：");
        scanf_s("%d", &id);
        if (id < MIN_RECORDS || id >= MAX_RECORDS+1) {
            printf("             请输入小于八位的ID\n");
        }
    } while (id < MIN_RECORDS || id >= MAX_RECORDS+1);
    change = findRecordByID(rec, id);
    if (!change) {
        printf("            住户信息中未找到该住户\n");
    } else {
        printf("             请输入小区名：");
        int i = change;
        while (i <= count) {
            if (rec[i].id == id) {
                scanf_s("%s", &rec[i].community, QUEUE_SIZE);
                i++;
            } else {
                i++;
            }
        }
        printf("             修改成功\n");
    }
}

/*修改小区是否扩容*/
void modifyIsListed() {
    char com[MAX_COMMUNITY_LEN] = { 0 };
    printf("             输入小区名：");
    scanf_s("%s", com, MAX_COMMUNITY_LEN);
    change = findRecordByCommunityName(rec, com);
    int n = change;
    if (change) {
        printf("             小区名：是否扩容：\n");
        printf(" %-8s", rec[change].community);
        printf("%-8d", rec[change].isListed);
        printf("\n");
        do {
            printf("             1为已扩容，0为未扩容\n");
            printf("             是否扩容：\n ");
            printf("             ");
            scanf_s("%d", &rec[change].isListed);
            if (0 > rec[change].isListed || 1 < rec[change].isListed) {
                printf("             请输入0或1\n");
            }
        } while (0 >rec[change].isListed || 1 < rec[change].isListed);
        while (n) {
            rec[n].isListed = rec[count].isListed;
            n = findRecordByCommunityName(rec, rec[n].community);
        }
        n = change;
        while (n < count) n++;
        printf("             修改成功\n");
    } else {
        printf("            住户信息中未找到该小区\n");
    }
    change = 0;
    id = 0;
}


/**
 *扩容管理
 */
/*查找是否有小区扩容*/
int findListed() {
    int i = 1;
    while (i <= count) {
        if (rec[i].isListed == 1 && !rec[i].isCounted) {
            return i;
        }
        i++;
    }
    return 0;
}

/*查找是否有小区扩容*/
int findUnlisted() {
    int i = 1;
    while (i <= count) {
        if (rec[i].isListed == 0 && !rec[i].isCounted) {
            return i;
        }
        i++;
    }
    return 0;
}

/**
 * 电费计算
 */
/*计算总电费*/
double calculateBill(double peak, double valley, double total, int peopleNum, int isJoined) {
	switch (isJoined) {
	case 0: return originCalculateBill(total, peopleNum);
	case 1: return TOUCalculateBill(peak, valley, total, peopleNum);
    default: ;
    }
	return 0;
}

// TODO 将魔法数改为常量
/*计算不参与峰谷的电费*/
double originCalculateBill(double total, int peopleNum) {
	if (peopleNum >= 0 && peopleNum <= 4 && total >= 0 && total <= 231) return(total * 0.5238);
	if (peopleNum >= 0 && peopleNum <= 4 && total > 231) return ((total - 230) * 0.5783) + 120.474;
	if (peopleNum >= 0 && peopleNum <= 4 && total > 400) return ((total - 400) * 0.8288) + 218.785;
	if (peopleNum >= 5 && peopleNum <= 6 && total >= 0 && total <= 331) return (total * 0.5238);
	if (peopleNum >= 5 && peopleNum <= 6 && total > 331) return ((total - 330) * 0.5783) + 172.854;
	if (peopleNum >= 5 && peopleNum <= 6 && total > 500) return ((total - 500) * 0.8288) + 271.165;
	if (peopleNum >= 7 && total >= 0 && total <= 431) return (total * 0.5238);
	if (peopleNum >= 7 && total > 431 && total <= 600) return ((total - 430) * 0.5783) + 225.234;
	if (peopleNum >= 7 && total > 600) return ((total - 600) * 0.8288) + 323.545;
	return 0;
}

/*计算峰谷电费*/
double TOUCalculateBill(double peak, double valley, double total, int peopleNum) {
	if (peopleNum >= 0 && peopleNum <= 4 && total >= 0 && total <= 231) return (0.5583 * peak) + (0.3583 * valley);
    if (peopleNum >= 0 && peopleNum <= 4 && total > 231 && total <= 400) return (0.5583 * peak) + (0.3583 * valley) + ((total - 230) * 0.05);
    if (peopleNum >= 0 && peopleNum <= 4 && total > 400) return (0.5583 * peak) + (0.3583 * valley) + ((total - 400) * 0.3) + 8.5;
    if (peopleNum >= 5 && peopleNum <= 6 && total >= 0 && total <= 231) return (0.5583 * peak) + (0.3583 * valley);
    if (peopleNum >= 5 && peopleNum <= 6 && total > 331 && total <= 500) return (0.5583 * peak) + (0.3583 * valley) + ((total - 330) * 0.05);
    if (peopleNum >= 5 && peopleNum <= 6 && total > 500) return (0.5583 * peak) + (0.3583 * valley) + ((total - 500) * 0.3) + 8.5;
    if (peopleNum >= 7 && total >= 0 && total <= 431 ) return (0.5583 * peak) + (0.3583 * valley);
    if (peopleNum >= 7 && total > 431 && total <= 600) return (0.5583 * peak) + (0.3583 * valley) + ((total - 430) * 0.05);
    if (peopleNum >= 7 && total > 600) return (0.5583 * peak) + (0.3583 * valley) + ((total - 600) * 0.3) + 8.5;
	return 0;
}



