#include <bits/stdc++.h>
using namespace std;

void solve(int n, string s) {

    if (s.size() == n) {
        cout << s << " ";
        return;
    }

    // 0 always allowed
    solve(n, s + '0');

    // 1 only when previous character is NOT '1'
    if (s.empty() || s.back() != '1') {
        solve(n, s + '1');
    }
}

int main() {

    int n;
    cin >> n;

    string s = "";

    solve(n, s);

    return 0;
}