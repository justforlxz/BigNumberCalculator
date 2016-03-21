#include<iostream>
#include<string>
#include<cstring>///    /=  %=  /  %      BigNum和普通数据类型的运算     运算之后答案是负数的情况   是小数的情况   减法负号问题
#define MAX_SIZE 100
using namespace std;
class BigNum
{
    long num[MAX_SIZE];///数组倒置储存，方便进位操作
    int Length;
public:
    BigNum();
    BigNum(char* str);
    BigNum(const char* str);
    BigNum(string s);
    BigNum(long val);
    BigNum(const BigNum& b);
    BigNum(long a[],int front,int size);
    void change(long a[],int front,int size);
    int length();
    void print();

    BigNum& operator=(BigNum n1);

    friend bool operator>(BigNum& n1,BigNum& n2);
    friend bool operator<(BigNum& n1,BigNum& n2);
    friend bool operator>=(BigNum& n1,BigNum& n2);
    friend bool operator<=(BigNum& n1,BigNum& n2);
    friend bool operator==(BigNum& n1,BigNum& n2);
    friend bool operator!=(BigNum& n1,BigNum& n2);

    BigNum& operator>>(int s);
    BigNum& operator<<(int s);

    friend BigNum operator+(BigNum& n1,BigNum& n2);
    friend BigNum operator*(BigNum& n1,BigNum& n2);
    friend BigNum operator-(BigNum& bn1,BigNum& bn2);
    friend BigNum operator/(BigNum& n1,BigNum& n2);
    friend BigNum operator%(BigNum& n1,BigNum& n2);

    BigNum& operator+=(BigNum& n);
    BigNum& operator-=(BigNum& n);
    BigNum& operator*=(BigNum& n);
    BigNum& operator/=(BigNum& n);
    BigNum& operator%=(BigNum& n);

    BigNum& operator++();
    BigNum operator++(int);
    BigNum& operator--();
    BigNum operator--(int);

    friend istream& operator>>(istream& is,BigNum& n);
    friend ostream& operator<<(ostream& os,const BigNum& n);
};

BigNum::BigNum()
{
    for(int i=0;i<MAX_SIZE;i++)
    num[i]=0;
    Length=1;
}
BigNum::BigNum(char* str)
{
    Length=strlen(str);
    int j=Length-1;
    for(int i=0;i<Length;i++,j--)
        num[i]=str[j]-'0';
    for(int i=Length;i<MAX_SIZE;i++)
        num[i]=0;
}
BigNum::BigNum(const char* str)
{
    Length=strlen(str);
    int j=Length-1;
    for(int i=0;i<Length;i++,j--)
        num[i]=str[j]-'0';
    for(int i=Length;i<MAX_SIZE;i++)
        num[i]=0;
}
BigNum::BigNum(string s)
{
    Length=s.length();
    int j=Length-1;
    for(int i=0;i<Length;i++,j--)
        num[i]=s[j]-'0';
    for(int i=Length;i<MAX_SIZE;i++)
        num[i]=0;
}
BigNum::BigNum(long val)
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
BigNum::BigNum(const BigNum& b)
{
    Length=b.Length;
    for(int i=0;i<MAX_SIZE;i++)
        num[i]=b.num[i];
}
BigNum::BigNum(long a[],int front,int size)
{
    Length=size;
    int j=front+size-1,i=0;
    for(;i<Length;i++,j--)
        num[i]=a[j];
    for(int i=Length;i<MAX_SIZE;i++)
        num[i]=0;
}
///暂定
void BigNum::change(long a[],int front,int size)
{
    Length=size;
    int j=front+size-1,i=0;
    for(;i<Length;i++,j--)
        num[i]=a[j];
    for(int i=Length;i<MAX_SIZE;i++)
        num[i]=0;
}

BigNum& BigNum::operator=(BigNum n1)
{
    if(this==&n1)return *this;
    Length=n1.Length;
    for(int i=0;i<MAX_SIZE;i++)
        num[i]=n1.num[i];
}

BigNum& BigNum::operator>>(int s)
{
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
BigNum& BigNum::operator<<(int s)
{
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

BigNum& BigNum::operator+=(BigNum& n)
{
    if(&n==this)
    {
        BigNum copy(*this);
        *this+=copy;
        return *this;
    }
    int max=Length>n.Length?Length:n.Length;
    BigNum temp;
    for(int i=0;i<max+3;i++)
        temp.num[i]=num[i]+n.num[i];
    for(int i=0;i<max+3;i++)
    {
        int k=temp.num[i]%10;
        temp.num[i+1]+=temp.num[i]/10;
        temp.num[i]=k;
    }
    int i;
    for(i=max+2;i>=0;i--)
            if(temp.num[i]!=0)break;
    temp.Length=i+1;
    *this=temp;
    return *this;
}
BigNum& BigNum::operator-=(BigNum& n)
{
    if(&n==this)
    {
        BigNum copy(*this);
        *this-=copy;
        return *this;
    }
    int max=Length>n.Length?Length:n.Length;
    BigNum temp;
    ///判断谁大谁小
    BigNum n1,n2;
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
    for(int i=0;i<max+3;i++)
    {
        if(n1.num[i]>=n2.num[i])
            temp.num[i]=n1.num[i]-n2.num[i];
        else
        {
            temp.num[i+1]--;
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
    for(i=max+2;i>=0;i--)
            if(temp.num[i]!=0)break;
    temp.Length=i+1;
    *this=temp;
    return *this;
}
BigNum& BigNum::operator*=(BigNum& n)
{
    if(&n==this)
    {
        BigNum copy(*this);
        *this*=copy;
        return *this;
    }
    int max=Length+n.Length+2;
    BigNum temp;
    for(int i=0;i<max;i++)
    {
//        int k=1;
        for(int j=0;j<max;j++)
        {
            temp.num[i+j]+=num[i]*n.num[j];
//            temp.num[i]+=num[i]*n.num[j]*k;
//            k*=10;
        }
    }
    for(int i=0;i<max;i++)
    {
//        int k=temp.num[i]%10;
        temp.num[i+1]+=temp.num[i]/10;
        temp.num[i]=temp.num[i]%10;
    }
    int i;
    for(i=max;i>=0;i--)
            if(temp.num[i]!=0)break;
    temp.Length=i+1;
    *this=temp;
    return *this;
}
BigNum& BigNum::operator/=(BigNum& n)
{
    if(&n==this)
    {
        BigNum copy(*this);
        *this/=copy;
        return *this;
    }
//    *this=*this/n;
//    return *this;
}
BigNum& BigNum::operator%=(BigNum& n)
{
    if(&n==this)
    {
        BigNum copy(*this);
        *this%=copy;
        return *this;
    }
//    *this=*this%n;
//    return *this;
}

BigNum operator+(BigNum& n1,BigNum& n2)
{
    int max=n1.Length>n2.Length?n1.Length:n2.Length;
    BigNum temp;
    for(int i=0;i<max+3;i++)
        temp.num[i]=n1.num[i]+n2.num[i];
    for(int i=0;i<max+3;i++)
    {
        int k=temp.num[i]%10;
        temp.num[i+1]+=temp.num[i]/10;
        temp.num[i]=k;
    }
    int i;
    for(i=max+2;i>=0;i--)
            if(temp.num[i]!=0)break;
    temp.Length=i+1;
    return temp;
}
BigNum operator*(BigNum& n1,BigNum& n2)
{
    int max=n1.Length+n2.Length+2;
    BigNum temp;
    for(int i=0;i<max;i++)
    {
//        int k=1;
        for(int j=0;j<max;j++)
        {
            temp.num[i+j]+=n1.num[i]*n2.num[j];
//            k*=10;
//            cout<<"temp[i]"<<temp.num[i]<<endl;
//            temp.num[i+1]+=temp.num[i]/10;
//            temp.num[i]=temp.num[i]%10;
        }
    }
    for(int i=0;i<max;i++)
    {
//        int k=temp.num[i]%10;
        temp.num[i+1]+=temp.num[i]/10;
        temp.num[i]=temp.num[i]%10;
    }
    int i;
    for(i=max;i>=0;i--)
            if(temp.num[i]!=0)break;
    temp.Length=i+1;
    return temp;
}
BigNum operator-(BigNum& bn1,BigNum& bn2)
{
    int max=bn1.Length>bn2.Length?bn1.Length:bn2.Length;
    BigNum temp;
    ///判断谁大谁小
    BigNum n1,n2;
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
//    BigNum copy(bn1);
//    if(&bn1==&bn2){n1=bn1;n2=copy;}
    for(int i=0;i<max+3;i++)
    {
        if(n1.num[i]>=n2.num[i])
            temp.num[i]=n1.num[i]-n2.num[i];
        else
        {
            temp.num[i+1]--;
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
    for(i=max+2;i>=0;i--)
            if(temp.num[i]!=0)break;
    temp.Length=i+1;
    return temp;
}
BigNum operator/(BigNum& n1,BigNum& n2)
{
//    int size=n2.Length-1,result[n1.Length];
//    ///提取n1中最高位起size位
//    int t[size],j=0;
//    for(int i=n1.Length-1;i>=n1.Length-size;i--)
//        t[j++]=n1.num[i];
//    BigNum temp(t,0,size);
//    int pos=0;
//    while(temp>=n2){pos++;temp-=n2;}
//    if(pos==0)temp.change(t,0,)
    int l=n1.Length-n2.Length;
    BigNum k;
    if(l<0)return k;
///l==0的是否与l>0的有重复
    else if(l==0){
        n1-=n2;
        int count;
        if(n1<k)return k;
        else
        {
            while(n1>=k){
                count++;
                n1-=n2;
            }
        }
        return BigNum(count);
    }
    else
    {
    long a[l+1],result[n1.Length+1],pos=0;
    for(int i=0;i<n1.Length+1;i++)result[i]=0;
    for(int i=1;i<l+1;i++)a[i]=0;
    a[0]=1;
    BigNum t(a,0,l+1),n3;

///循环条件
    for(int i=0;i<l;i++){
    n3=n2*t;
    cout<<"n3="<<n3<<endl;
    n1-=n3;
    int count=0;
    if(n1<k)break;
    else
    {

//        while(n1>=k){
//            count++;
//            n1-=n3;
//            cout<<"test"<<endl;
//        }

        result[pos++]=count;
    }

    t.change(a,0,l-i);
    }
    for(int i=0;i<pos;i++)
        cout<<result[i];
    cout<<endl;
    BigNum temp(result,0,pos);
    return temp;
    }
///result数组反向调换    数据返回值处理
}
BigNum operator%(BigNum& n1,BigNum& n2)
{

}

BigNum& BigNum::operator++()
{
    num[0]++;
    for(int i=0;i<Length;i++){
        int k=0;
        if(num[i]>=10)
        {
            k=1;
            num[i]=num[i]-10;
            num[i+1]++;
        }
        if(k==0)break;
    }
    if(num[Length]>0)Length++;
    return *this;
}
BigNum BigNum::operator++(int)
{
    BigNum t(*this);
    ++*this;
    return t;
}
BigNum& BigNum::operator--()
{
    num[0]--;
    for(int i=0;i<Length;i++){
        int k=0;
        if(num[i]<0)
        {
            k=1;
            num[i]=num[i]+10;
            num[i+1]--;
        }
        if(k==0)break;
    }
    if(num[Length-1]==0)Length--;
    return *this;
}
BigNum BigNum::operator--(int)
{
    BigNum t(*this);
    --*this;
    return t;
}

bool operator>(BigNum& n1,BigNum& n2)
{
    if(n1.Length>n2.Length)return true;
    else if(n1.Length<n2.Length)return false;
    else
    {
        for(int i=n1.Length-1;i>=0;i--)
            if(n1.num[i]>n2.num[i])return true;
            else if(n1.num[i]<n2.num[i])return false;
    }
}
bool operator<(BigNum& n1,BigNum& n2)
{
    if(n1.Length<n2.Length)return true;
    else if(n1.Length>n2.Length)return false;
    else
    {
        for(int i=n1.Length-1;i>=0;i--)
            if(n1.num[i]<n2.num[i])return true;
            else if(n1.num[i]>n2.num[i])return false;
    }
}
bool operator>=(BigNum& n1,BigNum& n2)
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
}
bool operator<=(BigNum& n1,BigNum& n2)
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
}
bool operator==(BigNum& n1,BigNum& n2)
{
    if(n1.Length>n2.Length)return false;
    else if(n1.Length<n2.Length)return false;
    else
    {
        for(int i=n1.Length-1;i>=0;i--)
            if(n1.num[i]!=n2.num[i])return false;
        return true;
    }
}
bool operator!=(BigNum& n1,BigNum& n2)
{
    if(n1.Length>n2.Length)return true;
    else if(n1.Length<n2.Length)return true;
    else
    {
        for(int i=n1.Length-1;i>=0;i--)
            if(n1.num[i]!=n2.num[i])return true;
        return false;
    }
}

istream& operator>>(istream& is,BigNum& n)
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
ostream& operator<<(ostream& os,const BigNum& n)
{
    int flag=0;
    for(int i=n.Length-1;i>=0;i--)
        {
        os<<n.num[i];
        flag=1;
        }
    if(flag==0)cout<<0;
//    os<<endl;
    return os;
}

int BigNum::length()
{
    return Length;
}
void BigNum::print()
{
    int flag=0;
    for(int i=Length-1;i>=0;i--)
        {
        cout<<num[i];
        flag=1;
        }
    if(flag==0)cout<<0;
    cout<<endl;
}
int main()
{
    BigNum a,b;
    cin>>a>>b;
    a>>2;
    b<<3;
    cout<<"a>>2:    "<<a<<"     a  Length:"<<a.length()<<endl;
    cout<<"b<<3:    "<<b<<"     b  Length:"<<b.length()<<endl;
//    BigNum n1(128),n2("128"),n3,n4("111111111111"),n5("127");///12位
//    cout<<"n1=";n1.print();
//    cout<<"n2=";n2.print();
//    cout<<"n3=";n3.print();
//    cin>>n3;
//    cout<<n3<<endl;
//    cout<<"n4.Length="<<n4.length()<<endl;
//    n3=n4;n3.print();
//
//    cout<<"case 1:"<<endl;
//    cout<<n1;
//    n1>n2?cout<<">":n1==n2?cout<<"=":cout<<"<";
//    cout<<n2<<endl;
//
//    cout<<"case 2:"<<endl;
//    cout<<n1;
//    n1>n5?cout<<">":n1==n5?cout<<"=":cout<<"<";
//    cout<<n5<<endl;
//
//    cout<<"case 3:"<<endl;
//    cout<<n5;
//    n5>n2?cout<<">":n5==n2?cout<<"=":cout<<"<";
//    cout<<n2<<endl;
//
//    cout<<"case 4:"<<endl;
//    cout<<n1;
//    n1>=n2?cout<<">=":cout<<"<";
//    cout<<n2<<endl;
//
//    cout<<"case 5:"<<endl;
//    cout<<n5;
//    n5<=n2?cout<<"<=":cout<<">";
//    cout<<n2<<endl;
//
//    cout<<"case 6:"<<endl;
//    cout<<n1;
//    n1==n2?cout<<"==":cout<<"!=";
//    cout<<n2<<endl;
//
//    cout<<"case 7:"<<endl;
//    cout<<n1;
//    n1!=n2?cout<<"!=":cout<<"==";
//    cout<<n2<<endl;
//
//    cout<<endl<<"+"<<endl;
//    n3=n1+n2;cout<<"n1+n2=";n3.print();
//    n3=n1+n1;cout<<"n1+n1=";n3.print();
//    n3+=n1;cout<<"n3+=n1:";n3.print();
//    n3+=n3;cout<<"n3+=n3:";n3.print();
//
//
//    cout<<endl<<"-"<<endl;
//    n3=n1-n5;cout<<"n1-n5=";n3.print();
//    n3=n1-n1;cout<<"n1-n1=";n3.print();
//    n3=n1;
//    n3-=n5;cout<<"n3-=n5:";n3.print();
//    n3=n1;
//    n3-=n3;cout<<"n3-=n3:";n3.print();
//
//    cout<<endl<<"*"<<endl;
//    n3=n1*n2;cout<<"n1*n2=";n3.print();
//    n3=n1*n1;cout<<"n1*n1=";n3.print();
//    n3=n1;
//    n3*=n5;cout<<"n3*=n5:";n3.print();
//    n3=n1;
//    n3*=n3;cout<<"n3*=n3:";n3.print();
//
//    cout<<endl<<"++"<<endl;
//    n3=n1;cout<<"n3="<<n3<<",++n3="<<++n3<<",n3++="<<n3++<<endl;
//    cout<<"n3="<<n3<<endl;
//
//    cout<<endl<<"++"<<endl;
//    n3=n1;cout<<"n3="<<n3;
//    ++n3;
//    cout<<",++n3="<<n3;
//    n3++;
//    cout<<",n3++="<<n3<<endl;
//    cout<<"n3="<<n3<<endl;
//
//    cout<<endl<<"--"<<endl;
//    n3=n1;cout<<"n3="<<n3<<",--n3="<<--n3<<",n3--="<<n3--<<endl;
//    cout<<"n3="<<n3<<endl;
//
//    cout<<endl<<"--"<<endl;
//    n3=n1;cout<<"n3="<<n3;
//    --n3;
//    cout<<",--n3="<<n3;
//    n3--;
//    cout<<",n3--="<<n3<<endl;
//    cout<<"n3="<<n3<<endl;
}
