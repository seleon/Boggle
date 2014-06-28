#include "baseboggleplayer.h"
#include "time.h"
#include "boggleplayer.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <cstdlib>
#include <thread>

int main (int argc, char* argv[]) {

  std::ifstream infile;
  infile.open("lex.txt");
  string s;
  BaseBogglePlayer * p = new BogglePlayer();
  std::set<string> lex;
  std::set<string> words;
  string** board;
  board = new string* [20];
  string word;
  int row = 20, col = 23;

  while(getline(infile, s)){
      lex.insert(s);
  }

  infile.close();
  infile.open("brd.txt");

  for(int i = 0; i < row; i++) { 
    board[i] = new string[col];
  } 

  getline(infile, word);
  getline(infile, word);

  for(int i = 0; i < row; i++) {
    for(int j = 0; j < col; j++) {
      getline(infile, word);
      board[i][j] = word;
      cout << board[i][j];
    }
    cout << endl;
  } 
   
  infile.close();
  p->buildLexicon(lex);

  if(!p->isInLexicon("abbbcdac")) {
    std::cerr << "Apparent problem with isInLexicon #3." << std::endl;
    return -1;
  }
  if(!p->isInLexicon("aaacbcdce")) {
    std::cerr << "Apparent problem with isInLexicon #3." << std::endl;
    return -1;
  }

  p->setBoard(20, 23, board);
  p->getAllValidWords(2, &words);

  cout << endl << words.size();
/*
  string wordA("a");
  string wordX("x");
  lex.insert(wordA);
  lex.insert("z");
  lex.insert("bats");
  lex.insert("blame");
  lex.insert("stab");
  lex.insert("quack");
  lex.insert("stack");
  lex.insert("ASFDUENKFNEKJNJKJJ");
  string row0[] = {"Qu","c", "u", "o"};
  string row1[] = {"b","A", "t", "S"};
  string row2[] = {"L","C", "M", "E"};
  string row3[] = {"d","k", "a", "f"};
  string* board[] = {row0,row1, row2, row3};
  set<string> words;
  vector<int> locations;

  p->buildLexicon(lex);

  p->setBoard(rows,cols,board);

  
  if(!p->isInLexicon("bats")) 
    std::cerr << "Apparent problem with isInLexicon #1." << std::endl;

  if(p->isInLexicon(wordX)){
    std::cerr << "Apparent problem with isInLexicon #2." << std::endl;
    return -1;
  }
  if(!p->isInLexicon(wordA)) {
    std::cerr << "Apparent problem with isInLexicon #3." << std::endl;
    return -1;
  }

  locations = p->isOnBoard("quack");
  if(locations.size() != 4 && locations[2] != 6) {
    std::cerr << "Apparent problem with isOnBoard #1." << std::endl;
    return -1;
  }

  locations.clear();
  locations = p->isOnBoard("asdasdf");
  if(locations.size() != 0) {
    std::cerr << "Apparent problem with isOnBoard #3." << std::endl;
    return -1;
  }

  if(!p->getAllValidWords(3,&words)) {
    std::cerr << "Apparent problem with getAllValidWords #1." << std::endl;
    return -1;
  }; 

  if(words.size() != 5 || words.count("bats") != 1) {
    std::cerr << "Apparent problem with getAllValidWords #2." << std::endl;
    return -1;
  }

  delete p;*/
  return 0;

}
