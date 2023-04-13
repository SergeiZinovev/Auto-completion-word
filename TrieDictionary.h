#pragma once

#include <iostream>
#include <string.h>
const int ALPHABET_SIZE = 26;

// Tree node structure 
struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    // isEndOfWord - true, if the key is the end of the word
    bool isEndOfWord;
};

TrieNode* getNewNode(void);
void insert(TrieNode* root, std::string key);
bool search(TrieNode* root, std::string key);
bool isEmpty(TrieNode*);
TrieNode* remove(TrieNode*, std::string, int depth = 0);
void hasPrefix(TrieNode* node, int& cnt_ends);
void findMinPrefixes(TrieNode* root, char buf[], int ind, std::string& res);
void wordSubstitution(TrieNode* root, std::string& result, std::string currenWord);
void wordSubstitutionInner(TrieNode* root, char buf[], int indexChar, std::string& result, int& counterWords, bool endWord);

