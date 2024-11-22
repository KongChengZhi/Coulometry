//
// Created by singsky on 24-11-19.
//

#ifndef GLOBAL_H
#define GLOBAL_H

#define MAX_NAME_LEN 25       // 姓名最大长度
#define MAX_COMMUNITY_LEN 25  // 小区名最大长度
#define MAX_RECORDS 99999999  // 最大ID
#define MIN_RECORDS 1         // 最小ID
#define QUEUE_SIZE 50         // 最大队列长度

// 电费记录结构体
typedef struct Record {
    int id;  // 户号
    char name[MAX_NAME_LEN];  // 姓名
    char community[MAX_COMMUNITY_LEN];  // 小区名
    int peopleNum;  // 家庭人口数
    int year; // 年份
    int month;  // 月份
    double peakUsage;  // 峰时用电量
    double valleyUsage;  // 谷时用电量
    double totalUsage;  // 总用电量
    double price;  // 总电费
    int isJoined;  // 是否参加峰谷计价政策，1为参加，0为不参加
    int isListed;  // 是否已经扩容，1为已扩容，0为未扩容
    int isCounted; //判断该数据是否已经统计过，适用于需要统计多个住户信息的情况
    struct Record* next;  //指针
} Record, *pRecord;

//声明全局变量
extern int id;
extern int count;
extern int change;

//全局通用
extern Record rec[QUEUE_SIZE];

#endif //GLOBAL_H
