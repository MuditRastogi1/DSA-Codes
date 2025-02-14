#include<bits/stdc++.h>
using namespace std;
//only for answer on long long range (not for very large answers)
 long long nCr(int n, int r) {
    r = max(r,n - r); 
    long long ans = 1;

    for(int i = 1; i <= r; i++) {
        ans *= (n - r + i);
        ans /= i;
    }
 return ans;
}
int main()
{
    cout<<nCr(7,1);
    return 0;
}




/*

class Solution {
    
string solve(int n) {
    vector<int> powers(n);
    powers[0] = 1;
    for (int i = 1; i < n; ++i) {
        powers[i] = (powers[i - 1] * 10) % 7;
    }

    vector<int> digits(n, 9);

    while (true) {
        int num = 0;
        for (int i = 0; i < n; ++i) {
            num = (num + digits[i] * powers[i]) % 7;
        }
        if (num == 0) {
            break;
        }

        int i = n/2;
        while (i >= 0 && digits[i] == 0) {
            digits[i] = 9;
            digits[n-i-1] = 9;
            --i;
        }
     --digits[i];
     if(i != n-i-1) --digits[n-i-1];
    }

    string ans = "";
    for (int i = 0; i < n; ++i) {
        ans += '0' + digits[i];
    }
 return ans;
}
public:
    string largestPalindrome(int n, int k) {
        string ans = "";
        
        if(k == 1 || k == 3) {
            for(int i=0; i<n; i++) ans += "9";
            return ans;
        }
        else if(k == 2) {
            for(int i=0; i<n; i++) ans += "9";
            ans[0] = '8'; ans.back() = '8';
            return ans;
        }
        else if(k == 4) {
            if(n == 1) return "8";
            for(int i=0; i<n; i++) ans += "9";
            ans[0] = '8'; ans.back() = '8';
            if(n > 2) {
                ans[1] = '8'; ans[n-2] = '8';
            }
            return ans;
        }
        else if(k == 5) {
            for(int i=0; i<n; i++) ans += "9";
            ans[0] = '5'; ans.back() = '5';
            return ans;
        }
        else if(k == 6) {
            if(n == 1) return "6";
            if(n == 2) return "66";
            for(int i=0; i<n; i++) ans += "9";
            ans[0] = '8'; ans.back() = '8';
            int rem = ((n-2)*9 + 16) % 3;
            if(n % 2 == 1) {
                char digit = '0' + 9 - rem;
                ans[n/2] = digit;
                return ans;
            }
            else {
                if(rem == 0) return ans;
                else if(rem == 1) {
                    ans[n/2] = '7'; ans[n/2-1] = '7';
                    return ans;
                }
                else {
                    ans[n/2] = '8'; ans[n/2-1] = '8';
                    return ans;
                }
            }
        }
        else if(k == 7) {
            if(n == 1) return "7";
            if(n == 2) return "77";
            ans = solve(n);
            return ans;
        }
        else if(k == 8) {
            if(n == 1) return "8";
            if(n == 2) return "88";
            for(int i=0; i<n; i++) ans += "9";
            ans[0] = '8'; ans[1] = '8'; ans[2] = '8';
            ans[n-1] = '8'; ans[n-2] = '8'; ans[n-3] = '8';
            return ans;
        }
        else if(k == 9) {
            for(int i=0; i<n; i++) ans += "9";
            return ans;
        }
     return "";
    }
};

*/



#define mod 10000000007
class Solution {
    long long flatten(vector<int>& v, int k) {
        long long index = 0;
        for (int i = 1; i < 101; i++) {
            if(v[i])
            index = (1LL * index * i + i) % mod;
        }
     return index;
    }
    int solve(int row, vector<vector<int>>& grid, vector<int>& vis, unordered_map<long long,int>& mpp, long long state) {
        if(row == grid.size()) {
            return 0;
        }
        if(mpp.find(state) != mpp.end()) {
            return mpp[state];
        }
        int ans = solve(row+1,grid,vis,mpp,state);
        for(int col=0; col<grid[0].size(); col++) {
            if(!vis[grid[row][col]]) {
                vis[grid[row][col]] = 1;
                long long n_state = (flatten(vis, 101)) % mod;
                    mpp[n_state]++;
                    ans = max(ans,grid[row][col] + solve(row+1,grid,vis,mpp,n_state));
                    mpp[n_state]--;  
                vis[grid[row][col]] = 0;
            }
        }
     return mpp[state] = ans;
    }
public:
    int maxScore(vector<vector<int>>& grid) {
        vector<int> vis(101,0);
        unordered_map<long long,int> mpp;
     return solve(0,grid,vis,mpp,0);
    }
};


/*
[[1,5,20,18],[19,6,17,3],[12,10,6,3],[1,20,12,15]]
[[8,11,3],[17,7,3],[13,20,3],[3,17,20]]




69
61
*/