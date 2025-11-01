#include <bits/stdc++.h>
using namespace std;


//TRIE

struct Node {
    Node *next_node[26] = {};
    int freq[26] = {}; //to count frequencies of some prefix
    Node() {
        memset(next_node, 0, sizeof next_node);
        memset(freq, 0, sizeof freq);
    }
};

Node *root;

void insert(string s) {
    Node *ptr = root;
    for (int i = 0; i < (int)s.size(); i++) {
        int c = s[i] - 'a';
        if (!ptr->next_node[c])
            ptr->next_node[c] = new Node();
        ptr->freq[c]++;
        ptr = ptr->next_node[c];
    }
}

//count frequency of given prefix
int count(string s) {
    Node *ptr = root;
    for (int i = 0; i < (int)s.size(); i++) {
        int c = s[i] - 'a';
        if (!ptr->next_node[c])
            return 0;
        if (i == (int)s.size() - 1)
            return ptr->freq[c];
        ptr = ptr->next_node[c];
    }
    return 0;
}

/*
 USAGE
 root = new Node();
// insert strings, count them if 0 it DNE

  */