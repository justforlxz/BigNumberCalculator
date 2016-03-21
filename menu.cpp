#include"BigNumber.h"
#include<iostream>///MAX_SIZE   seting
#include<string>
#include<cstdlib>ini

using namespace std;

void calculate();
void menu();
void Next()
{
    cout<<"计算完毕，是否继续？否则返回主菜单y/n?"<<endl;
    char ch;
    cin>>ch;
    if(ch=='y'||ch=='Y')
    {
        system("cls");
        calculate();
    }
    else {
            system("cls");
            menu();
    }
}
bool checkNumber(char ch)
{
    if(ch>='0'&&ch<='9')return true;
    else return false;
}

void display()
{
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"                     ################################################ "<<endl;
    cout<<"                    #                                                #"<<endl;
    cout<<"                    #  可以进行的计算：                              #"<<endl;
    cout<<"                    #         1.四则运算：+ - * /                    #"<<endl;
    cout<<"                    #         2.大小比较运算 >  <  >=  <=  =  !=     #"<<endl;
    cout<<"                    #         3.左右移：<<  >>                       #"<<endl;
    cout<<"                    #                                                #"<<endl;
    cout<<"                     ################################################ "<<endl<<endl;
    cout<<"请输入要进行的计算式，形如a+b，之后回车："<<endl;
}
void seting()
{

}
void calculate()
{
    loop:
    display();
    string temp;
    int flag=0;
    cin>>temp;

    if(temp.length()>MAX_SIZE*2+2)
    {
        cout<<"输入的算式超出设定的计算范围！是否返回主菜单重新设定？y/n?"<<endl;
        char ch;
        cin>>ch;
        if(ch=='y'||ch=='Y'){system("cls");menu();}
        else goto loop;
    }

    int i;
    for(i=0;i<temp.length();i++)
        if(!checkNumber(temp[i]))break;
    char sign=temp[i];

    ///第一个数
    string A_temp=temp.substr(0,i);
    BigNumber A(A_temp);

    if((temp[i]=='<'&&(temp[i+1]=='<'||temp[i+1]=='='||checkNumber(temp[i+1])))||
       (temp[i]=='>'&&(temp[i+1]=='>'||temp[i+1]=='='||checkNumber(temp[i+1])))||
       (temp[i]=='='&&checkNumber(temp[i+1]))||
       (temp[i]=='!'&&temp[i+1]=='=')||
       ((temp[i]=='+'||temp[i]=='-'||temp[i]=='*'||temp[i]=='/')&&checkNumber(temp[i+1])));
    else
    {
        cout<<"算式输入错误，请重新输入！"<<endl;
        system("pause");
        system("cls");
        goto loop;
    }

    if(!checkNumber(temp[i+1])){i++;flag=1;}

    ///第二个数
    string B_temp=temp.substr(i+1,temp.length()-i);
    BigNumber B(B_temp);

//    BigNumber C=A<<B.BigNToInt();
//    cout<<"A="<<A_temp<<"   B="<<B_temp<<endl;
//    cout<<"A<<B="<<A<<B.BigNToInt()<<endl;
//    A>>B.BigNToInt();
//    if(!checkNumber(temp[i-1]))i--;
    switch(sign)
    {
    case '+':system("cls");display();cout<<A<<sign;
             if(flag==1)cout<<temp[i];
             cout<<B<<"="<<A+B<<endl;
             Next();
             break;
    case '-':system("cls");display();cout<<A<<sign;
             if(flag==1)cout<<temp[i];
             cout<<B<<"="<<A-B<<endl;
             Next();
             break;
    case '*':system("cls");display();cout<<A<<sign;
             if(flag==1)cout<<temp[i];
             cout<<B<<"="<<A*B<<endl;
             Next();
             break;
    case '/':system("cls");display();cout<<A<<sign;
             if(flag==1)cout<<temp[i];
//             cout<<endl<<"A="<<A<<"   B="<<B<<endl;
//             cout<<"A/B="<<A/B<<"   A%B="<<A%B<<endl<<"***********"<<endl;
             cout<<B<<"=";
             if((A/B).length()==-1)cout<<"输入错误，除数不能为0！"<<endl;
             else
             cout<<A/B<<"......"<<A%B<<endl;
             Next();
             break;

    case '>':system("cls");display();cout<<A<<sign;
             if(flag==1)cout<<temp[i];
             cout<<B<<":";
             if(flag==0)
             {
                 if(A>B)cout<<"true"<<endl;
                 else cout<<"false"<<endl;
             }
             else if(temp[i]=='=')
             {
                 if(A>=B)cout<<"true"<<endl;
                 else cout<<"false"<<endl;
             }
             else if(temp[i]=='>')
                 cout<<(A>>B.BigNToInt())<<endl;
             else cout<<"算式输入错误！"<<endl;
             Next();
             break;
    case '<':system("cls");display();cout<<A<<sign;
             if(flag==1)cout<<temp[i];
             cout<<B<<":";
             if(flag==0)
             {
                 if(A<B)cout<<"true"<<endl;
                 else cout<<"false"<<endl;
             }
             else if(temp[i]=='=')
             {
                 if(A<=B)cout<<"true"<<endl;
                 else cout<<"false"<<endl;
             }
             else if(temp[i]=='<')
             {
                 if((A<<B.BigNToInt()).length()==-1)cout<<"超出数据最大位数！"<<endl;
                 else
                 cout<<A<<endl;
             }
             else cout<<"算式输入错误！"<<endl;
             Next();
             break;
    case '=':system("cls");display();cout<<A<<sign;
             if(flag==1)cout<<temp[i];
             cout<<B<<":";
             if(A==B)cout<<"true"<<endl;
             else cout<<"false"<<endl;
             Next();
             break;
    case '!':system("cls");display();cout<<A<<sign;
             if(flag==1)cout<<temp[i];
             cout<<B<<":";
             if(A!=B)cout<<"true"<<endl;
             else cout<<"false"<<endl;
             Next();
             break;
    default:system("cls");display();
            cout<<"算式输入错误，请重新输入！"<<endl;
            system("pause");
            goto loop;
    }
}

void menu()
{
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"                     ################################################ "<<endl;
    cout<<"                    #                                                #"<<endl;
    cout<<"                    #         1.大数计算器                           #"<<endl;
    cout<<"                    #         2.最大计算位数设置                     #"<<endl;
    cout<<"                    #         3.退出系统                             #"<<endl;
    cout<<"                    #                                                #"<<endl;
    cout<<"                     ################################################ "<<endl;
    string temp;
    int pos;
    cout<<"请输入所需操作对应的序号"<<endl;
    loop:
        cin>>temp;
        if(temp=="1")pos=1;else if(temp=="2")pos=2;else if(temp=="3")pos=3;else{
            cout<<"没有对应序号的操作，请重新输入："<<endl;goto loop;}
    switch(pos)
    {
        case 1:system("cls");calculate();break;
        case 2:system("cls");seting();break;
        case 3:exit(0);break;
        default:cout<<"没有对应序号的操作，请重新输入："<<endl;goto loop;
    }
}

