/******************************************************************************
��������
nλ�����ܱ�m���������ж��ٸ���

����
��һ����һ������K(K��10000)����ʾ�����ĸ�����
ÿ��������һ�У���������n(1��n��18),m(2��m��1000000)��

���
ÿ�����һ�������Ľ����

��������
4
1 2
3 2
3 3
3 10000
�������
5
450
300
0

ע�⣺
��1����Ҫɾ��Program��End��������־��
��2��fun()�ĺ���ͷ�����޸ģ�main()����Ҳ��Ҫ�޸ģ�
��3��wwjt()�����ǲ��Ժ����������޸ġ�
��4��������Ҫ��ͷ�ļ��ȿ��Բ������
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
//��1��nλ�����ܱ�m���������ĸ���
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
