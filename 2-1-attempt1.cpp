//Advent of Code 2023, Problem 2, Part 1, Attempt 1 (UNSUCCESSFUL)
//By Wilh3lm, released as GPL3
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class Draw{
public:
  int red=0;
  int green=0;
  int blue=0;
};

class Game{
public:
  vector<Draw> draws;
  int id;
};

string trimStart(string text, int characters){
  //Removes the first X characters from the text string
  string output="";
  for(int i=characters; i<text.length(); i++){
    output += text[i];
  }
  return output;
}

ifstream in;

int main(){
  cout << "Enter file name.\n";
  string filename;
  cin >> filename;
  in.open(filename);
  string currentLine;
  const int maxRed=12;
  const int maxGreen=13;
  const int maxBlue=14;
  int currentRed, currentGreen, currentBlue=0;
  Game currentGame;
  Draw currentDraw;
  stringstream lineStream;
  while(getline(in, currentLine)){
    //Reset current info
    currentDraw=Draw();
    currentGame=Game();
    currentRed=0;
    currentGreen=0;
    currentBlue=0;
    //Loop over all lines
    cout << currentLine << endl;
    lineStream=stringstream("");
    lineStream << trimStart(currentLine, 5);
    lineStream >> currentGame.id;
    cout << "GAME ID IS " << currentGame.id << endl;
    lineStream=stringstream(trimStart(lineStream.str(), lineStream.str().find(" ")+1));
    // Turn the stream into a string, find the first space, trim off everything up to and including it
    // Then stick that back into the string stream
    cout << lineStream.str() << endl;
    cout << endl;
  }
  return 0;
}
