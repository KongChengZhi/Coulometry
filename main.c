#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "menu.h"
#include "file.h"

/*������*/
int main()
{
    setbuf(stdout, NULL); //�������׼�����Ϊ�˽��CLion��������ʹ�ã�ʹ��Visual Studio����������������ɾ��
    printf("�������ݷ�����С�����������Ƽ�ϵͳ\n");
    count = readRecordFile(rec);       /*��һ��ԭ���ļ���������*/
    menuMain();                        /*�����˵�*/
    return 0;
}