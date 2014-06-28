// Sergio Leon <seleon>, Michael Lee <mil039>

#include <string>
#include <cstring>
#include"boggleutil.h"

//In this file, implement all of the operations your data structures support (you have declared these operations in boggleutil.h).


/*
 * This function takes in three arguments. It uses 
 * a recursive method to insert values into the 
 * Ternary Search Tree.
 */
void TST::insert(TSTNode* &curr, string word, unsigned int pos) {
    char c = word[pos];
    //checks if the node has been created yet
    if(curr == nullptr) 
        curr = new TSTNode(word[pos]);
    //check if current position is smaller
    if(c > curr->word)
        insert(curr->right, word, pos);
   //checks if current position is larger
    else if (c < curr->word) 
        insert(curr->left, word, pos);
   //checks if the value is at the end
    else {
	//if value and length are equal, it is the end
        if(pos + 1 == word.length())
            curr->isEnd = true;
       //otherwise recurse
        else 
            insert(curr->middle, word, pos + 1);
    }
}


/*
 * This function takes in three arguments and also 
 * uses a recursive method to find values into the 
 * Ternary Search Tree.
 */

bool TST::find(TSTNode* curr, string word, unsigned int pos)
{
    char c = word[pos];

    //checks if node is null or position is out of scope
    if (curr == nullptr || pos > word.length())
        return false;
    //checks if current position is smaller
    if(c > curr->word)
        return find(curr->right, word, pos);
    //checks if current position is larger
    else if (c < curr->word) 
        return find(curr->left, word, pos);
    //checks if you have reached the end or not
    else {
        //if the value has reached the end
        if((pos + 1) == word.length())
            return curr->isEnd;
	//recurse if it is not at the end yet
        else 
            return find(curr->middle, word, pos + 1);
    }
}


/*
 * This function takes in one argument and 
 * iterates through the tree. It checks if 
 * the word being passed in is the prefix of
 * another word in the Ternary Search Tree.
 */
bool TST::isPrefix(string word) {
    TSTNode* curr = root;
    unsigned int i = 0;
    //loop through string word
    while(i <= word.length()) { 
        //checks if the current node is null or out of scope
        if(curr == nullptr || i >= word.length())
            return false;
	//checks if the length of the words are equal
        if((word.length() - 1) == i && word[i] == curr->word) 
            return true;
	//checks if the value is larger than the word
        if(word[i] > curr->word)
            curr = curr->right;
       //checks if the value is smaller than the word
        else if(word[i] < curr->word) 
            curr = curr->left;
	//checks if the value is in the middle
        else {
            curr = curr->middle;
            i++;
        }
    }

    return false;
}
