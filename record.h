//
// Created by singsky on 24-11-19.
//

/**
 * TOU(Time-of-Use),用于表示分时电量
 */

#ifndef RECORD_H
#define RECORD_H
#include "global.h"


/**
 * 查找指定住户个人电费记录信息
 */
void findRecord();

/**
 * 从记录列表中搜索指定用户的列表
 */
int findRecordByID(Record* rec, int id);
int findRecordByIDDate(Record* rec, int id, int year, int month);
int findRecordByCommunityName(Record* rec, char* com);  // √

/**
 * 标题展示
 */
void displaySameTitle();
void displayDifferentTitle();


/**
 * 展示信息
 */
void displaySame(int n);
void displayDifferent(int n);
void displayCommunityByDate(); //BUG
void displayCommunityByID();  //BUG
void displayUnlisted();
void displayListed();
/* 这里对急需扩容的定义为：
 * 月均超过330度（即五口之家的的住户的第一档额度）占所有住户的60%以上
 */
void displayUrgent(); //显示急需扩容的小区名单

/**
 * 修改住户信息
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
 * 扩容管理
 */
int findListed();
int findUnlisted();

/**
 * 电费计算
 */
double calculateBill(double peak, double valley, double total, int number, int isJoined);
double originCalculateBill(double total, int number);
double TOUCalculateBill(double peak, double valley, double total, int number);

#endif //RECORD_H
