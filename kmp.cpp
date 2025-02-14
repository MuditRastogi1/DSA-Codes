#include<bits/stdc++.h>
using namespace std;

vector<int> kmp(string s) {
    int n = s.length();
    vector<int> lps(n,0);

    for(int i=1; i<n; i++) {
        int j = lps[i-1];

        while(j > 0 && s[i] != s[j]) {
            j = lps[j-1];
        }

        if(s[i] == s[j]) {
            j++;
        }
     lps[i] = j;
    }
 return lps;
}

int main()
 {            
    string s = "ababcababc";              
    vector<int> lps = kmp(s);
    for(int i=0; i<s.length(); i++) {
        cout<<i<<" "<<lps[i]<<endl;
    }
    return 0;
}