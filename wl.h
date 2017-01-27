//
//  hw1.h
//  hw1
//
//  Created by 易旻臻 on 1/25/17.
//  Copyright © 2017 Minzhen Yi. All rights reserved.
//

#ifndef hw1_h
#define hw1_h
using namespace std;

//class LinkedNode{
//public:
//    LinkedNode *next;
//    int value;
    
//    LinkedNode(int v = 0){
//        next = NULL;
//        value = v;
//    }
//};

class BSTNode{
public:
    string key;
    BSTNode *left;
    BSTNode *right;
//    LinkedNode *cnt;
    int *cnt;
    int arraySize;
    
    BSTNode(string k){
        key = k;
        left = right = NULL;
        cnt = NULL;
        arraySize = 0;
    }
    BSTNode(){}
};

class BSTree{
public:
    BSTNode* root;
    
    BSTree(){
        root = NULL;
    }
    ~BSTree(){
    }
    
    // insert string
    void insert(string key, int idx);
    // search a string
    int search(string key, int idx);
    // parse a command
    string* parse_command(string command);
    // parse a file
    void parse_file(string filename);
    // upper to lower
    string lower(string s);
    // test if a string is a valid number
    bool isValidNum(string s);
    // check if a chr is a valid word letter
    bool isValidLetter(char c);
    // destroy the tree
    void destroy(BSTNode* n);
};

#endif /* hw1_h */
