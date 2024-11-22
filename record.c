//
// Created by singsky on 24-11-19.
//

#include <stdio.h>
#include <string.h>
#include "record.h"
#include "global.h"
#include "menu.h"

//TODO �޸ļ����߼�����ֹ���������ַ� ��Ԥ��ʹ��ASCII����飩
//TODO �ص�
//TODO �����ѵǼǹ������ԣ�ͳ������С����
/**
 *����ָ��ס�����˵�Ѽ�¼��Ϣ
 */
void findRecord() {
    printf("           �����Ų��ҵ�Ѽ�¼��Ϣ\n");
    do {
        printf("           ���뻧�ţ�");
        scanf_s("%d", &id);
        if (id < MIN_RECORDS || id >= MAX_RECORDS+1) {
            printf("           ������С�ڰ�λ��ID\n");
        }
    } while( id < MIN_RECORDS || id >= MAX_RECORDS+1);
    //��ö�Ӧ�û��ڶ����е����
    int serial = findRecordByID(rec, id);
    int i = serial;
    if(i == -1) {
        printf("           ס����Ϣ��δ�ҵ���ס��\n");
    } else {
        int months = 0;
        double price = 0.0;
        double total = 0.0;
        double valley = 0.0;
        double peak = 0.0;
        //   printf("           1Ϊ�μӡ������ݣ�0Ϊδ���ݡ����μ�\n");
        printf("           �ҵ����ס����Ϣ\n");
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
        printf("%-16s", "          ��");
        printf("          ");
        printf("%-16lf", peak);
        printf("%-16lf", valley);
        printf("%-16lf", total);
        printf("%-16lf", price);
        printf("\n");
        printf("%-16s", "          �¾�");
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
 * �Ӽ�¼�б�������ָ���û����б�
 * TODO �޸Ĳ����߼� �Ƿ���Ϊȫ�ֱ���
 */

/*ͨ�����Ų����û�*/
int findRecordByID(Record* rec, int id) {
    for (int i = 0; i < count; i++) {
        if (rec[i].id == id) {
            return i;
        }
    }  // Warn
    return -1; // δ�ҵ�ʱ���� -1 ������ 0
}

/*ͨ�����ź����ڲ���*/
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

/*ͨ��С��������*/
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
 * ����չʾ
 */
void displaySameTitle() {
    printf("%-8s", "          ����");
    printf("%-8s", "      ����");
    printf("%-8s", "    С��");
    printf("%-8s", "  ����");
    printf("%-16s", "�Ƿ�����ȼƼ�");
    printf("%-16s", " ��С���Ƿ�������");
    printf("\n");
}

void displayDifferentTitle() {
    printf("%-8s", "          ���");
    printf("%-8s", "    �·�    ");
    printf("%-16s", "��ʱ����");
    printf("%-16s", "��ʱ����");
    printf("%-16s", "�ܵ���");
    printf("%-16s", "���");
    printf("\n");
}

/**
 * չʾ��Ϣ
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

/*��������ʾС����Ϣ*/;
void displayCommunityByDate() {
    char com[MAX_COMMUNITY_LEN] = { 0 };
    printf("           ����С������");
    scanf_s("%s", com, MAX_COMMUNITY_LEN);
    change = findRecordByCommunityName(rec, com);
    if (change) {
        printf("           ��������ʾС����Ѽ�¼��Ϣ\n");
        printf("           1Ϊ�����ݣ�0Ϊδ����\n");
        printf("           С�������Ƿ����ݣ�\n");
        printf("           ");
        printf("%-8s", rec[change].community);
        printf("%-8d", rec[change].isListed);
        printf("\n");
        printf("           ���:   �·ݣ�  ��ʱ��          ��ʱ��          ���õ�����      ��ѣ�\n");
        int n = change;
        while (n != -1) {
            int i = n;
            double price = 0.0;
            double total = 0.0;
            double valley = 0.0;
            double peak = 0.0;
            while (i <= count) {
                if ((strcmp(rec[i].community, com) == 0) && rec[n].year == rec[i].year && rec[n].month == rec[i].month && !rec[n].isCounted) {
                    //TODO ״ֻ̬�ܴ�һ��
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
        printf("          ס����Ϣ��δ�ҵ���С��\n");
    }
    change = -1;
    id = 0;
}

/*��������ʾС����Ϣ*/
void displayCommunityByID() {
    char com[MAX_COMMUNITY_LEN] = { 0 };
    printf("           ����С������");
    scanf_s("%s", com, MAX_COMMUNITY_LEN);
    change = findRecordByCommunityName(rec, com);
    if (change != -1) {
        printf("           ��������ʾС����Ѽ�¼��Ϣ\n");
        printf("           1Ϊ�����ݣ�0Ϊδ����\n");
        printf("           С�������Ƿ����ݣ�\n");
        printf("           ");
        printf("%-8s", rec[change].community);
        printf("%-8d", rec[change].isListed);
        printf("\n");
        printf("           ����:   ������  ��ʱ��          ��ʱ��          ���õ�����      ��ѣ�\n");
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
        printf("           ס����Ϣ��δ�ҵ���С��\n");
    }
    change = -1;
    id = 0;
}


/*��ʾδ����С������*/
void displayUnlisted() {
    int n = 1;
    int i = 1;
    if (findUnlisted()) {
        printf("             δ����С��������\n");
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
        printf("             ס����Ϣ��δ�ҵ�δ����С��\n");
    }
}

/*��ʾ������С������*/
void displayListed() {
    int n = 1;
    int i = 1;
    if (findUnlisted()) {
        printf("             ������С��������\n");
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
        printf("             ס����Ϣ��δ�ҵ�������С��\n");
    }
}

/*��������С������*/
void displayUrgent() {
    /*����a,b����õ��Ľ����һ��С��������a,b����Ϊdouble������int*/
    int i = 1;
    int x = 0;
    double b = 0.0;
    double a = 0.0;
    int n = findUnlisted();
    int c = n;
    if (n) {
        printf("             ��������С��������\n");
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
        printf("             ס����Ϣ��δ�ҵ�δ����С��\n");
    }
}


/**
 *�޸�ס����Ϣ
 */

/*�޸�ĳ���û���Ϣ�������*/
void modifyRecord() {
    int year = 0;
    int month = 0;
    do {
        printf("             ���뻧�ţ�");
        scanf_s("%d", &id);
        if (id < MIN_RECORDS || id >= MAX_RECORDS+1) {
            printf("             ������С�ڰ�λ��ID\n");
        }
    } while (id < MIN_RECORDS || id >= MAX_RECORDS+1);
    do {
        printf("             ������ݣ�");
        scanf_s("%d", &year);
        if (year < 2000 || year > 2024) {
            printf("             ������2000��2024֮������\n");
        }
    } while (year < 2000 || year > 2024);
    do {
        printf("             �����·ݣ�");
        scanf_s("%d", &month);
        if (month < 1 || month > 12) {
            printf("             ��������ȷ���·�\n");
        }
    } while (month < 1 || month > 12);
    change = findRecordByIDDate(rec, id, year, month);
    if (change != -1) {
        printf("             �ҵ�����ס����Ϣ \n");
        displaySameTitle();
        displaySame(change);
        displayDifferentTitle();
        displayDifferent(change);
        askfg();
        change = -1;
        printf("             �޸ĳɹ�\n");
    }
    else {
        printf("            ס����Ϣ��δ�ҵ���ס��\n");
    }
}

/*���ס����Ϣ*/
void addRecord() {
	printf("            ���ס����Ϣ\n");
	printf("            ����¼��ס����Ϣ����\n");
    do {
        printf("             ���뻧�ţ�");
        scanf_s("%d", &id);
        if (id < MIN_RECORDS || id >= MAX_RECORDS+1) {
            printf("             ������С�ڰ�λ��ID\n");
        }
    } while (id < MIN_RECORDS || id >= MAX_RECORDS+1);
	change = findRecordByID(rec, rec[count].id);     /*Ѱ���Ƿ�������ͬ�Ļ���*/
	if (change)
	{
		printf("            ���и��û���Ϣ��\n");             /*�����ͬ����Ϣ*/
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
		change = 0;                                /*��change��Ϊ0*/
	}
	else
	{
		printf("            ������");
		scanf_s("%s", rec[count].name, QUEUE_SIZE);
		printf("            С����");
		scanf_s("%s", rec[count].community, QUEUE_SIZE);
		addTOU();
		printf("            ������");
		scanf_s("%d", &rec[count].peopleNum);
		do
		{
			printf("            �Ƿ�μӷ�ȼƷ�?\n");
			printf("            1Ϊ�μӣ�0Ϊ���μ�\n");
			printf("            ");
			scanf_s("%d", &rec[count].isJoined);
			if (rec[count].isJoined < 0 || rec[count].isJoined > 1)
			{
				printf("            ������0��1\n");
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
				printf("            ��С���Ƿ�����?\n");
				printf("            1Ϊ�����ݣ�0Ϊδ����\n");
				printf("            ");
				scanf_s("%d", &rec[count].isListed);
				if (0 >rec[count].isListed || 1 < rec[count].isListed)
				{
					printf("            ������0��1\n");
				}
			} while (0 > rec[count].isListed || 1 < rec[count].isListed);
			rec[count].totalUsage = rec[count].peakUsage + rec[count].valleyUsage;
			rec[count].price = calculateBill(rec[count].peakUsage, rec[count].valleyUsage, rec[count].totalUsage, rec[count].peopleNum, rec[count].isJoined);
		}
	}
	printf("           �ɹ����ס����\n\n");
}
/*�������·����Ϣ*/
void addTOU() {
    do {
        printf("            ��ݣ�");
        scanf_s("%d", &rec[count].year);
        if (rec[count].year < 2000 || rec[count].year > 2024) {
            printf("            ������2000��2024֮������\n");
        }
    } while (rec[count].year < 2000 || rec[count].year > 2024);
    do {
        printf("            �·ݣ�");
        scanf_s("%d", &rec[count].month);
        if (1 > rec[count].month || rec[count].month > 12) {
            printf("            ��������ȷ���·�\n");
        }
    } while (1 > rec[count].month || rec[count].month > 12);
    printf("            ��ʱ������");
    scanf_s("%lf", &rec[count].peakUsage);
    printf("            ��ʱ������");
    scanf_s("%lf", &rec[count].valleyUsage);
  // TODO ����ʵ����������Ƿ����"�Ƿ�ͳ�ƹ�"�ı�ǩ  rec[count].count = 1;
}

/*ɾ��ס����Ϣ*/
void removeRecord() {
    int id = 0;
    int year = 0;
    int month = 0;
    printf("             ���뻧�ź����ڲ���Ҫɾ���ĵ�Ѽ�¼��Ϣ \n");
    do {
        printf("             ���뻧�ţ�");
        scanf_s("%d", &id);
        if (id < MIN_RECORDS || id >= MAX_RECORDS+1) {
            printf("             ������С�ڰ�λ��ID\n");
        }
    } while (id < MIN_RECORDS || id >= MAX_RECORDS+1);
    do {
        printf("             ������ݣ�");
        scanf_s("%d", &year);
        if (year < 2000 || year > 2024) {
            printf("             ������2000��2024֮������\n");
        }
    } while (year < 2000 || year > 2024);
    do {
        printf("             �����·ݣ�");
        scanf_s("%d", &month);
        if (month < 1 || month > 12) {
            printf("             ��������ȷ���·�\n");
        }
    } while (month < 1 || month > 12);
    int n = findRecordByIDDate(rec, id, year, month);
    if (n != -1) {
        while (n < count) {
            rec[n] = rec[++n];            /*�ú�һ�����鸲��ǰһ������*/
        }
        count--;
        printf("\n            ��ɾ��������Ϣ\n\n");
    }
    else {
        printf("            ס����Ϣ��δ�ҵ���ס��\n");
    }
}


/*���ķ�ʱ����*/
void changePeak() {
    printf("              ��ʱ������");
    scanf_s("%lf", &rec[change].peakUsage);
    rec[count].totalUsage = rec[count].peakUsage + rec[count].valleyUsage;
    rec[count].price = calculateBill(rec[count].peakUsage, rec[count].valleyUsage, rec[count].totalUsage, rec[count].peopleNum, rec[count].isJoined);
}

/*���Ĺ�ʱ����*/
void changeValley() {
    printf("              ��ʱ������");
    scanf_s("%lf", &rec[change].peakUsage);
    rec[count].totalUsage = rec[count].peakUsage + rec[count].valleyUsage;
    rec[count].price = calculateBill(rec[count].peakUsage, rec[count].valleyUsage, rec[count].totalUsage, rec[count].peopleNum, rec[count].isJoined);
}

/*�޸��Ƿ�μӷ�ȼƷ�*/
void modifyIsJoined() {
    do {
        printf("             ���뻧�ţ�");
        scanf_s("%d", &id);
        if (id < MIN_RECORDS || id >= MAX_RECORDS+1) {
            printf("             ������С�ڰ�λ��ID\n");
        }
    } while (id < MIN_RECORDS || id >= MAX_RECORDS+1);
    change = findRecordByID(rec, id);
    if (!change) {
        printf("            ס����Ϣ��δ�ҵ���ס��\n");
    } else {
        do {
            printf("             1Ϊ�μӣ�0Ϊ���μ�\n");
            printf("             �Ƿ�μӷ�ȼƷѣ�\n ");
            scanf_s("%d", &rec[change].isJoined);
            if (0 > rec[change].isJoined || 1 <  rec[change].isJoined) {
                printf("             ������0��1\n");
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
        printf("             �޸ĳɹ�\n");
    }
}

// TODO ������ID���һ��ŷ�װΪ����
/*�޸�ס������*/
void modifyPeopleNum() {
    do {
        printf("             ���뻧�ţ�");
        scanf_s("%d", &id);
        if (id < MIN_RECORDS || id >= MAX_RECORDS+1) {
            printf("             ������С�ڰ�λ��ID\n");
        }
    } while (id < MIN_RECORDS || id >= MAX_RECORDS+1);
    change = findRecordByID(rec, id);
    if (!change) {
        printf("            ס����Ϣ��δ�ҵ���ס��\n");
    } else
    {
        printf("             ������ס��������");
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
        printf("             �޸ĳɹ�\n");
    }
}

/*�޸�ס������С��*/
void modifyCommunityName() {
    do {
        printf("             ���뻧�ţ�");
        scanf_s("%d", &id);
        if (id < MIN_RECORDS || id >= MAX_RECORDS+1) {
            printf("             ������С�ڰ�λ��ID\n");
        }
    } while (id < MIN_RECORDS || id >= MAX_RECORDS+1);
    change = findRecordByID(rec, id);
    if (!change) {
        printf("            ס����Ϣ��δ�ҵ���ס��\n");
    } else {
        printf("             ������С������");
        int i = change;
        while (i <= count) {
            if (rec[i].id == id) {
                scanf_s("%s", &rec[i].community, QUEUE_SIZE);
                i++;
            } else {
                i++;
            }
        }
        printf("             �޸ĳɹ�\n");
    }
}

/*�޸�С���Ƿ�����*/
void modifyIsListed() {
    char com[MAX_COMMUNITY_LEN] = { 0 };
    printf("             ����С������");
    scanf_s("%s", com, MAX_COMMUNITY_LEN);
    change = findRecordByCommunityName(rec, com);
    int n = change;
    if (change) {
        printf("             С�������Ƿ����ݣ�\n");
        printf(" %-8s", rec[change].community);
        printf("%-8d", rec[change].isListed);
        printf("\n");
        do {
            printf("             1Ϊ�����ݣ�0Ϊδ����\n");
            printf("             �Ƿ����ݣ�\n ");
            printf("             ");
            scanf_s("%d", &rec[change].isListed);
            if (0 > rec[change].isListed || 1 < rec[change].isListed) {
                printf("             ������0��1\n");
            }
        } while (0 >rec[change].isListed || 1 < rec[change].isListed);
        while (n) {
            rec[n].isListed = rec[count].isListed;
            n = findRecordByCommunityName(rec, rec[n].community);
        }
        n = change;
        while (n < count) n++;
        printf("             �޸ĳɹ�\n");
    } else {
        printf("            ס����Ϣ��δ�ҵ���С��\n");
    }
    change = 0;
    id = 0;
}


/**
 *���ݹ���
 */
/*�����Ƿ���С������*/
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

/*�����Ƿ���С������*/
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
 * ��Ѽ���
 */
/*�����ܵ��*/
double calculateBill(double peak, double valley, double total, int peopleNum, int isJoined) {
	switch (isJoined) {
	case 0: return originCalculateBill(total, peopleNum);
	case 1: return TOUCalculateBill(peak, valley, total, peopleNum);
    default: ;
    }
	return 0;
}

// TODO ��ħ������Ϊ����
/*���㲻�����ȵĵ��*/
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

/*�����ȵ��*/
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



