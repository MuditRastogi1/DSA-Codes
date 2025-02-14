#include<bits/stdc++.h>
using namespace std;
 
const int MAX_N = 100'00'06;
const int LOG = 20;
int sparse[MAX_N][LOG]; // sparse[i][j] is minimum among arr[i..i+2^j-1]
int bin_log[MAX_N];

void build(int n)
{
       for(int j=1; j<LOG; j++) {
          for(int i=0; i+(1<<j)-1<n; i++) {
             sparse[i][j] = min(sparse[i][j-1],sparse[i+(1<<(j-1))][j-1]);
        }
    }
}

int query(int l, int r)
{
    int len = r - l + 1;
    int k = bin_log[len]; // while((1<<(k+1)) <= len) k++;
 return min(sparse[l][k],sparse[r-(1<<k)+1][k]);
}

int main()
{
    int n,q;
    cin>>n>>q;
    int arr[n];

	bin_log[1] = 0; //for quickly finding log2()
	for(int i = 2; i <= n; i++) {
		bin_log[i] = bin_log[i/2]+1;
	}

    for(int i=0; i<n; i++) {
       cin>>arr[i];
       sparse[i][0] = arr[i];
    }

    //pre-processing
    build(n);

    //answer queries in O(1)
    for(int i=0; i<q; i++) {
        int l,r;
        cin>>l>>r;
        cout<<query(l-1,r-1)<<endl;
    }
    return 0;
}