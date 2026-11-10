//INHERITANCE
//Capability of a class to derive properties and characteristics from another class. It is a mechanism of reusability of code.

//                 External code           within class          derived class
// public               Yes                    Yes                    Yes
// protected            No                     Yes                    Yes
// private              No                     Yes                    No

//Private>protected>public      (Private cant be accessed in any case)

//Parent Constructor is called first and then child constructor is called.

#include<bits/stdc++.h>
using namespace std;


/*----SINGLE INHERITENCE----*/
// class human{
// //   private:
// //   protected:
//   public:
//     string name;
//     int age, weight;

//     human(string name, int age, int weight){
//         this->name = name;
//         this->age = age;
//         this->weight = weight;
//     }

//     void Display(){
//         cout<<"Name: "<<name<<endl;
//         cout<<"Age: "<<age<<endl;
//         cout<<"Weight: "<<weight<<endl;
//     }
// };

// class Student: public human{
//     int roll_no;
//     int fees;
//   public:
//     Student(int roll_no, int fees, string name, int age, int weight): human(name, age, weight){
//         this->roll_no = roll_no;
//         this->fees = fees;
//     }

//     void Display(){
//         cout<<"Name: "<<name<<endl;
//         cout<<"Age: "<<age<<endl;
//         cout<<"Weight: "<<weight<<endl;
//         cout<<"Roll No: "<<roll_no<<endl;
//         cout<<"Fees: "<<fees<<endl;
//     }
// };

// int main(){
//     Student S1(1, 1000, "John", 20, 70);
//     S1.Display();
//     //On calling Display() function, if this function is not present in Student class, then it will call the Display() function of human class. This is called function overriding.
//     //parent class.
// }

/*----MULTILEVEL INHERITANCE----*/
//A class inheriting properties from a class which itself is inheriting properties from other class 

// class person{
//   public:
//     string name;

//     void introduce(){
//         cout<<"My name is "<<name<<endl;
//     }
// };

// class Employee: public person{
//   public:
//     int emp_id;
//     int salary;
//     void tellSalary(){
//         cout<<"My monthly Salary is "<<salary<<endl;
//     }
// };

// class Manager: public Employee{
//   public:
//     string branch;
//     string office;
//     void tellBranch(){
//         cout<<"My branch is "<<branch<<endl;
//     }
// };

// int main(){
//     Manager M1;
//     M1.name = "Advitiya";
//     M1.salary=1000000;
//     M1.branch="Bengaluru";
//     M1.introduce();
//     M1.tellSalary();
//     M1.tellBranch();
// }

/*----MULTIPLE INHERITANCE----*/
//A class inheriting properties from multiple classes

// class person{
//   public:
//     string name;

//     void introduce(){
//         cout<<"My name is "<<name<<endl;
//     }
// };

// class Employee{
//   public:
//     int emp_id;
//     int salary;
//     void tellSalary(){
//         cout<<"My monthly Salary is "<<salary<<endl;
//     }
// };

// class Manager: public Employee , public person{
//   public:
//     string branch;
//     string office;
//     void tellBranch(){
//         cout<<"My branch is "<<branch<<endl;
//     }
// };

// int main(){
//     Manager M1;
//     M1.name = "Advitiya";
//     M1.salary=1000000;
//     M1.branch="Bengaluru";
//     M1.introduce();
//     M1.tellSalary();
//     M1.tellBranch();
// }

/*----Hierarchical INHERITANCE----*/
//A class being inheritated by multiple child class

// class person{
//   public:
//     string name;

//     void introduce(){
//         cout<<"My name is "<<name<<endl;
//     }
// };

// class Employee:public person{
//   public:
//     int emp_id;
//     int salary;
//     void tellSalary(){
//         cout<<"My monthly Salary is "<<salary<<endl;
//     }
// };

// class Manager: public person{
//   public:
//     string branch;
//     string office;
//     void tellBranch(){
//         cout<<"My branch is "<<branch<<endl;
//     }
// };

// int main(){
//     Manager M1;
//     Employee E1;
//     E1.name = "Utkarsh";
//     E1.salary = 12030;
//     M1.name = "Advitiya";
//     M1.branch="Bengaluru";
//     M1.introduce();
//     M1.tellBranch();
//     E1.introduce();
//     E1.tellSalary();
// }

/*----HYBRID INHERITANCE----*/
//A mixture of more than one type of inheritance.

// class Student{
//   public:
//     string name;

//     void introduce(){
//         cout<<"My name is "<<name<<endl;
//     }
// };

// class male{
//   public:
//     void MalePrint(){
//         cout<<"I am male"<<endl;
//     }
// };

// class female{
//   public:
//     void FemalePrint(){
//         cout<<"I am female"<<endl;
//     }
// };

// class Boy:public Student , public male{
//   public:
//     void BoyPrint(){
//         cout<<"I am boy"<<endl;
//     }
// };

// class Girl:public Student , public female{
//   public:
//     void GirlPrint(){
//         cout<<"I am girl"<<endl;
//     }
// };

// int main(){
//     Boy B1;
//     B1.MalePrint();
//     B1.BoyPrint();

//     Girl G1;
//     G1.FemalePrint();
//     G1.GirlPrint();
// }

/*----MULTIPATH INHERITANCE----*/
// A special case of Hybrid inheritance where a child class inherits from multiple 
// parent classes, which themselves share a common grandparent class. 
//
// This creates a diamond-shaped inheritance path, leading to ambiguity unless 
// the "virtual" keyword is used to ensure the grandparent's members are inherited only once.


class Human{
  public:
    string name;

    void introduce(){
        cout<<"My name is "<<name<<endl;
    }
};

class Youtuber:public virtual Human{//virtual is needed, otherwise there would be two names in codeTeacher and will create ambiguity
  public:
    int subs;
};

class Engineer:public virtual Human{//virtual will make them understand that both name are same
  public:
    int salary;
};

class CodeTeacher:public Engineer, public Youtuber{
  public:
    CodeTeacher(){

    }
};

int main(){
    CodeTeacher CT1;
    CT1.name = "Advitiya";
}