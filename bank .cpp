/*
* Vishal Verma
*23/11/2015
*/

# include<iostream>
# include<stdio.h>
# include<string.h>
# include<fstream>
# include<iomanip>
# include<stdlib.h>
# include<windows.h>
# include<conio.h>
using namespace std;

class account
{
private:
    int acc_no;
    char name[15];
    char password[15];
    long long mobile;
    double balance;

public:
    void acc_add()
    {
        int temp_acc_no= 0, i = 0, j = 0;
        char ch;
        bool flag = true;
        char temp_pass1[15];
        char temp_pass2[15];

        system("cls");

        account member;

        do
        {
            cout<<"Enter Account Number : ";
            cin>>temp_acc_no;

            ifstream input("vishal.bin", ios :: binary | ios :: app);

            while(input.read((char*)&member, sizeof(member)))
            {
                if(member.return_acc_no() == temp_acc_no)
                {
                    cout<<"Error : Account Number already exist.\nTry Again."<<endl;
                    flag = false;
                    cout<<endl<<"Press Enter to continue";
                    getch();
                    system("cls");
                    break;
                }
                else if(member.return_acc_no() != temp_acc_no)
                {
                    flag = true;
                }
            }
            input.close();
        }while(flag == false);

        acc_no = temp_acc_no;

        int pass_flag = 0;

        do
        {
            system("cls");
            cout<<"Enter Your Account Password : ";
            i = 0;
            while(1)
            {
                if(i<0)
                    i = 0;
                temp_pass1[i] = getch();
                 if (temp_pass1[i] == 0x08)
                    i = i-2;
                system("cls");
                cout<<"Enter Your Account Password : ";
                for(j = 0; j <= i; j++)
                    cout<<"*";
                if(temp_pass1[i] == 0x1b || temp_pass1[i] == 0x0d)
                    break;
                i++;
            }

            temp_pass1[i] = '\0';

            system("cls");
            cout<<endl<<"Please Confirm Password by re-entering : ";
            i = 0;
            while(1)
            {
                if(i<0)
                    i = 0;
                temp_pass2[i] = getch();
                 if (temp_pass2[i] == 0x08)
                    i = i-2;
                system("cls");
                cout<<"Please Confirm Password by re-entering : ";
                for(j = 0; j <= i; j++)
                    cout<<"*";
                if(temp_pass2[i] == 0x1b || temp_pass2[i] == 0x0d)
                    break;
                i++;
            }
            temp_pass2[i] = '\0';
            system("cls");

            pass_flag = strcmp(temp_pass1,temp_pass2);
            if(pass_flag != 0)
            {
                cout<<endl<<"Error Password Do Not Match !!"<<endl<<"Press Enter to Try Again";
                getch();
                continue;
            }

        }while(pass_flag != 0);

        strcpy(password,temp_pass1);

        cout<<endl<<"Enter Name : ";
        fflush(stdin);
        i = 0;
        while((ch=getchar())!='\n')
        {
            name[i++] = ch;
        }
        name[i] = '\0';

        cout<<"Enter Mobile Number : ";
        cin>>mobile;

        cout<<"Enter Account Balance : ";
        cin>>balance;

        system("cls");
        cout<<"Account Created !!!";
        Sleep(1500);
        system("cls");
    }



    int acc_delete()
    {
        system("cls");
        int temp_acc_no = 0;
        bool flag = false;

        account member;

        while(flag == false)
        {
            system("cls");
            cout<<"Enter Account Number : ";
            cin>>temp_acc_no;

            ifstream input("vishal.bin", ios :: binary | ios :: app);

            while(input.read((char*)&member, sizeof(member)))
            {
                if(member.return_acc_no() == temp_acc_no)
                {
                    flag = true;
                    break;
                }
            }
            input.close();
            if(flag == false)
            {
                char temp;
                cout<<endl<<"Error : No such account found.\nTry Again."<<endl<<endl;
                cout<<"Press R To Retry Or any key to exit ";
                temp = getch();
                if (temp == 'R' || temp == 'r')
                    continue;
                else
                    return 0;
                system("cls");
            }
        }

        char temp_pass[15];
        char ch;
        int i = -1, pass_flag = 0;
        do
        {
        system("cls");
        cout<<"Enter Your Account Password : ";
        i = -1;
        pass_flag = 0;

        while(temp_pass[i] != 13 /*&& temp_pass[i] != 8*/)
        {
            temp_pass[++i] = getch();
            cout<<"*";
        }
        temp_pass[i] = '\0';

        pass_flag = strcmp(temp_pass,member.password);
        if(pass_flag != 0)
        {
            cout<<endl<<"Error Password Do Not Match !!"<<endl<<"Press Enter to Y Again Or any key to EXIT";
            ch = getch();
            if (ch != 'y' && ch != 'Y')
                return 0;

        }
        }while(pass_flag != 0);


        ifstream input("vishal.bin", ios :: binary | ios :: app);
        ofstream output("temp.bin", ios :: binary | ios :: app);

        while(input.read((char*)&member, sizeof(member)))
        {
            if(member.return_acc_no() != temp_acc_no)
            {
                output.write((char*)&member, sizeof(member));
            }
        }

        input.close();
        output.close();
        remove("vishal.bin");
        rename("temp.bin","vishal.bin");
        system("cls");
        cout<<"Account Deleted !!!";
        Sleep(2000);
        system("cls");
    }

    void show_all()
    {
        system("cls");
        cout<<"Account Number : "<<acc_no<<endl;
        cout<<"Name : "<<name<<endl;
        cout<<"Mobile Number : "<<mobile<<endl;
        cout<<"Current Balance : "<<balance<<endl<<endl;
        cout<<"Press Enter to continue";
        getch();
    }

    void show_detail()
    {
        system("cls");
        ifstream input("vishal.bin", ios :: binary);

        account member;
        int num = 1;

        cout.setf( ios :: left, ios :: adjustfield);

        cout<<"S.No  "<<setw(15)<<"NAME"<<setw(12)<<"ACCOUNT NO."<<setw(12)<<"MOBILE NO."<<setw(15)<<"BALANCE"<<endl;

        while(input.read((char*)&member, sizeof(member)))
        {
            cout<<setw(6)<<num++<<setw(15)<<member.name<<setw(12)<<member.acc_no<<setw(12)<<member.mobile<<setw(15)<<member.balance<<endl;
        }
        cout<<endl;
        cout<<"Press Any Key To Continue"<<endl;
        getch();
        system("cls");

        input.close();
    }

    int show()
    {
        int temp_acc_no = 0;
        bool flag = false;

        system("cls");

        ifstream input("vishal.bin", ios :: binary);

        account member;

        cout<<"Enter Account Number To See Details : ";
        cin>>temp_acc_no;

        while(input.read((char*)&member, sizeof(member)))
        {
            if(member.return_acc_no() == temp_acc_no)
            {
                flag = true;
                char temp_pass[15];
                char ch;
                int i = -1, pass_flag = 0;
                do
                {
                system("cls");
                cout<<"Enter Your Account Password : ";
                i = -1;
                pass_flag = 0;

                while(temp_pass[i] != 13)
                {
                    temp_pass[++i] = getch();
                    cout<<"*";
                }
                temp_pass[i] = '\0';

                pass_flag = strcmp(temp_pass,member.password);
                if(pass_flag != 0)
                {
                    cout<<endl<<"Error Password Do Not Match !!"<<endl<<"Press Enter to Y Again Or any key to EXIT";
                    ch = getch();
                    if (ch != 'y' && ch != 'Y')
                        return 0;

                }
                }while(pass_flag != 0);

                member.show_all();
                system("cls");
                break;
            }
        }

        if(flag == false)
        {
            cout<<endl<<"Error : No Account found with "<<temp_acc_no<<" number."<<endl;
            cout<<"Press Enter to continue"<<endl;
            getch();
            system("cls");
        }
    }
    void credit()
    {
        int temp_acc_no = 0, credit_amount = 0;
        bool flag = false;
        system("cls");
        cout<<"Enter Account Number To Deposit Amount :";
        cin>>temp_acc_no;
        cout<<"Enter the Amount to be Deposited : ";
        cin>>credit_amount;

        fstream modify("vishal.bin", ios :: binary | ios :: in | ios :: out);

        account member;

        while(modify.read((char*)&member, sizeof(member)))
        {
            if(member.return_acc_no() == temp_acc_no)
            {
                flag = true;
                member.balance += credit_amount;
                int shift_back = -1*sizeof(member);
                modify.seekp(shift_back, ios :: cur);
                modify.write((char*)&member, sizeof(member));
                modify.seekg(shift_back, ios :: cur);
                modify.read((char*)&member, sizeof(member));
                system("cls");
                cout<<"Transaction Successful !!!"<<endl;
                cout<<"New balance is "<<member.balance<<endl;
                Sleep(2000);
                system("cls");
            }
        }

        if(flag == false)
        {

            cout<<endl<<"Error : No Account found with "<<temp_acc_no<<" number."<<endl;
            cout<<"Press Enter to continue"<<endl;
            getch();
            system("cls");
        }
    }

    int debit()
    {
        int temp_acc_no = 0, debit_amount = 0;
        bool flag = false;
        system("cls");
        cout<<"Enter Account Number To Withdraw Amount :";
        cin>>temp_acc_no;
        cout<<"Enter the Amount to be Withdrawn : ";
        cin>>debit_amount;

        fstream modify("vishal.bin", ios :: binary | ios :: in | ios :: out);

        account member;

        while(modify.read((char*)&member, sizeof(member)))
        {
            if(member.return_acc_no() == temp_acc_no)
            {
                flag = true;
                char temp_pass[15];
                char ch;
                int i = -1, pass_flag = 0;
                do
                {
                system("cls");
                cout<<"Enter Your Account Password : ";
                i = -1;
                pass_flag = 0;

                while(temp_pass[i] != 13 /*&& temp_pass[i] != 8*/)
                {
                    temp_pass[++i] = getch();
                    cout<<"*";
                }
                temp_pass[i] = '\0';

                pass_flag = strcmp(temp_pass,member.password);
                if(pass_flag != 0)
                {
                    cout<<endl<<"Error Password Do Not Match !!"<<endl<<"Press Enter to Y Again Or any key to EXIT";
                    ch = getch();
                    if (ch != 'y' && ch != 'Y')
                        return 0;

                }
                }while(pass_flag != 0);

                if(member.balance<debit_amount)
                {
                    cout<<endl<<"Transaction Unsuccessful."<<endl<<endl;
                    cout<<debit_amount<<" is not available in your account. "<<endl;
                    cout<<"Press Enter to Continue"<<endl;
                    getch();
                    break;
                }
                member.balance -= debit_amount;
                int shift_back = -1*sizeof(member);
                modify.seekp(shift_back, ios :: cur);
                modify.write((char*)&member, sizeof(member));
                modify.seekg(shift_back, ios :: cur);
                modify.read((char*)&member, sizeof(member));
                system("cls");
                cout<<"Transaction Successful !!!"<<endl;
                cout<<"New balance is "<<member.balance<<endl;
                modify.close();
                Sleep(2000);
                system("cls");
            }
        }

        if(flag == false)
        {

            cout<<endl<<"Error : No Account found with "<<temp_acc_no<<" number."<<endl;
            cout<<"Press Enter to continue"<<endl;
            getch();
            system("cls");
        }
    }

    int return_acc_no()
    {
        return acc_no;
    }
};

void screen()
{
    system("cls");
    system("COLOR 1");
    cout<<"\t\t\t BANK PORTAL ONLINE ver1.1"<<endl<<endl;
    cout<<"1. Add Account\n";
    cout<<"2. Remove Account\n";
    cout<<"3. Show\n";
    cout<<"4. Show All\n";
    cout<<"5. Show Detail in table\n";
    cout<<"6. Debit\n";
    cout<<"7. Credit\n";
    cout<<"8. Exit Application\n";
}

int write_obj()
{
    ofstream output("vishal.bin", ios :: binary | ios :: app);

    account member;
    member.acc_add();

    output.write((char*)&member, sizeof(member));
    output.close();
}

int read_obj(int option)
{
    ifstream input("vishal.bin", ios :: binary);

    account member;

    if(option == 3)
    {
        member.show();
    }

    else if(option == 4)
    {
        while(input.read((char*)&member, sizeof(member)))
        {
            member.show_all();

        }
    }

    else if(option == 5)
    {
        member.show_detail();
    }

    system("cls");
    input.close();
}

int transaction(int option)
{
    account member;

    if(option == 6)
    {
        member.debit();
    }
    else if(option == 7)
    {
        member.credit();
    }
    else
        cout<<"Try Again. "<<endl;
        Sleep(1500);
        system("cls");
        return 1;
}

int main()
{
    int option = 0;
    do
    {
        screen();
        cin>>option;
        switch (option)
        {
            system("cls");
        case 1:
            write_obj();
            break;
        case 2:
            account member;
            member.acc_delete();
            break;
        case 3:
            read_obj(option);
            break;
        case 4:
            read_obj(option);
            break;
        case 5:
            read_obj(option);
            break;
        case 6:
            transaction(option);
            break;
        case 7:
            transaction(option);
            break;
        case 8:
            break;
        default :
            continue;
        }
    }while(option != 8);

    system("cls");
    cout<<"Closing !!!";
    Sleep(2000);

    return 0;
}
