#include<bits/stdc++.h>
using namespace std;

void insert(stack<int>&s,int temp){
    if(s.empty()){
        s.push(temp);
        return;
    }
    int Top  = s.top();
    s.pop();

    insert(s,temp);

    s.push(Top);

}

void reverse(stack<int>&s){
    if(s.empty()){
        return;
    }
    int temp = s.top();
    s.pop();
    reverse(s);

    insert(s,temp);


}

int main (){
    stack<int>s;
    s.push(1);
    s.push(2);
    s.push(5);
    s.push(4);
    stack<int> t=s;

    while(!t.empty()){
        cout<<t.top();
        t.pop();
    }
    cout<<endl;


    reverse(s);
    stack<int> tempStack = s;

    while (!tempStack.empty()) {
        cout << tempStack.top() ;
        tempStack.pop();
    }

    return 0;
}