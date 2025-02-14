#include<bits/stdc++.h>
using namespace std;

   //strictly greater element
    vector<int> prevGreaterElement(vector<int> nums) {
        vector<int> ans(nums.size(),-1);
        stack<int> st;

        for(int i=0; i<nums.size(); i++) {
            while(!st.empty() && nums[st.top()] <= nums[i]) {
                st.pop();
            }
         if(!st.empty()) ans[i] = st.top();
         st.push(i);
        }
     return ans;
    }
    
    //strictly
    vector<int> nextGreaterElement(vector<int>& nums) {
        vector<int> ans(nums.size(),nums.size());
        stack<int> st;

        for(int i=nums.size()-1; i>=0; i--)
        {
            while(!st.empty() && nums[st.top()] <= nums[i]) { //remove '=' sign to relax condition of strictly greater
             st.pop();
            }
         if(!st.empty()) ans[i] = st.top();
         st.push(i);
        }
     return ans;
    }

int main()
{
    vector<int> nums = {1,4,5,2,3,5,7};
    vector<int> prev = prevGreaterElement(nums);
    vector<int> next = nextGreaterElement(nums);
    return 0;
}