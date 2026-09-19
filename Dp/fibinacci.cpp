// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     int n;
//     cin >> n;

//     int a = 0, b = 1;

//     for (int i = 0; i < n; i++) {
//         cout << a<<" ";
//         int c = a + b;
//         a = b;
//         b = c;
//     }

    

//     return 0;
// }



// #include <bits/stdc++.h>
// using namespace std;

// int fib(int n) {
//     if (n <= 1)
//         return n;
    
//     return fib(n - 1) + fib(n - 2);
// }

// int main() {
//     int n;
//     cin >> n;

//     cout << fib(n);

//     return 0;
// }


// #include <bits/stdc++.h>
// using namespace std;

// int fib(int n, vector<int>& dp) {
//     if (n <= 1)
//         return n;

//     if (dp[n] != -1)
//         return dp[n];

//     dp[n] = fib(n - 1, dp) + fib(n - 2, dp);

//     return dp[n];
// }

// int main() {
//     int n;
//     cin >> n;

//     vector<int> dp(n + 1, -1);

//     cout << fib(n, dp);

//     return 0;
// }



#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> dp(n + 1);

    dp[0] = 0;

    if (n >= 1)
        dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    cout << dp[n];

    return 0;
}