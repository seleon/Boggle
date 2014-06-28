// Sergio Leon <seleon>, Michael Lee <mil039>

#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H
#include "baseboggleplayer.h"
#include "boggleutil.h"
using namespace std;


/*
 * This class contains the variables and constructors
 * for functions in boggleplayer.cpp and the nodes
 * for the board elements.
 */
class Node{
    public:
        string word; // Representation of each node on board
        bool visited; // Flag to check if node has been traversed
        int inRow; // Row that node is found in
        int inCol; // Column that node is found in
        vector<Node*> adjacent; // Adjacency list

        // Constructor
        Node(string w, bool v, int r, int c) :
            word(w), visited(v), inRow(r), inCol(c) {}; 
};

class BogglePlayer : public BaseBogglePlayer {
  public:
  void buildLexicon(const set<string>& word_list);
  
  void setBoard(unsigned int rows, unsigned int cols, string** diceArray); 

  bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
  
  bool isInLexicon(const string& word_to_check); 

  vector<int> isOnBoard(const string& word);

  void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);

  bool find(Node* node, string word, unsigned int pos);

  void setAdjacent();
 
  bool stringsEqual(string s1, string s2, unsigned int pos);

  void traverse(string word, unsigned int min, set<string>* words, vector<Node*> adjacent);

  BogglePlayer() {
  }
  
  ~BogglePlayer() {
  }

  private:
      TST* tree; // Ternary search tree
      vector<vector<Node*>> board; // Board representation
      vector<int> position; // Row major order vector
      int row; // Row size
      int column; // Column size
      bool lexiconBuilt; // Flag for lexicon built status
      bool boardSet; // Flag for board set status
};

#endif
