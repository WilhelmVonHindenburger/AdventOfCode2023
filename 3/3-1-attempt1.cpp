//Advent of code 2023, Problem 3, Part 1, Attempt 1
//By Wilh3lm, released under GPL3
//FAILED
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream in;
/* //FAILED ATTEMPT
void open(vector<vector<char>>& board, ifstream& i){
  //Assumes board is empty
  cout << "Enter file name.\n";
  string filename;
  cin >> filename;
  cout << "File name: \"" << filename << "\"\n";
  i.open(filename);
  cout << "TEST";
  
  while(!i){
    cout << "File not found. Try again.\n";
    cin >> filename;
    i.open(filename);
  }
  //Read from file
  //Calculate board size
  int x=0;
  int y=0;
  char c;
  while(i >> c){
    //While reading characters
    if(c=='\n'){
      //Newline
      board.push_back({});
      y++;
    }else{
      board[y].push_back(c);
    }
  }
  in.close();
}
*/

const int boardSize=140;

//ATTEMPT 2 (munmap_chunk error)
void open(vector<vector<char>>& board, ifstream& i){
  cout << "Enter file name.\n";
  string filename;
  cin >> filename;
  cout << "File name: \"" << filename << "\"\n";
  i.open(filename);
  while(!i){
    cout << "File not found. Try again.\n";
    cin >> filename;
    i.open(filename);
  }
  //Read from file
  //While there are empty spaces on the board:
  //  Read one character from file
  //  If EOF, fill rest of board with .
  //  If it is . or @ add it to the board
  //  All other characters are ignored
  int x=0;
  int y=0;
  char c;
  while((x < boardSize)&&(y<boardSize)){
    if(!(i >> c)){
      //End of file
      c='E';
      for(; y<boardSize; y++){
        for(; x<boardSize; x++){
          board[y][x]='.';
        }
        x=0;
      }
      i.close();
      return;
    }else while(c=='\n') i >> c; // Skip newlines
    cout << "Reading character \"" << c << "\"\n";
    board[y][x]=c;
    if(x==boardSize-1){
      x=0;
      y++;
      cout << "NEW LINE\n\n";
      if(y==boardSize){
        //End of board
        cout << "END OF BOARD\n\n";
        return;
      }
    }else{
      x++;
    }
  }
  i.close();
}

int main(){
  //Create board
  vector<char> row(boardSize);
  row={'\0'};
  vector<vector<char>> board;
  for(int i=0; i<boardSize; i++)board.push_back(row);
  cout << "Board has " << board.size() << " rows.\n";
  
  open(board, in);
  for(int y=0; y<board.size(); y++){
    cout << "ROW " << y << endl;
    for(int x=0; x<board[y].size(); x++){
      cout << board[y][x] << endl;
    }
    cout << endl;
  }
  return 0;
}
