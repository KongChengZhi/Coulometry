#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "menu.h"
#include "file.h"

/*主函数*/
int main()
{
    setbuf(stdout, NULL); //不缓存标准输出。为了解决CLion自身问题使用，使用Visual Studio等其他编译器可以删除
    printf("基于数据分析的小区电量扩容推荐系统\n");
    count = readRecordFile(rec);       /*数一下原有文件数据行数*/
    menuMain();                        /*打开主菜单*/
    return 0;
}