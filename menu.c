#include<stdio.h>
#include "menu.h"
#include "maincontrol.h"
#include "file.h"
#include "global.h"
 


/*主菜单*/
void menuMain()
{
	int choice;
	do
	{
		printf("          **********************************************************\n");
		printf("          *                                                        *\n");
		printf("          *          基于数据分析的小区电量扩容推荐系统                   *\n");
		printf("          *                  请选择您的身份                           *\n");
		printf("          *               [1] 用电数据统计员                          *\n");
		printf("          *               [2] 供电公司工作人员                        *\n");
		printf("          *               [3] 清屏                                  *\n");
		printf("          *               [0] 返回                                  *\n");
		printf("          *                                                        *\n");
		printf("          **********************************************************\n");
		printf("\n");
		printf("           请选择:");
		scanf_s("%d", &choice);
		if (choice >= 0 && choice <= 3)
			runmenuMain(choice);
		else
		{
			printf("\n");
			printf("          请重新输入\n\n");
		}
	} while (choice);
	saveFile(rec, count);        /*将用户信息保存在文件中*/
}

/*用电数据统计员*/
void statistician()
{
	int choice;
	do
	{
		printf("          **********************************************************\n");
		printf("          *                                                        *\n");
		printf("          *                    用电数据统计员                         *\n");
		printf("          *                [1] 查询电费记录信息                       *\n");
		printf("          *                [2] 添加住户电费记录信息                    *\n");
		printf("          *                [3] 删除住户电费记录信息                    *\n");
		printf("          *                [4] 修改电费记录信息                       *\n");
		printf("          *                [5] 清屏                                 *\n");
		printf("          *                [0] 返回                                 *\n");
		printf("          *                                                        *\n");
		printf("          **********************************************************\n");
		printf("\n");
		printf("           请选择:");
		scanf_s("%d", &choice);
		if (choice >= 0 && choice <= 5)
		{
			runstatistician(choice);
		}
		else
		{
			printf("\n");
			printf("          请重新输入\n\n");
		}
	} while (choice);
}

/*选择修改电费记录信息功能*/
void modify()
{
	int choice;
	do
	{
		printf("          **********************************************************\n");
		printf("          *                                                        *\n");
		printf("          *                    修改电费记录信息                       *\n");
		printf("          *                [1] 修改某户某月用电记录                    *\n");
		printf("          *                [2] 修改是否参加峰谷计费                    *\n");
		printf("          *                [3] 修改住户人数                          *\n");
		printf("          *                [4] 修改小区名                            *\n");
		printf("          *                [5] 修改小区是否扩容                       *\n");
		printf("          *                [6] 清屏                                 *\n");
		printf("          *                [0] 返回                                 *\n");
		printf("          *                                                        *\n");
		printf("          **********************************************************\n");
		printf("\n");
		printf("           请选择:");
		scanf_s("%d", &choice);
		if (choice >=0 && choice <= 6)
		{
			runmodify(choice);
			id = 0;
		}
		else
		{
			printf("\n");
			printf("          请重新输入\n\n");
		}
	} while (choice);
}

/*供电公司工作人员*/
void staff()
{
	int choice;
	do
	{
		printf("          **********************************************************\n");
		printf("          *                                                        *\n");
		printf("          *                  供电公司工作人员                          *\n");
		printf("          *               [1] 查询电费记录信息                         *\n");
		printf("          *               [2] 扩容管理                               *\n");
		printf("          *               [3] 清屏                                  *\n");
		printf("          *               [0] 返回                                  *\n");
		printf("          *                                                        *\n");
		printf("          **********************************************************\n");
		printf("\n");
		printf("           请选择:");
		scanf_s("%d", &choice);
		if (choice >= 0 && choice <= 3)
		{
			runstaff(choice);
		}
		else
		{
			printf("\n");
			printf("          请重新输入\n\n");
		}
	} while (choice);
}

/*询问需要修改的内容*/
void askfg()
{
	int choice;
	do
	{
		printf("          **********************************************************\n");
		printf("          *                                                        *\n");
		printf("          *                 修改电费记录信息                           *\n");
		printf("          *           选择修改峰时用电量还是谷时用电量                    *\n");
		printf("          *                [1] 修改峰时电量                           *\n");
		printf("          *                [2] 修改谷时电量                           *\n");
		printf("          *                [3] 清屏                                 *\n");
		printf("          *                [0] 返回                                 *\n");
		printf("          *                                                        *\n");
		printf("          **********************************************************\n");
		printf("\n");
		printf("           请选择:");
		scanf_s("%d", &choice);
		if (choice >= 0 && choice <= 3)
		{
			runchange(choice);
		}
		else
		{
			printf("\n");
			printf("          请重新输入\n\n");
		}
	} while (choice);
}

/*选择查询电费记录信息功能*/
void find()
{
	int choice;
	do
	{
		printf("          **********************************************************\n");
		printf("          *                                                        *\n");
		printf("          *                 查询电费记录信息                          *\n");
		printf("          *                [1] 按户号查询                            *\n");
		printf("          *                [2] 按小区查询                            *\n");
		printf("          *                [3] 清屏                                 *\n");
		printf("          *                [0] 返回                                 *\n");
		printf("          *                                                        *\n");
		printf("          **********************************************************\n");
		printf("\n");
		printf("           请选择:");
		scanf_s("%d", &choice);
		if (choice >= 0 && choice <= 3)
		{
			runfind(choice);
		}
		else
		{
			printf("\n");
			printf("          请重新输入\n\n");
		}
	} while (choice);
}

/*选择如何显示小区电费记录信息功能*/
void findcommunity()
{
	int choice;
	do
	{
		printf("          **********************************************************\n");
		printf("          *                                                        *\n");
		printf("          *                 显示小区电费记录信息                       *\n");
		printf("          *                [1] 按日期显示                            *\n");
		printf("          *                [2] 按户号显示                            *\n");
		printf("          *                [3] 清屏                                 *\n");
		printf("          *                [0] 返回                                 *\n");
		printf("          *                                                        *\n");
		printf("          **********************************************************\n");
		printf("\n");
		printf("           请选择:");
		scanf_s("%d", &choice);
		if (choice >= 0 && choice <= 3)
		{
			runfindcommunity(choice);
		}
		else
		{
			printf("\n");
			printf("          请重新输入\n\n");
		}
	} while (choice);
}

/*扩容管理*/
void expansion()
{
	int choice;
	do
	{
		printf("          **********************************************************\n");
		printf("          *                                                        *\n");
		printf("          *                     扩容管理                             *\n");
		printf("          *                  请选择查询方式                           *\n");
		printf("          *                [1] 查询已扩容小区                         *\n");
		printf("          *                [2] 查询未扩容小区                         *\n");
		printf("          *                [3] 查询急需扩容小区                        *\n");
//		printf("          *                [4] 查询不急需扩容小区                  *\n");
		printf("          *                [4] 清屏                                 *\n");
		printf("          *                [0] 返回                                 *\n");
		printf("          *                                                        *\n");
		printf("          **********************************************************\n");
		printf("\n");
		printf("           请选择:");
		scanf_s("%d", &choice);
		if (choice >= 0 && choice <= 5)
		{
			runexpansion(choice);
		}
		else
		{
			printf("\n");
			printf("          请重新输入\n\n");
		}
	} while (choice);
}