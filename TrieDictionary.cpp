#include "TrieDictionary.h"

// Returns a new node with empty children
TrieNode* getNewNode(void)
{
    // Allocating memory to a new node
    struct TrieNode* pNode = new TrieNode;

    // set the end-of-word flag to false
    pNode->isEndOfWord = false;

    // Initialize the children with a null pointer
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

//Inserts the key into the tree
void insert(TrieNode* root, std::string key)
{
    TrieNode* node = root;

    for (size_t i = 0; i < key.length(); i++)
    {
        // Calculate the index in the alphabet through the offset with respect to the first letter
        int index = key[i] - 'a';

        // if the pointer is empty, i.e. there are no children with this prefix
        // create a new node
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // mark the last node as a leaf, i.e. the end of the word
    node->isEndOfWord = true;
}

// Returns true if the key is in the tree, otherwise false 
bool search(struct TrieNode* root, std::string key)
{
    struct TrieNode* node = root;

    for (size_t i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

// Returns true if root has a leaf, otherwise false 
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Recursive function to remove a key from the tree 
TrieNode* remove(TrieNode* root, std::string key, int depth)
{
    // if tree is empty 
    if (!root)
        return nullptr;

    // If the end of the key has reached
    if (depth == key.size()) {

        // This node is no longer the end of the word 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // If the key is not a prefix, delete it
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // If we have not reached the end of the key, we recursively call for the child of the corresponding symbol 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // If the root has no child word and it does not end in another word. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }

    // Return the new root
    return root;
}
void hasPrefix(TrieNode* nodeCurrent, int& countEnds)
{
    if (nodeCurrent->isEndOfWord) // if the word has run out add to the counter
        countEnds++;
    for (size_t i = 0; i < ALPHABET_SIZE; i++) // go up the tree and count the ends of the words
    {
        if (nodeCurrent->children[i])
        {
            hasPrefix(nodeCurrent->children[i], countEnds);
        }
    }
}

void findMinPrefixes(TrieNode* root, char buf[], int ind, std::string& res)
{


    if (!root)
        return;
    int count = 0;
    hasPrefix(root, count);
    if (count == 1)
    {
        buf[ind] = '\0'; // finish the string
        res += std::string(buf) + " "; // add to the result and a space after
        return; // return from recursion
    }
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (root->children[i])
        {
            char currentChar = i + 'a';
            buf[ind] = currentChar;
            findMinPrefixes(root->children[i], buf, ind + 1, res);
        }
    }
}


void wordSubstitution(TrieNode* root, std::string& result, std::string currentWord) // word search function for substitution
{
    if (!root) // if a tree is empty
        return;
    if (currentWord.empty())// If there is nothing to compare it with
        return;
    char buf[50]; // buffer in which we will put the characters suitable for auto-substitution
    size_t indexChar = 0;  // index for buffer
    int counterWords = 0; // counter of words that will be offered for autosubstitution
    bool charPresence = true; // check if there are characters in the tree that match the entered one
    while (indexChar < currentWord.length()) // search for matches of the entered string with the presence in the tree
    {
        if (!charPresence) // if the characters do not have at least one match 
            return;
        charPresence = false;
        for (int i = 0; i < ALPHABET_SIZE; ++i) // looking for a match in the node
        {
            if (root->children[i]) // if there is a symbol in the node
            {
                if (currentWord[indexChar] == i + 'a') // and if it matches the current character of the entered string 
                {
                    buf[indexChar] = i + 'a';  //  add a character to the buffer
                    indexChar++;               // increase the index
                    root = root->children[i];  // Go to the child node
                    charPresence = true;        // report that the symbol has been found
                    i = ALPHABET_SIZE;
                    if (root->isEndOfWord && indexChar == currentWord.length()) //  if the last character of the entered word coincides with the end of the word in the dictionary
                    {
                        buf[indexChar] = '\0'; // end the string
                        result += std::string(buf) + " "; // add a word to the result 
                        counterWords++;                   // increment the word count

                    }
                    else if (indexChar == currentWord.length()) // if the typed word is finished
                    {
                        buf[indexChar] = '\0'; // end the string                  
                        result += std::string(buf); // add a word to the result 

                    }

                }
            }
        }
    }
    if (counterWords == 0)  // if no words for autocomposition were found
        result.clear();      // clean results
    charPresence = false; // since isEndOfWord can be true, the variable will act as a string end flag
    wordSubstitutionInner(root, buf, indexChar, result, counterWords, charPresence);// Run the word search algorithm
}
void wordSubstitutionInner(TrieNode* root, char buf[], int indexChar, std::string& result, int& counterWords, bool endWord)// internal word search function for substitution
{
    if (endWord)  // If we've reached the end of the word
    {
        buf[indexChar] = '\0'; // end the string
        result += std::string(buf) + " "; // add to result
        counterWords++;                //  increase counter
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i)// look for a continuation of the word
    {
        if (counterWords >= 3) // If the words are already three
            return;
        if (root->children[i]) // if there is the following symbol
        {
            buf[indexChar] = i + 'a';
            endWord = root->children[i]->isEndOfWord;
            wordSubstitutionInner(root->children[i], buf, indexChar + 1, result, counterWords, endWord);
        }
    }
}