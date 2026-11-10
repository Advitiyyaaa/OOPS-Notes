#include<bits/stdc++.h>
using namespace std;

class Customer{
    string name;
    int acc_no;
    int balance;
  public:
    Customer(){//Default Constructor
        cout<<"Constructor is called."<<endl;
    }
    // Customer(string name, int acc_no, int balance){//Parameterized Constructor
    //     this->name = name;
    //     this->acc_no = acc_no;
    //     this->balance = balance;
    // }
    inline Customer(string a, int b, int c):name(a),acc_no(b),balance(c){
        //inline Constructor
    }

    Customer(Customer &A){//Copy Construcctor (it also present by default)
        name = A.name;
        acc_no=A.acc_no;
        balance=A.balance;
    }

    void display(){
        cout<<name<<" "<<acc_no<<" "<<balance<<endl;
    }
};

int main(){
    Customer C1("Advitiya",12345,1000);
    Customer C2;
    Customer C3(C1);
    C1.display();
    C3.display();   
}

// "this" points to the object created.
// here constructor overloading is happening
//Constructor automatically calls itself on object creation, can be used for initialization