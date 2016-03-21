#ifndef BIGNUMBER_H_INCLUDED
#define BIGNUMBER_H_INCLUDED
#include<iostream>
#include<string>///    参数设置
#include<cstring>///      BigNumber和普通数据类型的运算     运算之后答案是负数的情况   是小数的情况   减法负号问题
//#define MAX_SIZE 100
using namespace std;
const int MAX_SIZE=10000;
class BigNumber
{
    long num[MAX_SIZE];///数组倒置储存，方便进位操作
    int Length;
public:
    BigNumber();
    BigNumber(int i);///Length=-1的特殊数据，表示不存在这个数符合计算条件的返回值
    BigNumber(char* str);
    BigNumber(const char* str);
    BigNumber(string s);
    BigNumber(long val);
    BigNumber(const BigNumber& b);
    BigNumber(long a[],int front,int size);///a[]中从pos起size位作为BigNumber构造
    int length();
    void print();
    int BigNToInt();

    BigNumber& operator=(BigNumber n1);

    friend bool operator>(BigNumber& n1,BigNumber& n2);
    friend bool operator<(BigNumber& n1,BigNumber& n2);
    friend bool operator>=(BigNumber& n1,BigNumber& n2);
    friend bool operator<=(BigNumber& n1,BigNumber& n2);
    friend bool operator==(BigNumber& n1,BigNumber& n2);
    friend bool operator!=(BigNumber& n1,BigNumber& n2);

    BigNumber& operator>>(int s);///右移运算符    将数组中所有元素整体向右移s位，下标变成负数的舍去
    BigNumber operator<<(int s);///左移运算符   将数组中所有元素整体向左移s位，相当于*10的s次方

    friend BigNumber operator+(BigNumber& n1,BigNumber& n2);
    friend BigNumber operator*(BigNumber& n1,BigNumber& n2);
    friend BigNumber operator-(BigNumber& bn1,BigNumber& bn2);
    friend BigNumber operator/(BigNumber n1,BigNumber n2);
    friend BigNumber operator%(BigNumber n1,BigNumber n2);

    BigNumber& operator+=(BigNumber& n);
    BigNumber& operator-=(BigNumber& n);
    BigNumber& operator*=(BigNumber& n);
    BigNumber& operator/=(BigNumber& n);
    BigNumber& operator%=(BigNumber& n);

    BigNumber& operator++();
    BigNumber operator++(int);
    BigNumber& operator--();
    BigNumber operator--(int);

    friend istream& operator>>(istream& is,BigNumber& n);
    friend ostream& operator<<(ostream& os,const BigNumber& n);
};

BigNumber::BigNumber()
{
    for(int i=0;i<MAX_SIZE;i++)
    num[i]=0;
    Length=1;
}
BigNumber::BigNumber(int i)
{
    for(int i=0;i<MAX_SIZE;i++)num[i]=0;
    Length=-1;
}
BigNumber::BigNumber(char* str)
{
    Length=strlen(str);
    int j=Length-1;
    for(int i=0;i<Length;i++,j--)
        num[i]=str[j]-'0';
    for(int i=Length;i<MAX_SIZE;i++)
        num[i]=0;
}
BigNumber::BigNumber(const char* str)
{
    Length=strlen(str);
    int j=Length-1;
    for(int i=0;i<Length;i++,j--)
        num[i]=str[j]-'0';
    for(int i=Length;i<MAX_SIZE;i++)
        num[i]=0;
}
BigNumber::BigNumber(string s)
{
    Length=s.length();
    int j=Length-1;
    for(int i=0;i<Length;i++,j--)
        num[i]=s[j]-'0';
    for(int i=Length;i<MAX_SIZE;i++)
        num[i]=0;
}
BigNumber::BigNumber(long val)
{
    long temp[MAX_SIZE],i=0,t;
    long k=val;
    while(k!=0)
    {
        t=k%10;
        temp[i++]=t;
        k/=10;
    }
    Length=i;
    for(i=0;i<Length;i++)
        num[i]=temp[i];
    for(i=Length;i<MAX_SIZE;i++)
        num[i]=0;
}
BigNumber::BigNumber(const BigNumber& b)
{
    Length=b.Length;
    for(int i=0;i<MAX_SIZE;i++)
        num[i]=b.num[i];
}
BigNumber::BigNumber(long a[],int front,int size)
{
    Length=size;
    int j=front+size-1,i=0;
    for(;i<Length;i++,j--)
        num[i]=a[j];
    for(int i=Length;i<MAX_SIZE;i++)
        num[i]=0;
}

int BigNumber::BigNToInt()
{
    int result=0,k=1;
    for(int i=0;i<Length;i++){
        result+=num[i]*k;
        k*=10;
    }
    return result;
}

BigNumber& BigNumber::operator=(BigNumber n1)///整体赋值
{
    if(this==&n1)return *this;
    Length=n1.Length;
    for(int i=0;i<MAX_SIZE;i++)
        num[i]=n1.num[i];
    return *this;
}

BigNumber& BigNumber::operator>>(int s)///左移
{
    if(s>=Length)
    {
        for(int i=0;i<Length;i++)num[i]=0;
    }
    for(int i=0;i<Length-s;i++)
    {
        num[i]=num[i+s];
//        cout<<"num[i]= "<<num[i]<<endl;
    }
    for(int i=Length-s;i<MAX_SIZE;i++)
        num[i]=0;
    Length-=s;
    return *this;
}
BigNumber BigNumber::operator<<(int s)///右移
{
    BigNumber temp(-1);
    if(Length+s>MAX_SIZE){
//            cout<<"超出数据最大位数！"<<endl;
            return temp;
    }
    for(int i=Length-1+s;i>=s;i--)
    {
        num[i]=num[i-s];
//        cout<<"num[i]= "<<num[i]<<endl;
    }
    for(int i=0;i<s;i++)
        num[i]=0;
    Length+=s;
    return *this;
}

BigNumber& BigNumber::operator+=(BigNumber& n)
{
    if(&n==this)///加上自己本身
    {
        BigNumber copy(*this);
        *this+=copy;
        return *this;
    }
    int max=Length>n.Length?Length:n.Length;
    BigNumber temp;
    for(int i=0;i<max+3;i++)///将结果赋值给temp
        temp.num[i]=num[i]+n.num[i];
    for(int i=0;i<max+3;i++)///进位
    {
        int k=temp.num[i]%10;
        temp.num[i+1]+=temp.num[i]/10;
        temp.num[i]=k;
    }
    int i;
    for(i=max+2;i>=0;i--)///去0
            if(temp.num[i]!=0)break;
    temp.Length=i+1;
    *this=temp;
    return *this;
}
BigNumber& BigNumber::operator-=(BigNumber& n)
{
    if(&n==this)///减去自己本身
    {
        BigNumber copy(*this);
        *this-=copy;
//        cout<<"test Length="<<Length<<endl;
        return *this;
    }
    int max=Length>n.Length?Length:n.Length;
    BigNumber temp;
    ///判断谁大谁小
    BigNumber n1,n2;
    if(*this>n)
    {
        n1=*this;
        n2=n;
    }
    else
    {
        n1=n;
        n2=*this;
    }
    for(int i=0;i<max+3;i++)///减法运算
    {
        if(n1.num[i]>=n2.num[i])
            temp.num[i]=n1.num[i]-n2.num[i];
        else///不够借1
        {
            n1.num[i+1]--;
            temp.num[i]=10+n1.num[i]-n2.num[i];
        }
    }
//    for(int i=0;i<max+3;i++)
//    {
//        int k=temp.num[i]%10;
//        temp.num[i+1]+=temp.num[i]/10;
//        temp.num[i]=k;
//    }
    int i;
//    cout<<"max="<<max<<endl;
    for(i=max+2;i>=0;i--){///去0
//            cout<<"i="<<i<<endl;
            if(temp.num[i]!=0)break;
    }
    if(i==-1)i=0;
    temp.Length=i+1;
    *this=temp;
//    cout<<"i="<<i<<"  temp  Length="<<temp.Length<<endl;
//    cout<<"test Length="<<Length<<endl;
    return *this;
}
BigNumber& BigNumber::operator*=(BigNumber& n)
{
    if(&n==this)///乘上自己本身
    {
        BigNumber copy(*this);
        *this*=copy;
        return *this;
    }
    int max=Length+n.Length+2;
    BigNumber temp;
    for(int i=0;i<max;i++)///结果赋值给temp
    {
//        int k=1;
        for(int j=0;j<max;j++)
        {
            temp.num[i+j]+=num[i]*n.num[j];
//            temp.num[i]+=num[i]*n.num[j]*k;
//            k*=10;
        }
    }
    for(int i=0;i<max;i++)///进位
    {
//        int k=temp.num[i]%10;
        temp.num[i+1]+=temp.num[i]/10;
        temp.num[i]=temp.num[i]%10;
    }
    int i;
    for(i=max;i>=0;i--)///去0
            if(temp.num[i]!=0)break;
    temp.Length=i+1;
    *this=temp;
    return *this;
}
BigNumber& BigNumber::operator/=(BigNumber& n)
{
    if(&n==this)///除去自己本身
    {
        BigNumber copy(*this);
        *this/=copy;
        return *this;
    }
    *this=*this/n;
    return *this;
}
BigNumber& BigNumber::operator%=(BigNumber& n)
{
    if(&n==this)///对自己取余
    {
        BigNumber copy(*this);
        *this%=copy;
        return *this;
    }
    *this=*this%n;
    return *this;
}

BigNumber operator+(BigNumber& n1,BigNumber& n2)
{
    int max=n1.Length>n2.Length?n1.Length:n2.Length;
    BigNumber temp;
    for(int i=0;i<max+3;i++)///加法运算
        temp.num[i]=n1.num[i]+n2.num[i];
    for(int i=0;i<max+3;i++)///进位
    {
        int k=temp.num[i]%10;
        temp.num[i+1]+=temp.num[i]/10;
        temp.num[i]=k;
    }
    int i;
    for(i=max+2;i>=0;i--)///去0
            if(temp.num[i]!=0)break;
    temp.Length=i+1;
    return temp;
}
BigNumber operator*(BigNumber& n1,BigNumber& n2)
{
    int max=n1.Length+n2.Length+2;
    BigNumber temp;
    for(int i=0;i<max;i++)///乘法运算
    {
//        int k=1;
        for(int j=0;j<max;j++)
        {
            temp.num[i+j]+=n1.num[i]*n2.num[j];///i,j控制赋值位置，减少运算量
//            k*=10;
//            cout<<"temp[i]"<<temp.num[i]<<endl;
//            temp.num[i+1]+=temp.num[i]/10;
//            temp.num[i]=temp.num[i]%10;
        }
    }
    for(int i=0;i<max;i++)///进位
    {
//        int k=temp.num[i]%10;
        temp.num[i+1]+=temp.num[i]/10;
        temp.num[i]=temp.num[i]%10;
    }
    int i;
    for(i=max;i>=0;i--)///去0
            if(temp.num[i]!=0)break;
    temp.Length=i+1;
    return temp;
}
BigNumber operator-(BigNumber& bn1,BigNumber& bn2)
{
    int max=bn1.Length>bn2.Length?bn1.Length:bn2.Length;
    BigNumber temp;
    ///判断谁大谁小
    BigNumber n1,n2;
    if(bn1>bn2)
    {
        n1=bn1;
        n2=bn2;
    }
    else
    {
        n1=bn2;
        n2=bn1;
    }
//    BigNumber copy(bn1);
//    if(&bn1==&bn2){n1=bn1;n2=copy;}
    for(int i=0;i<max+3;i++)///减法运算
    {
        if(n1.num[i]>=n2.num[i])
            temp.num[i]=n1.num[i]-n2.num[i];
        else///不够借1
        {
            n1.num[i+1]--;
            temp.num[i]=10+n1.num[i]-n2.num[i];
        }
    }
//    for(int i=0;i<max+3;i++)
//    {
//        int k=temp.num[i]%10;
//        temp.num[i+1]+=temp.num[i]/10;
//        temp.num[i]=k;
//    }
    int i;
    for(i=max+2;i>=0;i--)///去0
            if(temp.num[i]!=0)break;
    if(i==-1)i=0;
    temp.Length=i+1;
    return temp;
}
BigNumber operator/(BigNumber n1,BigNumber n2)
{
    BigNumber zero,one("1"),No(-1);
//    cout<<"zreo="<<zero<<endl;
    long result[n1.Length],count=0;
    for(int i=0;i<n1.Length;i++)result[i]=0;
    if(n2==zero){
//            cout<<"输入错误，除数不能为0！"<<endl;
            return No;
            }
    else if(n1<n2)return zero;
    else if(n1==n2)return one;
    else
    {
        long l=n1.Length-n2.Length;
        n2<<l;
        for(int i=0;i<=l;i++)///位移运算来循环
        {
//            cout<<"test"<<endl;
            count = 0 ;
//            cout<<"n1="<<n1<<"  n2="<<n2<<endl;
            while(n1>=n2)///当前位移数对应减法次数
            {
//                cout<<"tes1t"<<endl;
                n1-=n2;
//                cout<<"n1="<<n1<<"  n2="<<n2<<endl;
                count++;
            }
//            cout<<"n1="<<n1<<"  n2="<<n2<<endl;
            result[l-i]=count;
//            cout<<"n1.Length="<<n1.Length<<endl;
            if(n1==zero){///整除跳出
//                    cout<<"tes2t"<<endl;
                    break;
                    }
//            n1+=n2;
            n2>>1;
            while(n2>n1)///n1不够大，再向右移，缩小n2
            {
            n2>>1;
            i++;
            }
        }
//        cout<<"result[]= "<<endl;
//        cout<<"n1.Length="<<n1.Length<<endl;
//        for(int i=l;i>=0;i--)
//            cout<<result[i]<<" "<<"i="<<i<<" ";
//        cout<<endl;
        for(int i=l,j=0;i>j;i--,j++)///倒置result数组
        {
            long temp=result[i];
            result[i]=result[j];
            result[j]=temp;
        }
//        cout<<"result[]= "<<endl;
//        for(int i=0;i<=l;i++)cout<<result[i]<<" "<<"i="<<i<<" ";
//        cout<<endl;
        int pos;
        for(pos=0;pos<=l;pos++)///除0
            if(result[pos]!=0)break;
            else l--;
        BigNumber t(result,pos,l+1);
        return t;
    }
}
BigNumber operator%(BigNumber n1,BigNumber n2)
{
    BigNumber zero,one("1");
//    cout<<"zreo="<<zero<<endl;
//    long result[n1.Length],count=0;
//    for(int i=0;i<n1.Length;i++)result[i]=0;
    ///添加跳出处理       可视化处理
    if(n2==zero){cout<<"输入错误，除数不能为0！"<<endl;}
    else if(n1<n2)return n1;
    else if(n1==n2)return zero;
    else
    {
        long l=n1.Length-n2.Length;
        n2<<l;
        for(int i=0;i<=l;i++)///位移循环运算
        {
//            cout<<"test"<<endl;
//            count = 0 ;
//            cout<<"n1="<<n1<<"  n2="<<n2<<endl;
            while(n1>=n2)///当前位移数对应减法次数
            {
//                cout<<"tes1t"<<endl;
                n1-=n2;
//                cout<<"n1="<<n1<<"  n2="<<n2<<endl;
//                count++;
            }
//            cout<<"n1="<<n1<<"  n2="<<n2<<endl;
//            result[l-i]=count;
//            cout<<"n1.Length="<<n1.Length<<endl;
            if(n1==zero){///整除跳出
//                    cout<<"tes2t"<<endl;
                    break;
                    }
//            n1+=n2;
            n2>>1;
            while(n2>n1)///n1不够大，再向右移，缩小n2
            {
            n2>>1;
            i++;
            }
        }
//        cout<<"n1="<<n1<<endl;
//        cout<<"result[]= "<<endl;
//        cout<<"n1.Length="<<n1.Length<<endl;
//        for(int i=l;i>=0;i--)
//            cout<<result[i]<<" "<<"i="<<i<<" ";
//        cout<<endl;
//        for(int i=l,j=0;i>j;i--,j++)
//        {
//            long temp=result[i];
//            result[i]=result[j];
//            result[j]=temp;
//        }
//        cout<<"result[]= "<<endl;
//        for(int i=0;i<=l;i++)cout<<result[i]<<" "<<"i="<<i<<" ";
//        cout<<endl;
//        int pos;
//        for(pos=0;pos<=l;pos++)
//            if(result[pos]!=0)break;
//            else l--;
//        BigNumber t(result,pos,l+1);
        return n1;///n1既为经过除法运算之后剩下的，即余数
    }
    return n1;
}

BigNumber& BigNumber::operator++()
{
    num[0]++;
    for(int i=0;i<Length;i++){
        int k=0;
        if(num[i]>=10)///进位
        {
            k=1;
            num[i]=num[i]-10;
            num[i+1]++;
        }
        if(k==0)break;
    }
    if(num[Length]>0)Length++;/// Length控制
    return *this;
}
BigNumber BigNumber::operator++(int)
{
    BigNumber t(*this);
    ++*this;
    return t;
}
BigNumber& BigNumber::operator--()
{
    num[0]--;
    for(int i=0;i<Length;i++){
        int k=0;
        if(num[i]<0)///不够借1
        {
            k=1;
            num[i]=num[i]+10;
            num[i+1]--;
        }
        if(k==0)break;
    }
    if(num[Length-1]==0)Length--;///Length控制
    return *this;
}
BigNumber BigNumber::operator--(int)
{
    BigNumber t(*this);
    --*this;
    return t;
}

bool operator>(BigNumber& n1,BigNumber& n2)
{
    if(n1.Length>n2.Length)return true;
    else if(n1.Length<n2.Length)return false;
    else
    {
        for(int i=n1.Length-1;i>=0;i--)
            if(n1.num[i]>n2.num[i])return true;
            else if(n1.num[i]<n2.num[i])return false;
    }
    return true;
}
bool operator<(BigNumber& n1,BigNumber& n2)
{
    if(n1.Length<n2.Length)return true;
    else if(n1.Length>n2.Length)return false;
    else
    {
        for(int i=n1.Length-1;i>=0;i--)
            if(n1.num[i]<n2.num[i])return true;
            else if(n1.num[i]>n2.num[i])return false;
    }
    return true;
}
bool operator>=(BigNumber& n1,BigNumber& n2)
{
    if(n1.Length>n2.Length)return true;
    else if(n1.Length<n2.Length)return false;
    else
    {
        for(int i=n1.Length-1;i>=0;i--)
            if(n1.num[i]>n2.num[i])return true;
            else if(n1.num[i]<n2.num[i])return false;
        return true;
    }
    return true;
}
bool operator<=(BigNumber& n1,BigNumber& n2)
{
    if(n1.Length<n2.Length)return true;
    else if(n1.Length>n2.Length)return false;
    else
    {
        for(int i=n1.Length-1;i>=0;i--)
            if(n1.num[i]<n2.num[i])return true;
            else if(n1.num[i]>n2.num[i])return false;
        return true;
    }
    return true;
}
bool operator==(BigNumber& n1,BigNumber& n2)
{
    if(n1.Length>n2.Length)return false;
    else if(n1.Length<n2.Length)return false;
    else
    {
        for(int i=n1.Length-1;i>=0;i--)
            if(n1.num[i]!=n2.num[i])return false;
        return true;
    }
    return true;
}
bool operator!=(BigNumber& n1,BigNumber& n2)
{
    if(n1.Length>n2.Length)return true;
    else if(n1.Length<n2.Length)return true;
    else
    {
        for(int i=n1.Length-1;i>=0;i--)
            if(n1.num[i]!=n2.num[i])return true;
        return false;
    }
    return true;
}

istream& operator>>(istream& is,BigNumber& n)
{
    string temp;
    is>>temp;
    int j=temp.length()-1;
    for(int i=0;i<temp.length();i++,j--)
        n.num[i]=temp[j]-'0';
    for(j=temp.length();j<MAX_SIZE;j++)n.num[j]=0;
    n.Length=temp.length();
    return is;
}
ostream& operator<<(ostream& os,const BigNumber& n)
{
//    int flag=0;
    for(int i=n.Length-1;i>=1;i--)
        {
        os<<n.num[i];
//        flag=1;
        }
    os<<n.num[0];
//    if(flag==0)os<<0;///0的特殊处理
//    os<<endl;
    return os;
}

int BigNumber::length()
{
    return Length;
}
void BigNumber::print()
{
    int flag=0;
    for(int i=Length-1;i>=0;i--)
        {
        cout<<num[i];
        flag=1;
        }
    if(flag==0)cout<<0;///0的特殊处理
    cout<<endl;
}

#endif // BIGNUMBER_H_INCLUDED
