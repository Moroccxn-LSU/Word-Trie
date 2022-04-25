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
};
Node* convertCharToNode(char c) {
    Node* newNode = new Node();
    newNode->leadChar = c;
    newNode->isWord = false;
    newNode->rightSibling = nullptr;
    newNode->firstChild = nullptr;
    return newNode;
}
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
Node* findChild(Node* root, char c) {
    /*if (root == nullptr) {
        return nullptr;
    }*/
    Node* q = root->firstChild;
    if (q != nullptr) {
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
    Node* r = convertCharToNode(c);
    //root->firstChild = r;
    string ss = s.substr(1, s.length());
    Node* q = findChild(root, c);
    if (q == nullptr) {
        //Node* r = convertCharToNode(c);
        if (root != nullptr) {
            r->rightSibling = root->firstChild;
            root->firstChild = r;
        }
        insert(r, ss);
    }
    else {
        insert(q, ss);
    }
}
int main(){
    ifstream f("WORD.LST");
    Node* root = convertCharToNode('\0');
    string word;

    while (f >> word) {
        if (word.length() >= 4) {
            insert(root, word);
        }
    }
}

