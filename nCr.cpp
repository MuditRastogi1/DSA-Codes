#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007

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

//////////////////////////////////
//Method 2 (correct even for very large answers)

long long binpow(long long base, long long exp) {
    long long res = 1;
    while (exp > 0) {
        if (exp & 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
 return res % mod;
}

int fact(int n) {
    int res = 1;
    for (int i = 1; i <= n; i++) {
        res = res * 1ll * i % mod;
    }
 return res;
}

int nCr(int n, int k) {
    return fact(n) * binpow(fact(k), mod - 2) % mod * binpow(fact(n - k), mod - 2) % mod;
}


/////////////////////////////////////////////
/// @return 
int main()
{
    cout<<nCr(7,1);
    return 0;
}