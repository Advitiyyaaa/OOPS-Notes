#include<bits/stdc++.h>
using namespace std;
//STATIC Member
// They are attribute of classes or class member
// It is declared using static keyword
// Only one copy of that member is created for the entire class 'S' is shared by all the objects.
// It is initialized before any object of this class is created.

class Customer{
    string name; // belongs to obj
    int acc_no; // belongs to obj
    int balance; // belongs to obj
    static int total_customers; //belongs to class
    static int total_balance_bank; //belongs to class
  public:
    Customer(string name, int acc_no, int balance){
        this->name = name;
        this->acc_no = acc_no;
        this->balance = balance;
        total_customers++;
        total_balance_bank+=balance;
    }

    void deposit(int amount){
        if(amount<=0){
            cout<<"Amount should be greater than zero, you dumb fool"<<endl;
            return;
        }
        balance+=amount;
        total_balance_bank+=amount;
    }

    void withdraw(int amount){
        if(amount<=0){
            return;
        }
        if(balance>=amount){
            balance-=amount;
            total_balance_bank-=amount;
        }
    }

    static void getTotalCustomerCount(){ //Static function 
        cout<<"Total Customers: "<<total_customers<<endl; //can only access static member var
    }

    static void getTotalBankBalance(){
        cout<<"Total Bank Balance: "<<total_balance_bank<<endl;
    }
};

int Customer::total_balance_bank=0; //Initialization
int Customer::total_customers=0;

int main(){
    Customer C1("Advitiya",1,12000);
    Customer C2("Shivam",2,1200);
    Customer::getTotalBankBalance(); //these functions can be accessed because they are static and belong to class
    Customer::getTotalCustomerCount(); // hence using class i can access these
    C1.deposit(100000);
    Customer::getTotalBankBalance();
    C2.deposit(12000);
    Customer::getTotalBankBalance();
    C2.withdraw(12000);
    Customer::getTotalBankBalance(); 
    C2.deposit(0);
    Customer::getTotalBankBalance();
}