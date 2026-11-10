#include<bits/stdc++.h>
using namespace std;

class a{
    char b; // 1 byte
    double d; // 8 bytes
    char c; // 1 byte
    int k;  // 4 bytes
    char z; // 1 byte
    // string s = 32 bytes
};
// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 
// b x x x x x x x d d d  d  d  d  d  d  c  x  x  x  k  k  k  k  z  x  x  x  x  x  x  x  
// size = 32 (as it is multiple of 8(largest bit size))
int main(){
    a obj;
    cout<<sizeof(obj);
}

