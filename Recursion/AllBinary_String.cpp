#include<bits/stdc++.h>
using namespace std;
// void solve(int n,string &s){//pass by reference hui
//      if(s.size()==n){
//         cout<<s<<" ";
//         return ;
//      }
//      s+='0';
//     solve(n,s);
//     s.pop_back();

//     s+='1';

//     solve(n,s);
//     s.pop_back();
// }


void solve(int n,string s){ // pass by value 
     if(s.size()==n){
        cout<<s<<" ";
        return ;
     }
     
    solve(n,s+'0');
    solve(n,s+'1');
   
}

int main(){
    int n;
    cout<<"Enter n:";
    cin>>n;
    string s = "";
    solve(n,s);



    return 0;
}