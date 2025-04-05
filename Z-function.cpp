#include <bits/stdc++.h>
using namespace std;

vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
 return z;
}

int main()
{
    int n;
    cin >> n;
    string s = "abcmabckab";
    vector<int> z = z_function(s);
    for (auto it : z) {
        cout << it << " ";
    }
 return 0;
}

//  z[i] == k      ------>        substr(0,k) == subtr(i,k)

//         _____   ___
// a b c m a b c k a b
// 0 0 0 0 3 0 0 0 2 0
//         *       *