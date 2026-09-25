#include<bits/stdc++.h>
using namespace std;
int main(){
    //int to binary
    int n = 8;

string binary = bitset<8>(n).to_string();
// cout<<binary;
// binary string to int 
    string s = "1101";

int nm = stoi(s,0, 2);
cout<<nm;
}