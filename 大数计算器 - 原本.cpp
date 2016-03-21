#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

#define MAX_LENGTH 10000
#define MAX_LENGTH_ 10000
#define RESULT_LENGTH 20000

using namespace std;
bool CheckNumber(char c);
bool CheckOperation(char c);
void pluss(char A[MAX_LENGTH],char B[MAX_LENGTH],int ,int);///加
void reduce(char A[MAX_LENGTH],char B[MAX_LENGTH],int ,int);///减
void multip(char A[MAX_LENGTH],char B[MAX_LENGTH],int ,int);///乘
void dividion(char A[MAX_LENGTH],char B[MAX_LENGTH]);///除
void reduce1(char A[MAX_LENGTH],char B[MAX_LENGTH],int A_length,int B_length);
short check_relation(char A[MAX_LENGTH],char B[MAX_LENGTH],int A_length,int B_length);

char A[MAX_LENGTH]= {'z'};
char B[MAX_LENGTH]= {'z'};
int A_length=0;
int B_length=0;
char C[RESULT_LENGTH]= {'z'};
int C_length=0;
char operation='z';

int main()
{
    char big = 'y';
    while(big=='y'||big=='Y')
    {
        system("cls");
        cout<<"请输入(超大数)计算式:操作数最大长度为"<<MAX_LENGTH<<endl;
        while(true)
        {
            string s;///输入的全部
            cin>>s;
            bool flag=false;///判断输入是否规范

            if(s.length()>MAX_LENGTH*2+1)///判断长度
            {
                cout<<"输入表达式超出范围，请重新输入"<<endl;
                continue;
            }

            A_length=0;
            for(int i=0; (i<=MAX_LENGTH&&i<s.length()); i++)
            {
                if(CheckNumber(s[i]))///第一个数字
                {
                    A[i]=s[i];
                    A_length++;
                }
                else
                {
                    if(CheckOperation(s[i]))///判断运算符
                    {
                        operation=s[i];
                        break;
                    }
                    else
                    {
                        cout<<"输入中含有非法字符,请重新输入！"<<endl;
                        flag=true;
                        break;
                    }

                }
            }
            if(flag==true)continue;///输入不规范
            if(operation=='z')///可以不用吧
                if(A_length<MAX_LENGTH)
                {
                    cout<<"输入不是个正确的表达式，请重新输入！"<<endl;
                    continue;
                }
                else
                {
                    cout<<"输入操作数超出了计算范围,请重新输入！"<<endl;
                    continue;
                }

            B_length=0;
            for(int i=0; i<MAX_LENGTH&&i<(s.length()-A_length-1); i++)///第二个数
            {
                if(CheckNumber(s[i+A_length+1]))
                {
                    B[i]=s[i+A_length+1];
                    B_length++;
                }
                else
                {
                    cout<<"输入中含有非法字符,请重新输入！"<<endl;
                    flag=true;
                    break;
                }
            }
            if(flag)
                continue;
            if(A_length+B_length+1<s.length())
            {
                cout<<"输入操作数超出了计算范围,请重新输入！"<<endl;
                continue;
            }
            break;
        }
///打印计算式
        system("cls");///清屏
        for(int i=0; i<A_length; i++)///输出计算式
            cout<<A[i];
        cout<<operation;
        for(int i=0; i<B_length; i++)
            cout<<B[i];
        cout<<"=";
///以上为输入部分
        if(operation=='+')///调用函数
            pluss(A,B,A_length,B_length);
        else if(operation=='-')
            reduce(A,B,A_length,B_length);
        else if(operation=='*')
            multip(A,B,A_length,B_length);
        else
            dividion(A,B);

///打印计算结果
        bool flag=true;
        for(int i=0; i<C_length; i++)
        {
            if(C[i]=='0'&&flag&&i!=(C_length-1));///???
            else
            {
                flag=false;
                cout<<C[i];
            }
        }
        if(operation=='/'&&A_length>0)///显示除法所得的余数
        {
            if(!(A_length==1&&A[0]=='0'))
            {
                cout<<"…";
                for(int i=0; i<A_length; i++)
                    cout<<A[i];
            }
        }
        cout<<endl;
        cout<<"是否继续？    <Y>    <N>"<<endl;
        cin>>big;
    }
    return 0;
}

bool CheckOperation(char c)///检查输入字符是否为+-*/运算符
{
    if(c=='+'||c=='-'||c=='/'||c=='*')
        return true;
    else
        return false;
}

bool CheckNumber(char c)///检查输入字符是否为数字
{
    if(c>='0'&&c<='9')
        return true ;
    else
        return false;
}

bool check_B_is_0(char B[MAX_LENGTH],int B_length)///如果B为0，返回true
{
    for(int i=0; i<B_length; i++)
        if(B[i]!='0')
            return false;
    return true;
}

short Abigger(char A[MAX_LENGTH],char B[MAX_LENGTH],int A_length)///比较相同位数的A和B的大小，A大则返回1，相等，返回0，A小返回-1
{
    for(int i=0; i<A_length; i++)
    {
        if(A[i]>B[i])
            return 1;
        if(A[i]<B[i])
            return -1;
    }
    return 0;
}

void pluss(char A[MAX_LENGTH],char B[MAX_LENGTH],int A_length,int B_length)///乘法
{
    C_length=0;
    int length;
    char temp[RESULT_LENGTH];
    int JinWei=0;
    if(A_length>B_length)
    {
        length=A_length-B_length;
        int j=0;
        for(int i=A_length-1; i>=0; i--)
        {
            C_length++;
            if((A[i]+B[i-length]-'0'-'0'+JinWei)>9&&i-length>=0)//有进位
            {
                temp[j]=(char)(A[i]+B[i-length]-'0'+JinWei-10);
                JinWei=1;
            }
            if((A[i]+B[i-length]-'0'-'0'+JinWei)<10&&i-length>=0)//无进位
            {
                temp[j]=(char)(A[i]+B[i-length]-'0'+JinWei);
                JinWei=0;
            }
            if((A[i]-'0'+JinWei)>9&&i-length<0)
            {
                temp[j]=(char)(A[i]+JinWei-10);
                JinWei=1;
            }
            if((A[i]-'0'+JinWei)<10&&i-length<0)
            {
                temp[j]=(char)(A[i]+JinWei);
                JinWei=0;
            }
            j++;
        }
        if(JinWei==1)
        {
            temp[C_length]='1';
            C_length++;
        }
    }
    else
    {
        length=B_length-A_length;
        int j=0;
        for(int i=B_length-1; i>=0; i--,j++)
        {
            C_length++;
            if((B[i]+A[i-length]-'0'-'0'+JinWei)>9&&i-length>=0)//有进位
            {
                temp[j]=(char)(B[i]+A[i-length]-'0'+JinWei-10);
                JinWei=1;
            }
            if((B[i]+A[i-length]-'0'-'0'+JinWei)<10&&i-length>=0)//无进位
            {
                temp[j]=(char)(B[i]+A[i-length]-'0'+JinWei);
                JinWei=0;
            }
            if((B[i]-'0'+JinWei)>9&&i-length<0)
            {
                temp[j]=(char)(B[i]+JinWei-10);
                JinWei=1;
            }
            if((B[i]-'0'+JinWei)<10&&i-length<0)
            {
                temp[j]=(char)(B[i]+JinWei);
                JinWei=0;
            }
        }
        if(JinWei==1)
        {
            temp[C_length]='1';
            C_length++;
        }
    }
    for(int i=0; i<C_length; i++) //将temp逆序存储的结果还原存储在C数组中
    {
        C[i]=temp[C_length-1-i];
    }
}

void reduce(char A[MAX_LENGTH],char B[MAX_LENGTH],int A_length,int B_length)//计算A-B
{
    if(A_length>B_length)
    {
        reduce1(A,B,A_length,B_length);
    }
    else if(A_length<B_length)
    {
        reduce1(B,A,B_length,A_length);
        for(int i=C_length; i>0; i--) //在结果前面添加-号
            C[i]=C[i-1];
        C[0]='-';
        C_length++;
    }
    else
    {
        short judge=Abigger(A,B,A_length);
        if(judge==1)
            reduce1(A,B,A_length,B_length);
        else if(judge==0) //两数相等
        {
            C_length=1;
            C[0]='0';
        }
        else
        {
            reduce1(B,A,B_length,A_length);
            for(int i=C_length; i>0; i--) //在结果前面添加-号
                C[i]=C[i-1];
            C[0]='-';
            C_length++;
        }
    }
}

void reduce1(char A[MAX_LENGTH],char B[MAX_LENGTH],int A_length,int B_length)//A必须大于B才能运算成功
{
    int JieWei=0;
    char temp[MAX_LENGTH_]= {'z'};
    C_length=0;

    for(int i=A_length-1; i>=0; i--)
    {
        if((i>=(A_length-B_length)))
            if((A[i]-B[i-(A_length-B_length)]-JieWei)<0)
            {
                temp[C_length]=(A[i]-B[i-(A_length-B_length)]-JieWei+10+'0');
                C_length++;
                JieWei=1;
            }
            else
            {
                temp[C_length]=(A[i]-B[i-(A_length-B_length)]+'0'-JieWei);
                C_length++;
                JieWei=0;
            }
        else if((A[i]-JieWei)<'0')
        {
            temp[C_length]=(A[i]-JieWei+10);
            C_length++;
            JieWei=1;
        }
        else
        {
            temp[C_length]=(A[i]-JieWei);
            C_length++;
            JieWei=0;
        }
    }
    while(1)//删除结果高位0
    {
        if(C_length==1) break;
        if(temp[C_length-1]=='0')
            C_length--;
        else break;
    }
    for(int i=0; i<C_length; i++) //将temp逆序存储的结果还原存储在C数组中
    {
        C[i]=temp[C_length-1-i];
    }
}

void multip(char A[MAX_LENGTH],char B[MAX_LENGTH],int A_length,int B_length)
{
    char temp[8][MAX_LENGTH_];
    int temp_length[8];
    char temp1[RESULT_LENGTH];
    int temp1_length=0;

    for(int i=0; i<A_length; i++)
        C[i]=A[i];
    C_length=A_length;

    for(int i=0; i<8; i++)
    {
        pluss(A,C,A_length,C_length);
        for(int j=0; j<C_length; j++)
            temp[i][j]=C[j];
        temp_length[i]=C_length;
    }

    for(int i=0; i<RESULT_LENGTH; i++) //C初始化为0
        C[i]='0';
    C_length=1;

    for(int i=B_length-1; i>=0; i--)
    {
        if(B[i]=='0')
        {
            continue;
        }
        if(B[i]=='1')
        {
            temp1_length=A_length+(B_length-1-i);
            for(int j=0; j<(B_length-i); j++)
                temp1[temp1_length-j]='0';
            for(int j=0; j<(A_length); j++)
                temp1[j]=A[j];
            pluss(C,temp1,C_length,temp1_length);
        }
        else
        {
            int m=B[i]-'0'-2;
            temp1_length=temp_length[m]+(B_length-1-i);
            for(int j=0; j<(B_length-i); j++)
                temp1[temp1_length-j]='0';
            for(int j=0; j<temp_length[m]; j++)
                temp1[j]=temp[m][j];
            pluss(C,temp1,C_length,temp1_length);
        }
    }
}

void dividion(char A[MAX_LENGTH],char B[MAX_LENGTH])
{
    if(check_B_is_0(B,B_length))
    {
        C_length=12;
        C[0]='i';
        C[1]='n';
        C[2]='p';
        C[3]='u';
        C[4]='t';
        C[5]=' ';
        C[6]='B';
        C[7]=' ';
        C[8]='i';
        C[9]='s';
        C[10]=' ';
        C[11]='0';
    }
    else
    {
        short relation=check_relation(A,B,A_length,B_length);
        if(relation==0)
        {
            C_length=1;
            C[0]='1';
            A_length=0;
        }
        else if(relation==-1)
        {
            C_length=1;
            C[0]='0';
        }
        else//被除数大于除数
        {
            char temp1[MAX_LENGTH];
            int temp1_length=0;
            char temp2[RESULT_LENGTH];
            int temp2_length=0;
            char temp[10][MAX_LENGTH_];
            int temp_length[10];
            temp_length[0]=1;
            temp[0][0]='0';
            C_length=1;
            C[0]='0';

            for(int i=1; i<10; i++)
            {
                pluss(B,C,B_length,C_length);
                for(int j=0; j<C_length; j++)
                    temp[i][j]=C[j];
                temp_length[i]=C_length;
            }

            for(int i=0; i<B_length; i++)
                temp1[i]=A[i];
            temp1_length=B_length;
            for(int i=(B_length-1); i<A_length;)
            {
                {
                    for(int j=9; j>=0; j--)
                    {
                        short judge=check_relation(temp[j],temp1,temp_length[j],temp1_length);
                        if(judge==1)
                            continue;
                        else
                        {
                            temp2[temp2_length++]=j+'0';
                            reduce(temp1,temp[j],temp1_length,temp_length[j]);
                            break;
                        }
                    }
                    for(int j=0; j<C_length; j++)
                        temp1[j]=C[j];
                    temp1_length=C_length;

                    if((i+1)>=(A_length))
                    {
                        break;
                    }
                    i++;
                    temp1[temp1_length]=A[i];
                    temp1_length++;
                    for(int k=0; k<temp1_length-1; k++) //删除高位0
                    {
                        if(temp1[k]=='0')
                        {
                            temp1_length--;
                            for(int m=k; m<temp1_length; m++)
                                temp1[m]=temp1[m+1];
                        }
                        else break;
                    }
                }
            }

            for(int i=0; i<C_length; i++)
                A[i]=C[i];
            A_length=C_length;
            for(int i=0; i<temp2_length; i++)
                C[i]=temp2[i];
            C_length=temp2_length;


            for(int k=0; k<C_length-1; k++) //删除高位0
            {
                if(C[k]=='0')
                {
                    C_length--;
                    for(int m=k; m<C_length; m++)
                        C[m]=C[m+1];
                }
                else break;
            }
        }
    }
}

short check_relation(char A[MAX_LENGTH],char B[MAX_LENGTH],int A_length,int B_length)//A>B 1;B>A -1;A=B 0
{
    if(A_length>B_length)
        return 1;
    else if(A_length<B_length)
        return -1;
    else
        return Abigger(A,B,A_length);
}
