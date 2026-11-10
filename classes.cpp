#include<bits/stdc++.h>
using namespace std;

// class student{
//   public:
//     string name;
//     int roll_no;
//     string grade;
// };

// int main(){
//     student s1;
//     s1.name="Advitiya";
//     s1.roll_no=17;
//     s1.grade="A+";
//     cout<<s1.name;
// }

class student{
  private:
    string name;
    int roll_no;
    string grade;
  public:
    void setName(string s){
        name = s;
    }
    void setRollno(int t){
        roll_no=t;
    }
    void setGrade(string g){
        grade = g;
    }
    string getName(){
        return name;
    }
    int getRollno(){
        return roll_no;
    }
    string getGrade(){
        return grade;
    }
};

int main(){
    student s1;
    s1.setName("Advitiya");
    s1.setRollno(17);
    s1.setGrade("A");
    cout<<s1.getName();
}