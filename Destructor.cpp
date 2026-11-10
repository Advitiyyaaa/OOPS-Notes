#include<bits/stdc++.h>
using namespace std;
//Destructor is an instance member function that is invoked automatically whenever an object is going to be destroyed.
//It is the last function that is called before an object is destroyed.

class Customer{
    string name;
    int *balance;
  public:
    Customer(string name,int bal){
        this->name = name;
        balance = new int;
        *balance = bal;
    }

    ~Customer(){ //Destructor
        delete balance;
    }
};

int main(){
    Customer C1("Advitiya",1000);
}

//Constructor works in given order
//Destructor works in reverse order
//Here on using default copy constructor it will crash as pointer balance would be same for both objects and on deletion of one no error
//but on second dectructor call error:segmented error
//to fix use your own copy constructor where you create new pointer for the object