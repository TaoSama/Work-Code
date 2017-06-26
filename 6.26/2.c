/*********************************************************************************
问题描述
求两个不超过100位的非负整数之和。

输入
有三行，第一行是样例个数，后面两行每一行是一个不超过100位的非负整数，没有多余的前导0

输出
一行，即两数相加后的结果，结果里不能有多余的前导0，即如果结果是342，则不能输出为0342

输入样列
2
888888888888
333333333333
1234
23

输出样列
1222222222221
1257



注意：
（1）不要删除Program和End这两个标志；
（2）add_b的函数头不能修改，main()函数也不要修改；
（3）wwjt()函数是测试函数，不能修改。
（4）其他需要的头文件等可以补充加入
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

//两数相加，结果放在s1中
void add_b(char s1[],char s2[])
{

/**********Program**********/

    int len1 = strlen(s1);
    int len2 = strlen(s2);

    // 翻转两个字符串
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

    // 从低位到高位相加
    int carry = 0; //进位
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
    // 最后一次进位
    if(carry > 0) s1[maxlen++] = '1';
    s1[maxlen] = '\0';

    // 翻转回来字符串
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

