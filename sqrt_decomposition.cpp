#include<bits/stdc++.h>
using namespace std;
 
int main()
{
    vector<int> arr = {1,2,3,4,5};
    vector<vector<int>> queries = {{0,0}, {1,1}, {2,4}};

    int n = arr.size();
    int len = ceil(sqrt(n)); // size of the block and the number of blocks
    vector<int> sq (len);

    for (int i=0; i<n; i++) {
        sq[i / len] += arr[i]; //initializing sqrt values with their respective range
    }

    for (auto q : queries) 
    {
      int l = q[0], r = q[1];
      int sum = 0;
        for (int i=l; i<=r; )
        {
            if (i % len == 0 && i + len - 1 <= r) { // if the whole block starting at i belongs to [l, r]
                sum += sq[i / len];
                i += len;
            }
            else { //perform manually for partial blocks
                sum += arr[i];
                ++i;
            }
        }
     cout<<sum<<" ";
    }
    return 0;
}