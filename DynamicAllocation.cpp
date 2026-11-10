#include<bits/stdc++.h>
using namespace std;

class student{
  public:
    string name;
    int roll_no;
    string grade;
};

int main(){
    student *s1 = new student;
    s1->name="Advitiya";
    (*s1).roll_no=17;
    s1->grade="A+";
    cout<<(*s1).name;
    cout<<s1->roll_no;
    delete s1;
}

//Dynamic allocation(in heap)
// use * = pointers or ->

// Computer consist of two memories "stack" which is static memory and "heap" which is dynamic memory.
// delete only works for dynamic memory