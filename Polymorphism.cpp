#include<bits/stdc++.h>
using namespace std;

//POLYMORPHISM
//1. Compile time: Function Overloading , Operator Overloading
//2. Runtime: Virtual Function

//Function Overloading: Same function name with different parameters

class Area{
  public:
    void getArea(int r){
        cout<<3.14*r*r<<endl;
    }
    void getArea(int l,int b){
        cout<<l*b<<endl;
    }
};

//Operator Overloading: Same operator with different meaning

class Complex{
    int real,img;
  public:
    Complex(){

    }
    Complex(int real,int img){
        this->real = real;
        this->img = img;
    }
    void Display(){
        cout<<real<<" + i"<<img<<endl;
    }
    Complex operator +(Complex &C){
        Complex ans;
        ans.real = real+C.real;
        ans.img = img+C.img;
        return ans;
    }

    Complex operator -(Complex &C){
        Complex ans;
        ans.real = real-C.real;
        ans.img = img-C.img;
        return ans;
    }
};
//Virtual Function: A function in base class which is redefined in derived class. It is used to achieve runtime polymorphism.

class Animal{
  public:
    // virtual void makeSound(){ // virtual keyword is used to tell the compiler that this function can be overridden in derived class
    //     cout<<"Some generic sound"<<endl;
    // }

    virtual void makeSound()=0; // pure virtual function, making this class abstract class
};

class Dog : public Animal{
  public:
    void makeSound(){
        cout<<"Bark"<<endl;
    }
};

class Cat : public Animal{
  public:
    void makeSound(){
        cout<<"Meow"<<endl;
    }
};

int main(){
    // Area A1;
    // A1.getArea(10);
    // A1.getArea(10,5);

    // Complex C1(5,6);
    // Complex C2(4,5);
    // Complex C3 = C1+C2;
    // Complex C4 = C1-C2;
    // C3.Display();
    // C4.Display();

    Animal *P;
    P = new Dog();
    P->makeSound();
    P = new Cat();
    P->makeSound();
}