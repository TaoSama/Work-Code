/******************************************************************************

问题描述
小明喜欢做a+b的算术，但是他经常忘记把末位对齐，再进行加，所以，经常会算错。
比如12+13，他把12左移了1位，结果变成了133。小明已经算了一些等式，
请计算一下他到底移动了多少位。

输入
第一行是一个整数K，表示样例的个数。以后每行一个样例，形如a+b=c, 1≤a,b≤1e4;0≤c≤1e9。

输出
每行输出一个样例的结果，以b为标准，a如果往左移n位，输出n，如果往右移n位，输出-n。
测试数据保证一定有解，如果存在多个解，输出左移的结果。

样例输入
6
12+13=1213
12+13=1312
12+13=25
12+13=12013
12+13=133
12+13=142

样例输出
2
-2
0
3
1
-1


注意：
（1）不要删除Program和End这两个标志；
（2）fun()的函数头不能修改，main()函数也不要修改；
（3）wwjt()函数是测试函数，不能修改。
（4）其他需要的头文件等可以补充加入

*******************************************************************************/
#include <stdio.h>
const int MAX = 1000000000;

int check(int a,int b,int c);
void wwjt();

int main()
{
        int ca,a,b,c,i,n;
        scanf("%d",&ca);
        while(ca--){
        scanf("%d+%d=%d",&a,&b,&c);
        n = fun(a,b,c);
        printf("%d\n",n);
    }
        wwjt();
        return 0;
}

int fun(int a,int b,int c)
{

/**********Program**********/


    // 右移
    int ret = 0;
    long long newb = b;
    for(int i = 0; i <= 10; ++i){
        if(a + newb == c) {ret = -i; break;}
        newb *= 10;
    }

    // 左移
    long long newa = a;
    for(int i = 0; i <= 10; ++i){
        if(newa + b == c) {ret = i; break;}
        newa *= 10;
    }

    return ret;



/**********  End  **********/
}

void wwjt()
{
    int ca,a,b,c,i,n;
    FILE *fin,*fout;
    fin=fopen("in.txt","r");
    fout=fopen("out.txt","w");
    fscanf(fin,"%d",&ca);
    while(ca--){
        fscanf(fin,"%d+%d=%d",&a,&b,&c);
        n = fun(a,b,c);
        fprintf(fout,"%d\n",n);
    }
    fclose(fin);
    fclose(fout);
}

