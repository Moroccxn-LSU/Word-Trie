// Adam Elkhanoufi
// CSC 3102
// Word Trie
// 04/20/2022
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Node {
    public:

        char leadChar;
        bool isWord;
        Node* rightSibling;
        Node* firstChild;

        Node(char c) {
            leadChar = c;
            isWord = false;
            rightSibling = nullptr;
            firstChild = nullptr;
        }
};
void preorder(Node* root, string prefix, string forbidden) {
    if (root == nullptr) { 
        return; 
    }
    if (root->isWord) { 
        cout << prefix << endl;
    }
    prefix = prefix + root->leadChar;
    Node* q = root->firstChild;
    while (q != nullptr) {
        if (forbidden.find(q->leadChar) < forbidden.length()) {
            q = q->rightSibling;
        }
        else {
            preorder(q, prefix, forbidden);
        }
    }
}
//Issue is here when stall is trying to be inserted it says root->firstchild->rightsibling is null
Node* findChild(Node* root, char c) {
    if (root->firstChild == nullptr) {
        return nullptr;
    }
    Node* q = root->firstChild;
    if (q->rightSibling != nullptr) {
        while (q->leadChar != c) {
            q = q->rightSibling;
        }
    }
    return q;
}
Node* search(Node* root, string qprefix) {
    if (qprefix.length() == 0) {
        return root;
    }
    Node* q = findChild(root, qprefix[0]);
    if (q == nullptr) {
        return nullptr;
    }
    return search(q, qprefix.substr(1, qprefix.length()));
}
void Query(Node* root, string qprefix, string forbidden) {
    Node* q = search(root, qprefix);
    preorder(q, qprefix, forbidden);
}
void insert(Node* root, string s) {
    if (s.empty()) {
        root->isWord = true;
        return;
    }
    char c = s[0];
    string ss = s.substr(1, s.length());
    Node* q = findChild(root, c);
    if (q == nullptr) {
        Node* r = new Node(c);
        r->rightSibling = root->firstChild;
        root->firstChild = r;
        insert(r, ss);
    }
    else {
        insert(q, ss);
    }
}
int main(){
    ifstream f("inputFile.txt");
    Node* root = new Node('\0');
    string word, instruction, prefix, forbidden;
    int numInstructions;
    
    f >> numInstructions;

    while (f >> instruction) {
        if (instruction == "IN") {
            f >> word;
            insert(root, word);
        }
        else if (instruction == "QU") {
            f >> prefix;
            f >> forbidden;
            Query(root, prefix, forbidden);
        }
    }
    return 0;
}

