// Sergio Leon <seleon>, Michael Lee <mil039>

#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H
//Data structures for lexicon and board should reside in this file.
//All of the operations your data structures support should be declared within your data structures.

using namespace std; 

/*
 * This class contains the variables and constructors for the
 * Ternary Search Tree nodes.
 */
class TSTNode {
public:
    TSTNode* left; //left node
    TSTNode* right; //right node
    TSTNode* middle; //middle node
    char word; //word of the node
    bool isPrefix; //prefix flag
    bool isEnd; //flag if at the end of tree

    TSTNode() : left(nullptr), right(nullptr), middle(nullptr), word(0), isPrefix(false), isEnd(false) {};

    TSTNode(const char& w) : left(nullptr), right(nullptr), middle(nullptr), word(w), isPrefix(false), isEnd(false) {};
};

class TST {
public:
    TSTNode* root; //node of root
    unsigned int size; //size of the tree

    void insert(TSTNode* &curr, string word, unsigned int pos);
    bool find(TSTNode* curr, string word, unsigned int pos);
    bool isPrefix(string word);

    TST() : root(nullptr), size(0) {};
};
   
#endif
