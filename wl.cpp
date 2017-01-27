//
//  main.cpp
//  hw1
//
//  Created by Minzhen Yi on 1/25/17.
//  Copyright © 2017 Minzhen Yi. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "wl.h"
#include <ctype.h>
#include <string>
using namespace std;

void BSTree::insert(string key, int idx){
    BSTNode *new_node;
    BSTNode *cur, *pre;
    
    if(root == NULL){
        new_node = new BSTNode(key);
        root = new_node;
        new_node->arraySize += 1;
        new_node->cnt = (int*) realloc(new_node->cnt, new_node->arraySize*sizeof(int));
        new_node->cnt[new_node->arraySize-1] = idx;
        return;
    }
    cur = pre = root;
    
    while(cur != NULL){
        pre = cur;
        if(cur->key < key){
            cur = cur->right;
        }
        else if(cur->key > key){
            cur = cur->left;
        }
        else{
            // set existed node cnt
            cur->arraySize += 1;
            cur->cnt = (int*) realloc(cur->cnt, cur->arraySize*sizeof(int));
            cur->cnt[cur->arraySize-1] = idx;
            return;
        }
    }
    
    new_node = new BSTNode(key);
    if(pre->key > key){
        pre->left = new_node;
    }
    else if(pre->key < key){
        pre->right = new_node;
    }
    
    // set new_node cnt
    new_node->arraySize += 1;
    new_node->cnt = (int*) realloc(new_node->cnt, new_node->arraySize*sizeof(int));
    new_node->cnt[new_node->arraySize-1] = idx;
}

int BSTree::search(string key, int idx){
    BSTNode* cur = root;
    while(cur != NULL){
        if(cur->key == key){
            // idx is larger than the occurence # of word
            if(idx > cur->arraySize){
                return NULL;
            }
            return cur->cnt[idx-1];
        }
        else if(cur->key < key){
            cur = cur->right;
        }
        else{
            cur = cur->left;
        }
    }
    return NULL;
}

// parse command to string*
string* BSTree::parse_command(string command){
    int start, end, idx;
    start = end = idx = 0;
    string* res;
    
    while(end < command.size()){
        end = command.find(' ', start);
        // command starts with ' '
        if(end == -1){
            end = command.size();
        }
        if(end == start){
            while(end < command.size() && command[end] == ' '){
                end += 1;
            }
            // empty substr
            if(end == command.size()){
                if((res[0] == "load" and idx == 2) or (res[0] == "locate" and idx == 3) or res[0] == "new" or res[0] == "end"){
                    return res;
                }
                return NULL;
            }
            start = end;
            continue;
        }
        string substr = command.substr(start, end-start);
        start = end+1;
        // first part of command
        if(idx == 0){
            string lower_substr = lower(substr);
            if(lower_substr == "load"){
                res = new string[2];
            }
            else if(lower_substr == "locate"){
                res = new string[3];
            }
            else if(lower_substr == "new"){
                res = new string[1];
            }
            else if(lower_substr == "end"){
                res = new string[1];
            }
            else{
                return NULL;
            }
            idx += 1;
            res[0] = lower_substr;
        }
        else if(idx == 1){
            if(res[0] == "load"){
                res[1] = substr;
            }
            else if(res[0] == "locate"){
                res[1] = lower(substr);
            }
            else{
                return NULL;
            }
            idx += 1;
        }
        else if(idx == 2){
            if(res[0] == "locate"){
                if(isValidNum(substr)){
                    res[2] = substr;
                }
                else{
                    return NULL;
                }
            }
            else{
                return NULL;
            }
            idx += 1;
        }
        else{
            return NULL;
        }
    }
    
    if((res[0] == "load" and idx == 2) or (res[0] == "locate" and idx == 3) or res[0] == "new" or res[0] == "end"){
        return res;
    }
    return NULL;
}

// load file to parse and store
void BSTree::parse_file(string filename){
    
    int idx = 1;
    ifstream fin(filename);
    string s, word = "";
    
    while( getline(fin,s) )
    {
        for(int i = 0; i < s.size(); i++){
            if(isValidLetter(s[i])){
                word += s[i];
            }
            // has an invalid letter or it is the end of a line
            else if(not isValidLetter(s[i])){
                if(word != ""){
                    word = lower(word);
                    insert(word, idx);
                    word = "";
                    idx += 1;
                }
            }
        }
        if(word != ""){
            word = lower(word);
            insert(word, idx);
            word = "";
            idx += 1;
        }
    }
}

// upper to lower
string BSTree::lower(string s){
    for(int i = 0; i < s.size(); i++){
        if(s[i] >= 'A' && s[i] <= 'Z'){
            s[i] = s[i]-'A'+'a';
        }
    }
    return s;
}

// check if n in locate command is valid
bool BSTree::isValidNum(string s){
    if(s.size() == 0){
        return false;
    }
    for(int i = 0; i < s.size(); i++){
        if(not (s[i] >= '0' and s[i] <= '9')){
            return false;
        }
    }
    int num = stoi(s);
    if(num == 0){
        return false;
    }
    return true;
}

// check if chr is a valid word letter
bool BSTree::isValidLetter(char c){
    if(isalnum(c) or c == 39){
        return true;
    }
    return false;
}

void BSTree::destroy(BSTNode* n){
    if(n != NULL){
	cout << "!" << endl;
        destroy(n->left);
        destroy(n->right);
        free(n->cnt);
	n->cnt = NULL;
        delete n;
	n = NULL;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    string command, *parsed;
    BSTree bstree;
    
    while(1){
        cout << '>';
        cin.clear();
        getline(cin, command);
        cin.clear();
        parsed = bstree.parse_command(command);
        if(parsed == NULL){
            cout << "ERROR: Invalid command" << endl;
        }
        else{
            if(parsed[0] == "load"){
                bstree.destroy(bstree.root);
                bstree.root = NULL;
                bstree.parse_file(parsed[1]);
            }
            else if(parsed[0] == "locate"){
                int res = bstree.search(parsed[1], stoi(parsed[2]));
                if(res != NULL){
                    cout << res << endl;
                }
                else{
                    cout << "No matching entry" << endl;
                }
            }
            else if(parsed[0] == "new"){
                bstree.destroy(bstree.root);
                bstree.root = NULL;
            }
            else if(parsed[0] == "end"){
                bstree.destroy(bstree.root);
                bstree.root = NULL;
                break;
            }
        }
	delete[] parsed;
    }
    return 0;
}
