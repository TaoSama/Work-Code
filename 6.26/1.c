/*-------------------------------------------------------
【程序设计】
---------------------------------------------------------

题目：此程序功能将输入的十进制整数num(num<=65535)转换为二进制(双字节，16位)输出。

例如：输入：35，   输出：0000000000100011
      输入：15625，输出：0011110100001001
说明：逆序输出即可，不要求数组逆置

要求：完成函数fun(),其功能是实现十进制数到二进制字符串的转换，
      其形式参数为待转换的十进制整数。
　　
注意:部分源程序给出如下。wwjt()为测试函数。　

请勿改动main函数和其他函数中的任何内容,仅在函数fun的花括号中填入所编写的若干语句。
-------------------------------------------------------*/
#include<stdio.h>

void wwjt();

/**************************************************
  十进制数转成二进制数的字符串
  int number 要转换的十进制正整数
 char str[] 存放二进制数的字符串
 **************************************************/
void  fun(int number, char str[])
{

/**********Program**********/

    int idx = 0;
    while(number > 0){
        str[idx++] = '0' + (number % 2);
        number /= 2;
    }


/**********  End  **********/


}

int main()
{
        char binStr[17]="0000000000000000";        //用来存放双字节二进制的符串
        int  number,i;

        printf("请输入一个十进制正整数：");
        scanf("%d",&number);
        if (number > 0)
                fun(number,binStr);
        printf("%d转成二进制为:",number);
        for (i = 15 ; i >= 0;i--)  //逆序输出
                putchar(binStr[i]);
        wwjt();
        return 0;
}

void wwjt()
{
  FILE *IN,*OUT;
  char binstr[17];
  int i ,j;
  int t;
  IN=fopen("in.dat","r");
  if(IN==NULL)
  {
    printf("Read FILE Error");
  }
  OUT=fopen("out.dat","w");
  if(OUT==NULL)
  {
    printf("Write FILE Error");
  }
  for(i=0;i<30;i++)
  {
    fscanf(IN,"%d",&t);
    for (j=0;j<16;j++)
                binstr[j]='0';
        binstr[j]='\0';
    fun(t,binstr);
    fprintf(OUT,"%s\n",binstr);
  }
  fclose(IN);
  fclose(OUT);
}
