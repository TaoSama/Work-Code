/******************************************************************************
问题描述
n位数中能被m整除的数有多少个？

输入
第一行是一个整数K(K≤10000)，表示样例的个数。
每个样例是一行，两个整数n(1≤n≤18),m(2≤m≤1000000)。

输出
每行输出一个样例的结果。

样例输入
4
1 2
3 2
3 3
3 10000
样例输出
5
450
300
0

注意：
（1）不要删除Program和End这两个标志；
（2）fun()的函数头不能修改，main()函数也不要修改；
（3）wwjt()函数是测试函数，不能修改。
（4）其他需要的头文件等可以补充加入
*******************************************************************************/

#include<stdio.h>
long long int fun(int n,long long int m);
void wwjt();
int main()
{
    int t;
    int n;
    long long int  m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %lld",&n,&m);
        if(n>1)
            printf("%lld\n",fun(n,m)-fun(n-1,m));
        else
            printf("%lld\n",fun(1,m));
    }
    wwjt();
}
//求1至n位数中能被m整除的数的个数
long long int fun(int n,long long int m)
{

/**********Program**********/


    long long int power = 1;
    for(int i = 1; i <= n; ++i) power *= 10;
    long long int ret = 0;
    if(n == 1){
        ret = (power - 1) / m + 1;
    }
    else{
        ret = (power - 1) / m;
    }

    return ret;



/**********  End  **********/





}



void wwjt()
{
    int K;
    int n;
        long long int  m;
    FILE *fin,*fout;
    fin=fopen("in.txt","r");
        fout=fopen("out.txt","w");
    fscanf(fin,"%d",&K);K=K/10;
    while(K--)
    {
        fscanf(fin,"%d %lld",&n,&m);
        if(n>1)
            fprintf(fout,"%lld\n",fun(n,m)-fun(n-1,m));
        else
            fprintf(fout,"%lld\n",fun(1,m));
    }
    fclose(fin);
    fclose(fout);
}
