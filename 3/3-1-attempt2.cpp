//Advent of code 2023, Problem 3, Part 1, Attempt 2
//By Wilh3lm, released under GPL3
//COMPLETED
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
const int boardSize=140;
ifstream in;

class NumPos{
  public:
    int x=-1;
    int y=-1;
    int length=0;
};

class Number{
  public:
    NumPos position;
    int value=0;
};


int main(){
  vector<string> board;
  cout << "Enter file name.\n";
  string filename;
  cin >> filename;
  cout << "File name: \"" << filename << "\"\n";
  in.open(filename);
  while(!in){
    cout << "File not found. Try again.\n";
    cin >> filename;
    in.open(filename);
  }
  cout << "File opened.\n";
  string currentLine;
  while(!in.eof()){
    currentLine="";
    getline(in, currentLine);
    board.push_back(currentLine);
  }
  board.pop_back(); // Empty line from EOF
  cout << "File has been read.\n";
  vector<NumPos> numberPositions;
  NumPos currentNumberPosition;
  for(int i=0; i<board.size(); i++){
    //Search through each row
    for(int j=0; j<board[i].length(); j++){
      //Search within strings
      if((board[i][j]>='0') && (board[i][j]<='9')){
        //Number
        currentNumberPosition.y=i;
        if(j==0){
          //Line begins with number
          currentNumberPosition.x=0;
          currentNumberPosition.length=1;
        }
        else if((board[i][j-1]>='0') && (board[i][j-1]<='9')){
          //If previous character is number
          currentNumberPosition.length++;
        }
        else if(!((board[i][j-1]>='0') && (board[i][j-1]<='9'))){
          //If previous character is NOT A NUMBER
          currentNumberPosition.x=j;
          currentNumberPosition.length=1;
        }
      }
      else{
        //Not number
        if(currentNumberPosition.y != -1) numberPositions.push_back(currentNumberPosition);
        //if(currentNumberPosition.y != -1) cout << "Number found at row " << currentNumberPosition.y << ", column " << currentNumberPosition.x << " and with length " << currentNumberPosition.length << endl;
        //Yes, zero-indexed positions
        currentNumberPosition.x=-1;
        currentNumberPosition.y=-1;
        currentNumberPosition.length=0;
      }
    }
  }
  vector<Number> numbers;
  Number currentNumber;
  for(int i=0; i<numberPositions.size(); i++){
    //Search through number positions, convert them to numbers
    string numberString=board[numberPositions[i].y].substr(numberPositions[i].x, numberPositions[i].length);
    currentNumber.position=numberPositions[i];
    currentNumber.value=stoi(numberString);
    cout << "Number with value " << currentNumber.value << " found.\n";
    numbers.push_back(currentNumber);
  }
  int total=0;
  for(int i=0; i<numbers.size(); i++){
    //Search through each number, find the symbols, add to total
    bool isPartNumber=false;
    //Figure out if it's near a symbol
    
    int x1=max(numbers[i].position.x-1, 0);
    int x2=min(numbers[i].position.x+numbers[i].position.length, static_cast<int>(board.size())-1);
    int y1=max(numbers[i].position.y-1, 0);
    int y2=min(numbers[i].position.y+1, static_cast<int>(board.size())-1);
    
    for(int y=y1; y<=y2; y++){
      for(int x=x1; x<=x2; x++){
        switch(board[y][x]){
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
          case '.':
            break;
          default:
            isPartNumber=true;
        }
      }
    }
    
    if(isPartNumber){
      total += numbers[i].value;
      cout << "Part number " << numbers[i].value << " found at row " << numbers[i].position.y << ", column " << numbers[i].position.x << endl;
    }
  }
  cout << "Total: " << total << endl;
}
