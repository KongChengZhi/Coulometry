//
// Created by singsky on 24-11-19.
//

/**
 * TOU(Time-of-Use),���ڱ�ʾ��ʱ����
 */

#ifndef RECORD_H
#define RECORD_H
#include "global.h"


/**
 * ����ָ��ס�����˵�Ѽ�¼��Ϣ
 */
void findRecord();

/**
 * �Ӽ�¼�б�������ָ���û����б�
 */
int findRecordByID(Record* rec, int id);
int findRecordByIDDate(Record* rec, int id, int year, int month);
int findRecordByCommunityName(Record* rec, char* com);  // ��

/**
 * ����չʾ
 */
void displaySameTitle();
void displayDifferentTitle();


/**
 * չʾ��Ϣ
 */
void displaySame(int n);
void displayDifferent(int n);
void displayCommunityByDate(); //BUG
void displayCommunityByID();  //BUG
void displayUnlisted();
void displayListed();
/* ����Լ������ݵĶ���Ϊ��
 * �¾�����330�ȣ������֮�ҵĵ�ס���ĵ�һ����ȣ�ռ����ס����60%����
 */
void displayUrgent(); //��ʾ�������ݵ�С������

/**
 * �޸�ס����Ϣ
 */
void modifyRecord();
void addRecord();
void addTOU();
void removeRecord();
void changePeak();
void changeValley();
void modifyIsJoined();
void modifyPeopleNum();
void modifyCommunityName();
void modifyIsListed();

/**
 * ���ݹ���
 */
int findListed();
int findUnlisted();

/**
 * ��Ѽ���
 */
double calculateBill(double peak, double valley, double total, int number, int isJoined);
double originCalculateBill(double total, int number);
double TOUCalculateBill(double peak, double valley, double total, int number);

#endif //RECORD_H
