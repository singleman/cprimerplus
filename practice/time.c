#include<stdio.h>
#include<time.h>

int main()
{
    time_t first;    //�������
    struct tm *local;       //tm�ṹ�����
    first=time(NULL);       //ȡ�õ�ǰʱ�䣬�������time()����
    local=localtime(&first);//����������ʱ��ת��Ϊ������ʱ�䲢�洢���ṹ�嵱��
    printf("����Ϊ��λ��ʱ�䣺%d\n",first);
    printf("��ʵʱ�䣺%d:%d:%d:%d:%d\n",local->tm_year+1900,local->tm_mon,local->tm_mday,local->tm_hour,local->tm_min);
    return 0;
}
