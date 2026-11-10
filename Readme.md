# Object-Oriented Programming (OOP) — Unified Master Notes

> **Tone & Style:** Crisp, no-fluff, intuitive, practical C++ implementation notes. Written by a developer, for developers.

---

## Table of Contents
1. [Classes, Objects & Access Specifiers](#1-classes-objects--access-specifiers)
2. [Structure Padding & Memory Alignment](#2-structure-padding--memory-alignment)
3. [Memory Management: Stack vs Heap (Dynamic Allocation)](#3-memory-management-stack-vs-heap-dynamic-allocation)
4. [Constructors & Object Initialization](#4-constructors--object-initialization)
5. [Destructors & The Shallow vs Deep Copy Problem](#5-destructors--the-shallow-vs-deep-copy-problem)
6. [Static Members & Class-Level Methods](#6-static-members--class-level-methods)
7. [The Four Pillars of OOP](#7-the-four-pillars-of-oop)
   - [I. Encapsulation](#i-encapsulation)
   - [II. Abstraction](#ii-abstraction)
   - [III. Inheritance (All 6 Types + Diamond Problem)](#iii-inheritance)
   - [IV. Polymorphism (Compile-time & Runtime)](#iv-polymorphism)
8. [Quick Revision Cheat Sheet & Gotchas](#8-quick-revision-cheat-sheet--gotchas)

---

## 1. Classes, Objects & Access Specifiers

### What is a Class and an Object?
- **Class:** A user-defined blueprint / template that defines data members (properties) and member functions (behaviors).
- **Object:** An actual physical instance of a class that occupies memory.

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
  private:
    // By default, members are private in C++
    string name;
    int roll_no;
    string grade;

  public:
    // Getters and Setters for controlled access
    void setName(string s) { name = s; }
    void setRollno(int t)  { roll_no = t; }
    void setGrade(string g){ grade = g; }

    string getName() { return name; }
    int getRollno()  { return roll_no; }
    string getGrade(){ return grade; }
};

int main() {
    Student s1;
    s1.setName("Advitiya");
    s1.setRollno(17);
    s1.setGrade("A");

    cout << s1.getName() << " | Roll No: " << s1.getRollno() << endl;
    return 0;
}
```

### Access Specifiers
| Specifier | Accessible within Class? | Accessible in Derived Class? | Accessible from Outside / Main? |
|---|:---:|:---:|:---:|
| `public` |  Yes |  Yes |  Yes |
| `protected` |  Yes |  Yes |  No |
| `private` |  Yes |  No |  No |

> **Rule of thumb:** `Private > Protected > Public`. Private is strictly internal to the declaring class.

---

## 2. Structure Padding & Memory Alignment

Why does `sizeof(obj)` rarely equal the simple sum of its data types?  
**Because the CPU reads memory in "word" blocks (e.g., 4 or 8 bytes at a time) instead of 1 byte at a time.** To optimize read cycles, the compiler inserts empty padding bytes (`x`).

### Alignment Rules:
1. Every member must start at a memory offset that is a multiple of its own size.
2. The total size of the entire structure/class must be a multiple of the **largest member's size**.

### Real Code & Byte Trace:
```cpp
class a {
    char b;   // 1 byte
    double d; // 8 bytes
    char c;   // 1 byte
    int k;    // 4 bytes
    char z;   // 1 byte
};
// string s would take 32 bytes on modern 64-bit std::string implementations
```

#### Memory Layout (Byte offsets 0 to 31):
```text
Offset:  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
Byte:   [b][x][x][x][x][x][x][x][d][d][d][d][d][d][d][d][c][x][x][x][k][k][k][k][z][x][x][x][x][x][x][x]
```
- Offset `0`: `b` (char, 1 byte)
- Offset `1-7`: `x x x x x x x` (7 padding bytes so `double d` can align at offset 8, a multiple of 8)
- Offset `8-15`: `d d d d d d d d` (double, 8 bytes)
- Offset `16`: `c` (char, 1 byte)
- Offset `17-19`: `x x x` (3 padding bytes so `int k` can align at offset 20, a multiple of 4)
- Offset `20-23`: `k k k k` (int, 4 bytes)
- Offset `24`: `z` (char, 1 byte)
- Offset `25-31`: `x x x x x x x` (7 trailing padding bytes to make total size 32, a multiple of 8)
- **Total `sizeof(a)` = 32 bytes.**

---

## 3. Memory Management: Stack vs Heap (Dynamic Allocation)

Computers have two primary memory areas for running programs:
1. **Stack:** Static memory. Automatically allocated and deallocated as scopes open and close. Fast, but limited size.
2. **Heap:** Dynamic memory. Manually allocated with `new`, must be manually freed with `delete`. Slower, but vast.

```cpp
class Student {
  public:
    string name;
    int roll_no;
    string grade;
};

int main() {
    // Dynamic allocation on Heap:
    // Student pointer stored on stack -> points to Student object on heap
    Student *s1 = new Student;

    // Two equivalent ways to access members through pointers:
    s1->name = "Advitiya";      // Arrow operator (cleaner)
    (*s1).roll_no = 17;         // Dereference then dot
    s1->grade = "A+";

    cout << (*s1).name << " " << s1->roll_no << endl;

    // CRITICAL: delete only works on dynamically allocated (heap) memory!
    delete s1; 
    s1 = nullptr; // good practice to prevent dangling pointers
}
```

---

## 4. Constructors & Object Initialization

### Key Features:
- Member function called **automatically** upon object creation.
- Has the **same name as the class**, with **no return type** (not even `void`).
- Can be overloaded (Constructor Overloading).
- The `this` pointer holds the address of the current instance (`this->name = name`).

```cpp
class Customer {
    string name;
    int acc_no;
    int balance;

  public:
    // 1. Default Constructor
    Customer() {
        cout << "Default Constructor called." << endl;
    }

    // 2. Parameterized Constructor
    Customer(string name, int acc_no, int balance) {
        this->name = name;
        this->acc_no = acc_no;
        this->balance = balance;
    }

    // 3. Inline Constructor (Member Initializer List) - Fastest and cleanest
    inline Customer(string a, int b, int c) : name(a), acc_no(b), balance(c) {
        // Initializes fields directly before constructor body runs
    }

    // 4. Copy Constructor (Passed by reference to avoid infinite copy recursion!)
    Customer(const Customer &A) {
        name = A.name;
        acc_no = A.acc_no;
        balance = A.balance;
    }

    void display() {
        cout << name << " | Acc: " << acc_no << " | Bal: " << balance << endl;
    }
};

int main() {
    Customer C1("Advitiya", 12345, 1000); // Parameterized
    Customer C2;                          // Default
    Customer C3(C1);                      // Copy Constructor
    C1.display();
    C3.display();
}
```

---

## 5. Destructors & The Shallow vs Deep Copy Problem

### What is a Destructor?
- An instance member function invoked **automatically** whenever an object is destroyed (goes out of scope or deleted via `delete`).
- Last function to run before the object’s memory is reclaimed.
- Name starts with `~` followed by class name (`~Customer()`). Cannot take arguments, cannot be overloaded.

### Execution Order:
- **Constructors run in normal order** (creation order: C1 -> C2 -> C3).
- **Destructors run in REVERSE order** (LIFO / Stack unwinding: C3 -> C2 -> C1).

```cpp
class Customer {
    string name;
    int *balance; // Pointer to heap memory

  public:
    Customer(string name, int bal) {
        this->name = name;
        balance = new int; // Dynamic allocation inside constructor
        *balance = bal;
    }

    // DEEP COPY CONSTRUCTOR (Required when class has pointer members!)
    Customer(const Customer &other) {
        this->name = other.name;
        this->balance = new int; // Allocate fresh new heap address!
        *(this->balance) = *(other.balance);
    }

    ~Customer() {
        // Free heap memory to prevent memory leaks
        delete balance;
    }
};
```

### The Segmentation Fault Trap (Shallow vs Deep Copy):
> **Beware:** If you use C++'s default compiler-generated copy constructor on a class with raw pointer members (`balance`):
> 1. `C2(C1)` simply copies the memory address of `balance`. Both `C1.balance` and `C2.balance` now point to the **exact same memory location** (Shallow Copy).
> 2. When `C2` goes out of scope, its destructor runs and frees `balance`.
> 3. When `C1` goes out of scope, its destructor runs and tries to `delete balance` again.
> 4. **Result:** Double Free error -> `Segmentation fault` (Crash!).
> 5. **Fix:** Write your own copy constructor to allocate a separate pointer and copy the underlying value (Deep Copy).

---

## 6. Static Members & Class-Level Methods

- **Static Variable:** An attribute that belongs to the **Class itself**, not to individual objects.
  - Only **one copy** exists for the entire class, shared by all objects.
  - Initialized **outside the class** using the scope resolution operator `::`.
  - Exists in memory even before any object is created.
- **Static Function:** A function that belongs to the class.
  - Can **only access static member variables** directly (cannot use `this` or access non-static instance fields).
  - Can be called without creating any object: `Customer::getTotalBankBalance()`.

```cpp
class Customer {
    string name;   // Belongs to each object
    int acc_no;    // Belongs to each object
    int balance;   // Belongs to each object

    // Static variables belong to the class
    static int total_customers;
    static int total_balance_bank;

  public:
    Customer(string name, int acc_no, int balance) {
        this->name = name;
        this->acc_no = acc_no;
        this->balance = balance;
        total_customers++;
        total_balance_bank += balance;
    }

    void deposit(int amount) {
        if (amount <= 0) {
            cout << "Amount should be greater than zero, you dumb fool" << endl;
            return;
        }
        balance += amount;
        total_balance_bank += amount;
    }

    void withdraw(int amount) {
        if (amount <= 0) return;
        if (balance >= amount) {
            balance -= amount;
            total_balance_bank -= amount;
        }
    }

    // Static functions can only access static members
    static void getTotalCustomerCount() {
        cout << "Total Customers: " << total_customers << endl;
    }

    static void getTotalBankBalance() {
        cout << "Total Bank Balance: " << total_balance_bank << endl;
    }
};

// Static member definitions & initializations outside the class
int Customer::total_customers = 0;
int Customer::total_balance_bank = 0;

int main() {
    Customer C1("Advitiya", 1, 12000);
    Customer C2("Shivam", 2, 1200);

    // Call static functions directly via Class Name:
    Customer::getTotalBankBalance();    // 13200
    Customer::getTotalCustomerCount();   // 2

    C1.deposit(100000);
    Customer::getTotalBankBalance();    // 113200

    C2.deposit(0);                      // "Amount should be greater than zero, you dumb fool"
}
```

---

## 7. The Four Pillars of OOP

```text
               ┌────────────────────────────────────────────────────────┐
               │                  4 PILLARS OF OOP                      │
               └───────┬────────────┬─────────────┬─────────────┬───────┘
                       │            │             │             │
        ┌──────────────┴─┐   ┌──────┴──────┐   ┌──┴──────────┐  └─────────────┐
        │ Encapsulation  │   │ Abstraction │   │ Inheritance │  │ Polymorphism│
        └────────────────┘   └─────────────┘   └─────────────┘  └─────────────┘
```

---

### I. Encapsulation
> **"Wrapping up data (variables) and methods (functions) into a single unit, while strictly controlling access to them."**

- **Why?** Prevents outside direct tampering, prevents invalid states, enforces business rules.
- **How?** Keep data variables `private`, expose validation-checked `public` methods (`deposit()`, `withdraw()`, getters/setters).
- *See the `Customer` class in Section 6 where balance cannot be set arbitrarily negative.*

---

### II. Abstraction
> **"Displaying only essential features to the outside world while hiding internal complex implementation details."**

- **Example in real life:** When you press the gas pedal of a car, you don't need to know how fuel injection or spark ignition works.
- **Example in code:** In `C1.deposit(5000)`, the caller doesn't need to know how ledger calculations or `total_balance_bank` internal math runs.
- **Enforced via:** Abstract Classes and Pure Virtual Functions (see Section IV).

---

### III. Inheritance
> **"The capability of a class to derive properties and characteristics from another class. Mechanism for code reusability."**

- **Constructor Order:** Parent Constructor is executed **first**, then Child Constructor.
- **Destructor Order:** Child Destructor runs **first**, then Parent Destructor.
- **Access Specifiers in Inheritance:**
  - `class Child : public Parent` -> `public` remains public, `protected` remains protected.
  - `class Child : protected Parent` -> `public` and `protected` become protected in child.
  - `class Child : private Parent` -> `public` and `protected` become private in child.
  - `private` members of Parent are **never directly accessible** in Child, regardless of inheritance mode!

---

#### 1. Single Inheritance
A single child inherits from a single parent.
```cpp
class Human {
  public:
    string name;
    int age, weight;

    Human(string name, int age, int weight) {
        this->name = name;
        this->age = age;
        this->weight = weight;
    }
};

class Student : public Human {
    int roll_no;
    int fees;
  public:
    // Call parent constructor in initialization list
    Student(int roll_no, int fees, string name, int age, int weight)
        : Human(name, age, weight) {
        this->roll_no = roll_no;
        this->fees = fees;
    }

    void Display() {
        cout << name << " | Age: " << age << " | Roll: " << roll_no << endl;
    }
};
```

---

#### 2. Multilevel Inheritance
A class inherits from a derived class (Grandparent -> Parent -> Child).
```cpp
class Person {
  public:
    string name;
    void introduce() { cout << "My name is " << name << endl; }
};

class Employee : public Person {
  public:
    int salary;
    void tellSalary() { cout << "Salary: " << salary << endl; }
};

class Manager : public Employee {
  public:
    string branch;
    void tellBranch() { cout << "Branch: " << branch << endl; }
};

// Manager has access to name, salary, branch!
```

---

#### 3. Multiple Inheritance
A single child inherits directly from **two or more independent parent classes**.
```cpp
class Person {
  public:
    string name;
    void introduce() { cout << "My name is " << name << endl; }
};

class Employee {
  public:
    int salary;
    void tellSalary() { cout << "Salary: " << salary << endl; }
};

// Inherits from BOTH Employee and Person
class Manager : public Employee, public Person {
  public:
    string branch;
};
```

---

#### 4. Hierarchical Inheritance
One parent class is inherited by **multiple child classes**.
```text
           ┌──────────┐
           │  Person  │
           └──┬────┬──┘
      ┌───────┘    └───────┐
      ▼                    ▼
┌──────────┐         ┌──────────┐
│ Employee │         │ Manager  │
└──────────┘         └──────────┘
```
```cpp
class Person { public: string name; };
class Employee : public Person { public: int salary; };
class Manager  : public Person { public: string branch; };
```

---

#### 5. Hybrid Inheritance
A combination of two or more types of inheritance (e.g., Multilevel + Multiple).
```cpp
class Student { public: string name; };
class Male    { public: void MalePrint() { cout << "I am male" << endl; } };
class Female  { public: void FemalePrint() { cout << "I am female" << endl; } };

class Boy  : public Student, public Male   { /* Hybrid */ };
class Girl : public Student, public Female { /* Hybrid */ };
```

---

#### 6. Multipath Inheritance & The Diamond Problem (Virtual Base Classes)
Occurs when a child inherits from two parent classes that both inherited from the **same grandparent class**.

```text
               ┌──────────┐
               │  Human   │  (has 'name')
               └──┬────┬──┘
        ┌─────────┘    └─────────┐
        ▼                        ▼
 ┌──────────────┐         ┌──────────────┐
 │   Youtuber   │         │   Engineer   │
 └──────┬───────┘         └──────┬───────┘
        └─────────┐    ┌─────────┘
                  ▼    ▼
             ┌─────────────┐
             │ CodeTeacher │  (Diamond shape -> Ambiguity!)
             └─────────────┘
```

- **The Problem:** Without intervention, `CodeTeacher` gets **two copies** of `name` (one via `Youtuber` and one via `Engineer`). Writing `CT1.name = "Advitiya"` throws a compiler error: `"request for member 'name' is ambiguous"`.
- **The Fix:** Use `virtual` inheritance on both parents. This instructs the compiler: *"Hey, keep only ONE shared instance of the grandparent `Human`."*

```cpp
class Human {
  public:
    string name;
};

// virtual keyword prevents duplicate copies of Human
class Youtuber : public virtual Human {
  public:
    int subs;
};

class Engineer : public virtual Human {
  public:
    int salary;
};

class CodeTeacher : public Engineer, public Youtuber {
  public:
    CodeTeacher() {}
};

int main() {
    CodeTeacher CT1;
    CT1.name = "Advitiya"; // Perfectly valid and unambiguous!
}
```

---

### IV. Polymorphism
> **"Poly" (many) + "Morph" (forms). The ability of code or entities to behave differently in different contexts.**

```text
                           ┌─────────────────────────┐
                           │      POLYMORPHISM       │
                           └────────────┬────────────┘
                   ┌────────────────────┴───────────────────┐
                   ▼                                        ▼
      ┌─────────────────────────┐              ┌─────────────────────────┐
      │  Compile-time (Static)  │              │   Runtime (Dynamic)     │
      └────────────┬────────────┘              └────────────┬────────────┘
          ┌────────┴────────┐                               │
          ▼                 ▼                               ▼
    Function             Operator                        Virtual
   Overloading          Overloading                     Functions
```

---

#### 1. Compile-Time Polymorphism (Early Binding)

##### A. Function Overloading:
Same function name with different parameter signatures (type, count, or order of arguments).
```cpp
class Area {
  public:
    void getArea(int r) {
        cout << "Circle Area: " << 3.14 * r * r << endl;
    }
    void getArea(int l, int b) {
        cout << "Rectangle Area: " << l * b << endl;
    }
};
```

##### B. Operator Overloading:
Giving special customized meaning to an existing C++ operator when applied to user-defined objects.
```cpp
class Complex {
    int real, img;
  public:
    Complex() : real(0), img(0) {}
    Complex(int real, int img) : real(real), img(img) {}

    void Display() {
        cout << real << " + i" << img << endl;
    }

    // Overloading '+' operator
    Complex operator +(const Complex &C) {
        Complex ans;
        ans.real = this->real + C.real;
        ans.img  = this->img  + C.img;
        return ans;
    }

    // Overloading '-' operator
    Complex operator -(const Complex &C) {
        Complex ans;
        ans.real = this->real - C.real;
        ans.img  = this->img  - C.img;
        return ans;
    }
};

int main() {
    Complex C1(5, 6), C2(4, 5);
    Complex C3 = C1 + C2; // Invokes operator+
    Complex C4 = C1 - C2; // Invokes operator-
    C3.Display(); // 9 + i11
    C4.Display(); // 1 + i1
}
```

---

#### 2. Runtime Polymorphism (Late Binding & Dynamic Dispatch)

##### Virtual Functions & Abstract Classes:
- A base class declares a method as `virtual`. When invoked via a base class pointer (`Animal *P`), C++ looks up the **vtable** at runtime to call the actual derived class's implementation instead of the base one.
- **Pure Virtual Function (`= 0`):** Has no implementation in the base class. Any class containing at least one pure virtual function becomes an **Abstract Class** and cannot be instantiated directly.

```cpp
class Animal {
  public:
    // Pure virtual function makes Animal an Abstract Class
    virtual void makeSound() = 0; 
};

class Dog : public Animal {
  public:
    void makeSound() override {
        cout << "Bark" << endl;
    }
};

class Cat : public Animal {
  public:
    void makeSound() override {
        cout << "Meow" << endl;
    }
};

int main() {
    // Animal A; // Error: Cannot declare variable of abstract class type 'Animal'

    Animal *P; // Pointer to base class

    P = new Dog();
    P->makeSound(); // Outputs: "Bark" (resolved dynamically at runtime)
    delete P;

    P = new Cat();
    P->makeSound(); // Outputs: "Meow"
    delete P;
}
```

---

## 8. Quick Revision Cheat Sheet & Gotchas

1. **Size of an Empty Class:** In C++, an empty class has `sizeof = 1 byte` so that each instance has a unique memory address.
2. **Padding Rule:** Data aligned to own size; structure aligned to largest member's size.
3. **Pointers & Arrow (`->`):** `ptr->member` is shorthand syntactic sugar for `(*ptr).member`.
4. **`this` pointer:** An implicit pointer passed to non-static member functions pointing to the object that invoked the function.
5. **Constructor Calling:** Base/Parent constructor runs **first**, derived constructor runs **second**.
6. **Destructor Calling:** Runs in strict **reverse** order (LIFO). Always make base class destructors `virtual` if deleting derived objects via base pointers!
7. **Shallow vs Deep Copy:** If an object owns dynamic heap memory (`new`), you **MUST** implement a custom Copy Constructor and Destructor (`delete`), otherwise double-free segmentation faults will crash the program.
8. **Static Members:** Belongs to the class, not individual objects. Shared across all instances. Initialized globally via `Type ClassName::var = val;`. Static methods cannot access `this` or non-static fields.
9. **Diamond Problem Solution:** Use `virtual` inheritance (`class B : virtual public A`) so the grandparent is only inherited once.
10. **Compile-time vs Runtime:**
    - Compile-time: Function overloading, Operator overloading (Fast, early binding).
    - Runtime: Virtual functions via base pointers (Dynamic binding via VTable/VPtr).

