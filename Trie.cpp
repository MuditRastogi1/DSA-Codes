#include<bits/stdc++.h>
using namespace std;

class TrieNode
{
    public:
    TrieNode* child[26];
    bool flag;
    TrieNode() {
     for(int i=0; i<26; i++) {
        this->child[i] = NULL;
     }
     flag = false;
    }
};

class Trie {
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* curr = root;
        for(auto ch : word) {
         int i = ch - 'a';
         if(!curr->child[i]) curr->child[i] = new TrieNode();
         curr = curr->child[i];
        }
     curr->flag = true;
    }
    
    bool search(string word) {
        TrieNode* curr = root;
        for(auto ch : word) {
         int i = ch - 'a';
         if(!curr->child[i]) return false;
         curr = curr->child[i];
        }
     return curr->flag;
    }
    
    bool startsWith(string prefix) {
        TrieNode* curr = root;
        for(auto ch : prefix) {
         int i = ch - 'a';
         if(!curr->child[i]) return false;
         curr = curr->child[i];
        }
     return true;
    }
};

int main()
{
    Trie trie;
    trie.insert("mudit");
    cout<<trie.search("mudit");
    return 0;
}