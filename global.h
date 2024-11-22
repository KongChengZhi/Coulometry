//
// Created by singsky on 24-11-19.
//

#ifndef GLOBAL_H
#define GLOBAL_H

#define MAX_NAME_LEN 25       // ������󳤶�
#define MAX_COMMUNITY_LEN 25  // С������󳤶�
#define MAX_RECORDS 99999999  // ���ID
#define MIN_RECORDS 1         // ��СID
#define QUEUE_SIZE 50         // �����г���

// ��Ѽ�¼�ṹ��
typedef struct Record {
    int id;  // ����
    char name[MAX_NAME_LEN];  // ����
    char community[MAX_COMMUNITY_LEN];  // С����
    int peopleNum;  // ��ͥ�˿���
    int year; // ���
    int month;  // �·�
    double peakUsage;  // ��ʱ�õ���
    double valleyUsage;  // ��ʱ�õ���
    double totalUsage;  // ���õ���
    double price;  // �ܵ��
    int isJoined;  // �Ƿ�μӷ�ȼƼ����ߣ�1Ϊ�μӣ�0Ϊ���μ�
    int isListed;  // �Ƿ��Ѿ����ݣ�1Ϊ�����ݣ�0Ϊδ����
    int isCounted; //�жϸ������Ƿ��Ѿ�ͳ�ƹ�����������Ҫͳ�ƶ��ס����Ϣ�����
    struct Record* next;  //ָ��
} Record, *pRecord;

//����ȫ�ֱ���
extern int id;
extern int count;
extern int change;

//ȫ��ͨ��
extern Record rec[QUEUE_SIZE];

#endif //GLOBAL_H
