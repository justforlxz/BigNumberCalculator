#include"BigNumber.h"
#include<iostream>///MAX_SIZE   seting
#include<string>
#include<cstdlib>ini

using namespace std;

void calculate();
void menu();
void Next()
{
    cout<<"������ϣ��Ƿ���������򷵻����˵�y/n?"<<endl;
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
    cout<<"                    #  ���Խ��еļ��㣺                              #"<<endl;
    cout<<"                    #         1.�������㣺+ - * /                    #"<<endl;
    cout<<"                    #         2.��С�Ƚ����� >  <  >=  <=  =  !=     #"<<endl;
    cout<<"                    #         3.�����ƣ�<<  >>                       #"<<endl;
    cout<<"                    #                                                #"<<endl;
    cout<<"                     ################################################ "<<endl<<endl;
    cout<<"������Ҫ���еļ���ʽ������a+b��֮��س���"<<endl;
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
        cout<<"�������ʽ�����趨�ļ��㷶Χ���Ƿ񷵻����˵������趨��y/n?"<<endl;
        char ch;
        cin>>ch;
        if(ch=='y'||ch=='Y'){system("cls");menu();}
        else goto loop;
    }

    int i;
    for(i=0;i<temp.length();i++)
        if(!checkNumber(temp[i]))break;
    char sign=temp[i];

    ///��һ����
    string A_temp=temp.substr(0,i);
    BigNumber A(A_temp);

    if((temp[i]=='<'&&(temp[i+1]=='<'||temp[i+1]=='='||checkNumber(temp[i+1])))||
       (temp[i]=='>'&&(temp[i+1]=='>'||temp[i+1]=='='||checkNumber(temp[i+1])))||
       (temp[i]=='='&&checkNumber(temp[i+1]))||
       (temp[i]=='!'&&temp[i+1]=='=')||
       ((temp[i]=='+'||temp[i]=='-'||temp[i]=='*'||temp[i]=='/')&&checkNumber(temp[i+1])));
    else
    {
        cout<<"��ʽ����������������룡"<<endl;
        system("pause");
        system("cls");
        goto loop;
    }

    if(!checkNumber(temp[i+1])){i++;flag=1;}

    ///�ڶ�����
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
             if((A/B).length()==-1)cout<<"������󣬳�������Ϊ0��"<<endl;
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
             else cout<<"��ʽ�������"<<endl;
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
                 if((A<<B.BigNToInt()).length()==-1)cout<<"�����������λ����"<<endl;
                 else
                 cout<<A<<endl;
             }
             else cout<<"��ʽ�������"<<endl;
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
            cout<<"��ʽ����������������룡"<<endl;
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
    cout<<"                    #         1.����������                           #"<<endl;
    cout<<"                    #         2.������λ������                     #"<<endl;
    cout<<"                    #         3.�˳�ϵͳ                             #"<<endl;
    cout<<"                    #                                                #"<<endl;
    cout<<"                     ################################################ "<<endl;
    string temp;
    int pos;
    cout<<"���������������Ӧ�����"<<endl;
    loop:
        cin>>temp;
        if(temp=="1")pos=1;else if(temp=="2")pos=2;else if(temp=="3")pos=3;else{
            cout<<"û�ж�Ӧ��ŵĲ��������������룺"<<endl;goto loop;}
    switch(pos)
    {
        case 1:system("cls");calculate();break;
        case 2:system("cls");seting();break;
        case 3:exit(0);break;
        default:cout<<"û�ж�Ӧ��ŵĲ��������������룺"<<endl;goto loop;
    }
}

