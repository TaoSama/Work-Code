/*********************************************************************************
��������
������������100λ�ķǸ�����֮�͡�

����
�����У���һ����������������������ÿһ����һ��������100λ�ķǸ�������û�ж����ǰ��0

���
һ�У���������Ӻ�Ľ��������ﲻ���ж����ǰ��0������������342���������Ϊ0342

��������
2
888888888888
333333333333
1234
23

�������
1222222222221
1257



ע�⣺
��1����Ҫɾ��Program��End��������־��
��2��add_b�ĺ���ͷ�����޸ģ�main()����Ҳ��Ҫ�޸ģ�
��3��wwjt()�����ǲ��Ժ����������޸ġ�
��4��������Ҫ��ͷ�ļ��ȿ��Բ������
***********************************************************************************/
#include <stdio.h>
#include <string.h>

void add_b(char s1[],char s2[]);
void wwjt();
int main()
{
        char s1[102],s2[102];
        int i,k;
        scanf("%d",&k);
        while(k--)
        {
                scanf("%s",s1);
                scanf("%s",s2);
                add_b(s1,s2);
                printf("%s\n",s1);
        }
        wwjt();
        return 0;
}

//������ӣ��������s1��
void add_b(char s1[],char s2[])
{

/**********Program**********/

    int len1 = strlen(s1);
    int len2 = strlen(s2);

    // ��ת�����ַ���
    for(int i = 0; i < len1 / 2; ++i){
        char tmp = s1[i];
        s1[i] = s1[len1 - i - 1];
        s1[len1 - i - 1] = tmp;
    }
    for(int i = 0; i < len2 / 2; ++i){
        char tmp = s2[i];
        s2[i] = s2[len2 - i - 1];
        s2[len2 - i - 1] = tmp;
    }

    // �ӵ�λ����λ���
    int carry = 0; //��λ
    int maxlen = len1 > len2 ? len1 : len2;
    for(int i = 0; i < maxlen; ++i){
        int a = 0, b = 0;
        if(i < len1) a = s1[i] - '0';
        if(i < len2) b = s2[i] - '0';
        int add = a + b + carry;
        if(add >= 10) {
            carry = 1;
            add -= 10;
        }
        else carry = 0;
        s1[i] = add + '0';
    }
    // ���һ�ν�λ
    if(carry > 0) s1[maxlen++] = '1';
    s1[maxlen] = '\0';

    // ��ת�����ַ���
    for(int i = 0; i < maxlen / 2; ++i){
        char tmp = s1[i];
        s1[i] = s1[maxlen - i - 1];
        s1[maxlen - i - 1] = tmp;
    }



/**********  End  **********/

}

void wwjt()
{
        char s1[102],s2[102];
        int i;
        FILE *fin,*fout;
        fin=fopen("in.txt","r");
        fout=fopen("out.txt","w");
        for (i=0;i<100;i++)
        {
                fscanf(fin,"%s",s1);
                fscanf(fin,"%s",s2);
                add_b(s1,s2);
                fprintf(fout,"%s\n",s1);
        }
        fclose(fin);
        fclose(fout);
}

