#include<bits/stdc++.h>
using namespace std;

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T> using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
	pbds<int> st;

    for(auto it : st) {
        cout<<it<<" ";
    } cout<<endl;
}

// // Note 1 :
// greater<int>    ......  for descending order
// less_equal<int> ......  for multiset (ascending order)


// // Available functions
//     st.insert(int)
//     st.erase(int)
//     *st.find_by_order(int)
//     st.order_of_key(int)
//     *st.lower_bound(int)
//     *st.upper_bound(int)



