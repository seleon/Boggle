// Sergio Leon <seleon>, Michael Lee <mil039>

#include "boggleplayer.h"
#include "boggleutil.h"
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

/*  This function takes as argument a set containing the words
 *  specifying the official lexicon to be used for the game. 
 *  The words are loaded into a ternary search tree.
 */
void BogglePlayer::buildLexicon(const set<string>& word_list){
    tree = new TST(); //Ternary search tree
   
    // Iterate through the word list and insert into tree 
    for(set<string>::const_iterator it = word_list.begin(); it != word_list.end(); it++) {
         string word = *it;
         tree->insert(tree->root, word, 0); 
    }

    // Set lexiconBuilt flag 
    lexiconBuilt = true;
}


/*  This function takes as arguments the number of rows and 
 *  columns in the board, and an array of arrays of strings 
 *  representing what is shown on the face of dice on a
 *  Boggle board. The board and the adjacency list of each
 *  node are set.
 */
void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray) {
   
    // Go through every row in board
    for(unsigned int i = 0; i < rows; i++) {
        vector<Node*> boardRows; 

        // Go through every column in board, fill boardRows vector
        for(unsigned int j = 0; j < cols; j++) {
            string dice = diceArray[i][j];
  
            // Lowercase word set as Node, pushed into vector
            std::transform(dice.begin(), dice.end(), dice.begin(), ::tolower);
            Node* temp = new Node(dice, false, i, j);
            boardRows.push_back(temp);
        }

        // Set row vector
        board.push_back(boardRows);
    }

    // Set boardSet flag and row, column members
    boardSet = true;
    row = rows;
    column = cols;

    // Set adjacency matrix
    setAdjacent();
}

/*  This function recursively traverses the adjacency list
 *  of a Node choosing paths of any words that are prefixes
 *  of any other word in the lexicon.
 */
void BogglePlayer::traverse(string word, unsigned int min, set<string>* words, vector<Node*> adjacent) {

    // Go through adjacency list
    for(unsigned int i = 0; i < adjacent.size(); i++) {

        // Check if adjacent has been visited
        if(adjacent[i]->visited == false) {
            adjacent[i]->visited = true;
            string w = word + adjacent[i]->word;

            //Insert into set if larger than minimum length and in lex
            if(w.length() >= min && isInLexicon(w)) 
                words->insert(w);
          
            // Recurse if word is a prefix of another 
            if(tree->isPrefix(w)) 
                traverse(w, min, words, adjacent[i]->adjacent);
       
            adjacent[i]->visited = false;
        }
    }
}
   
/* This function takes two arguments: an int specifying a minimum word length, and a
 * pointer to a set of strings. It will return true, after filling the set with all 
 * the words that are valid.
 */
bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words) {

    // Exit if board or lexicon have not been set
    if(!boardSet || !lexiconBuilt) 
        return false;

    // Set all elements to not visited
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < column; j++) 
            board[i][j]->visited = false;
    }

    // Go through each element
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < column; j++) {
            string word = board[i][j]->word;
            board[i][j]->visited = true;

            // Insert into set if word length greater than minimum and in lex
            if(word.length() >= minimum_word_length && isInLexicon(word)) 
                words->insert(word);
           
            // Traverse if element's word is prefix 
            if(tree->isPrefix(word)) 
                traverse(word, minimum_word_length, words, board[i][j]->adjacent);
            
            board[i][j]->visited = false;
        }
    }

    return true;
}

/* This function takes as argument a const string passed by
 * reference. The function returns true if the word is in 
 * the lexicon, and returns false if it is not.
 */
bool BogglePlayer::isInLexicon(const string& word_to_check) {

    // Exit if lexicon has not been built
    if(!lexiconBuilt) 
        return false;
    else 
         
        // Find word in tree
        return tree->find(tree->root, word_to_check, 0);
}
  
/* This function sets the adjaceny list
 * of every Node in the board.
 */ 
void BogglePlayer::setAdjacent() {

    // Go through every element in board
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < column; j++) {
 
            // Upper left corner
            if(i == 0 && j == 0) {
                board[i][j]->adjacent.push_back(board[i][j+1]);
                board[i][j]->adjacent.push_back(board[i+1][j+1]);
                board[i][j]->adjacent.push_back(board[i+1][j]);
            }

            // Top right corner
            else if(i == 0 && j == column-1) {
                board[i][j]->adjacent.push_back(board[i][j-1]);
                board[i][j]->adjacent.push_back(board[i+1][j-1]);
                board[i][j]->adjacent.push_back(board[i+1][j]);
            }

            // Bottom right corner
            else if(i == row-1 && j == column-1) {
                board[i][j]->adjacent.push_back(board[i][j-1]);
                board[i][j]->adjacent.push_back(board[i-1][j-1]);
                board[i][j]->adjacent.push_back(board[i-1][j]);
            }

            // Bottom left corner
            else if(i == row-1 && j == 0) {
                board[i][j]->adjacent.push_back(board[i-1][j]);
                board[i][j]->adjacent.push_back(board[i-1][j+1]);
                board[i][j]->adjacent.push_back(board[i][j+1]);
            }

            // Top edge
            else if(i == 0) {
                board[i][j]->adjacent.push_back(board[i][j-1]);
                board[i][j]->adjacent.push_back(board[i+1][j-1]);
                board[i][j]->adjacent.push_back(board[i+1][j]);
                board[i][j]->adjacent.push_back(board[i+1][j+1]);
                board[i][j]->adjacent.push_back(board[i][j+1]);
            }

            // Bottom edge
            else if(i == row-1) {
                board[i][j]->adjacent.push_back(board[i][j-1]);
                board[i][j]->adjacent.push_back(board[i-1][j-1]);
                board[i][j]->adjacent.push_back(board[i-1][j]);
                board[i][j]->adjacent.push_back(board[i-1][j+1]);
                board[i][j]->adjacent.push_back(board[i][j+1]);
            }

            // Left edge
            else if(j == 0) {
                board[i][j]->adjacent.push_back(board[i-1][j]);
                board[i][j]->adjacent.push_back(board[i-1][j+1]);
                board[i][j]->adjacent.push_back(board[i][j+1]);
                board[i][j]->adjacent.push_back(board[i+1][j+1]);
                board[i][j]->adjacent.push_back(board[i+1][j]);
            }

            // Right edge
            else if(j == column-1) {
                board[i][j]->adjacent.push_back(board[i-1][j]);
                board[i][j]->adjacent.push_back(board[i-1][j-1]);
                board[i][j]->adjacent.push_back(board[i][j-1]);
                board[i][j]->adjacent.push_back(board[i+1][j-1]);
                board[i][j]->adjacent.push_back(board[i+1][j]);
            }

            // Not on edge or corner
            else {
                board[i][j]->adjacent.push_back(board[i-1][j-1]);
                board[i][j]->adjacent.push_back(board[i-1][j]);
                board[i][j]->adjacent.push_back(board[i-1][j+1]);
                board[i][j]->adjacent.push_back(board[i][j-1]);
                board[i][j]->adjacent.push_back(board[i][j+1]);
                board[i][j]->adjacent.push_back(board[i+1][j-1]);
                board[i][j]->adjacent.push_back(board[i+1][j]);
                board[i][j]->adjacent.push_back(board[i+1][j+1]);
            }
        }
    }
}

/* This function returns true if both strings that are passed in are
 * equal relative to a given position
 */ 
bool BogglePlayer::stringsEqual(string s1, string s2, unsigned int pos) {
    bool flag = true;

    // Go through each element of string
    for(unsigned int i = 0; i < s1.length(); i++) {

        // Set flag if any element of s1 and s2 do not match
        if(s1[i] != s2[i + pos] || i + pos >= s2.length())
            flag = false;  
    }
    
    // Return true if flag has not changed
    if(flag) 
        return true;
    else
        return false;
}

/* This function recursively traverses the adjacency list of a 
 * Node and fills the position vector of the board.
 */
bool BogglePlayer::find(Node* node, string word, unsigned int pos) { 
    bool flag = false;
    unsigned int i = 0; 

    // Go through adjacency list if given position fits word length
    if(pos < word.length()) {
        while(i < node->adjacent.size()) {

            // Check for string equality
            if(stringsEqual(node->adjacent[i]->word, word, pos) && node->adjacent[i]->visited == false) {
                node->adjacent[i]->visited = true;
  
                // Push row major index into position vector 
                position.push_back(node->adjacent[i]->inRow*column +node->adjacent[i]->inCol);
                
                // Return true if adjacent node's word length plus offset matches     
                if(pos + node->adjacent[i]->word.length() == word.length()) 
                    return true;
               
                // Return true if find successful
                flag = find(node->adjacent[i], word, pos +  node->adjacent[i]->word.length());
                if(flag) 
                    return true;
 
                // Pop from position vector and reset visited flag 
                node->adjacent[i]->visited = false;
                position.pop_back();
            } 
                
            i++;
        }
    }

    // Given position does not fit word length
    else if(pos == word.length()) 
        return true;
    else if(pos > word.length()) 
        return false;

    // Return flag status
    if(flag) 
        return true;
    else
        return false;
}

/* This function takes as argument a string passed 
 * by reference and returns a vector with integers 
 * specifying the locations of dice that can be used 
 * to form the word, in the order that spells the word. 
 */
vector<int> BogglePlayer::isOnBoard(const string& word) {
   
    // Return empty vector if board has not been set 
    if(!boardSet) {
        position.clear();
        return position;
    }
   
    // Set all elements to unvisited 
    for(int i = 0; i < row; i++) { 
        for(int j = 0; j < column; j++) 
           board[i][j]->visited = false;
    }
  
    // Go through each element in board 
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < column; j++) {

            // Check for string equality
            if(stringsEqual(board[i][j]->word, word, 0)) {
                board[i][j]->visited = true;
              
                // Push back row major index 
                position.clear(); 
                position.push_back(i*column + j);

                // Return success of find
                if(find(board[i][j], word, board[i][j]->word.length())) 
                    return position;
            } 
        }
    }

    // Reset all visited flags
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < column; j++)
            board[i][j]->visited = false;
    }

    // Clear position vector and return
    position.clear(); 
    return position; 
}

void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {
}

