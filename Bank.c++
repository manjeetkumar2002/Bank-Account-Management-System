#include<iostream>
#include<fstream>
#include<windows.h>
#include<sstream>
using namespace std;

class Account{
    private:
    string AccountNo,Password;
    int Balance;
    public :

    Account():AccountNo(""),Password(""),Balance(0){}
    void setAccountNo(string id){
        AccountNo = id;
    }
    void setPassword(string pass){
        Password=pass;
    }
    void setBalance(int balance){
        Balance = balance;
    }
    string getAccountNo(){
        return AccountNo;
    }
    string getPassword(){
        return Password;
    }
    int getBalance(){
        return Balance;
    }
};


void openAccount(Account user){
    system("cls");
    string id,password;
    cout<<"Enter Account No : ";
    cin>>id;
    user.setAccountNo(id);
    cout<<"Enter Your Password : ";
    cin>>password;
    user.setPassword(password);
    
    user.setBalance(0);

    ofstream fout("Account.txt",ios::app);
    if(!fout){
        cout<<"ERROR : File Not Open!"<<endl;
    }
    else{
        fout<<user.getAccountNo()<<" : "<<user.getPassword()<<" : "<<user.getBalance()<<endl;
        cout<<"Account is Opened Successfully!"<<endl;
    }
    fout.close();
    Sleep(5000);
}

void addCash(){
    system("cls");
    string id;
    cout<<"Enter Account No : ";
    cin>>id;

    ifstream fin("Account.txt");
    ofstream fout("Account temp.txt"); // creating temp file
    if(!fin || !fout){
        cout<<"ERROR : File Not Open!"<<endl;
    }
    string line;
    bool found = false;
    while(getline(fin,line)){
        stringstream ss;
        ss<<line;
        string userID,userPw;
        int userBalance;
        char delimeter;
        // stringstream helps us in parsing the string into the variable
        // so that we get the values into the variable
        // then we can check each account id with the input id
        ss>>userID>>delimeter>>userPw>>delimeter>>userBalance;
        if(id == userID){
            found = true;
            int cash;
            cout<<"Enter Cash : ";
            cin>>cash;

            int newBalance = userBalance + cash;
            userBalance = newBalance;
            // storing in temp file
            fout<<userID<<" : "<<userPw<<" : "<<userBalance<<endl;
            cout<<"New Balance is : "<<userBalance<<endl;
        }
        else{
            fout<<line<<endl;
        }
    }

    if(!found){
        cout<<"Enter valid Account No!"<<endl;
    }
    fout.close();
    fin.close();
    remove("Account.txt");
    rename("Account temp.txt","Account.txt");
    Sleep(5000);
}

void withdraw(){
    system("cls");
    string id,pass;
    cout<<"Enter Account No : ";
    cin>>id;
    cout<<"Enter Password : ";
    cin>>pass;
    ifstream fin("Account.txt");
    ofstream fout("Account temp.txt");
    if(!fin || !fout){
        cout<<"ERROR : File Not Open!"<<endl;
    }

    string line;
    bool found = false;
    while(getline(fin,line)){
        stringstream ss;
        ss<<line;
        string userID,userPw;
        int userBalance;
        char delimeter;
        ss>>userID>>delimeter>>userPw>>delimeter>>userBalance;

        if(id==userID){
            found = true;
            // withdraw the cash
            if(pass==userPw){
                int cash;
                cout<<"Enter the amount you want to withdraw : ";
                cin>>cash;
               
                if(cash>userBalance){
                    cout<<"You Balance is Low!"<<endl;
                }
                else{
                    // is withdraw money is less or equal to simply subtract that amount
                    int newBalance = userBalance - cash;
                    userBalance = newBalance;
                    cout<<"Cash is withdraw successfully "<<endl;
                    cout<<"New Balance is "<<userBalance<<endl;
                }
            }
            else{
                cout<<"Wrong Password!"<<endl;
            }
            fout<<userID<<" : "<<userPw<<" : "<<userBalance<<endl;
        }
        else{
            fout<<userID<<" : "<<userPw<<" : "<<userBalance<<endl;
        }
    }

    if(!found){
        cout<<"Enter a valid Account No "<<endl;
    }
    // close the files 
    fout.close();
    fin.close();

    remove("Account.txt");
    rename("Account temp.txt","Account.txt");
    Sleep(4000);
}
int main(){
    Account user;
    bool exit = false;
    while(!exit){
        system("cls");
        int val;
        cout<<"Welcome to Bank Management System"<<endl;
        cout<<"*********************************"<<endl;
        cout<<"1.Open New Account."<<endl;
        cout<<"2.Add Cash."<<endl;
        cout<<"3.Withdraw Cash."<<endl;
        cout<<"4.Exit."<<endl;
        cout<<"Enter Your Choice :";
        cin>>val;
        if(val==1){
            openAccount(user);
        }
        else if(val==2){
            addCash();
        }
        else if(val==3){
            withdraw();
        }
        else if(val==4){
            system("cls");
            exit=true;
            cout<<"Good Luck!"<<endl;
        }
        Sleep(3000);
    }
}