#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007


    //without leading 0's
    int solve(int i, int bound, int sum, string s, int min_sum, int max_sum, int dp[24][2][200]) {
       if(i == s.length())  //check base condition here
        return (min_sum <= sum && sum <= max_sum);

        if(dp[i][bound][sum] != -1) 
         return dp[i][bound][sum];

        int curr = 0, maxDigit = bound ? (s[i]-'0') : 9; //so that current no. does not exceed maximum limit
        for(int j=0; j<=maxDigit; j++) { //bound may only change if it was prev. 1
            curr += solve(i+1,bound & (j == s[i]-'0'),sum+j,s,min_sum,max_sum,dp);
            curr = curr % mod;
        }
     return dp[i][bound][sum] = curr;
    }
    

    //considering leading 0's (SHORTER VERSION)
    int solve(int i, int bound, int isLeading0, string s, int dp[11][2][2]) {
       if(i == s.length()) {
        return !isLeading0;
       }

        if(dp[i][bound][isLeading0] != -1) 
         return dp[i][bound][isLeading0];

        int curr = 0, maxDigit = bound ? (s[i]-'0') : 9; 
        for(int j=0; j<=maxDigit; j++) {
            if(j == 0 && isLeading0)
             curr += solve(i+1,bound & (j == s[i]-'0'),1,s,dp);
            else 
             curr += solve(i+1,bound & (j == s[i]-'0'),0,s,dp);
        }
     return dp[i][bound][isLeading0] = curr;
    }

    //considering leading 0's (LONGER VERSION)
    int solve(int i, int bound, int isLeading0, int even, int odd, string s, int dp[11][2][2][10][10][21], int rem, int k) {
       if(i == s.length()) {
        return (even == odd && rem == 0);
       }

        if(dp[i][bound][isLeading0][even][odd][rem] != -1) 
         return dp[i][bound][isLeading0][even][odd][rem];

        int curr = 0, maxDigit = bound ? (s[i]-'0') : 9; 
        for(int j=0; j<=maxDigit; j++) {
            if(j == 0 && isLeading0)
             curr += solve(i+1,bound & (j == s[i]-'0'),even,odd,1,s,dp,0,k);
            else 
             curr += solve(i+1,bound & (j == s[i]-'0'),even+(j%2==0),odd+(j%2),0,s,dp,(rem*10+j)%k,k);
         curr = curr % mod;
        }
     return dp[i][bound][isLeading0][even][odd][rem] = curr;
    }

int main()
 {
//         memset(dp,-1,sizeof(dp));
//         string s = "";
//         cout<<solve(0,1,0,s,3,dp) % mod;

}
