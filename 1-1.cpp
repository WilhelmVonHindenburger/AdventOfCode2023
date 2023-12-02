//Advent of Code 2023, Problem 1, Part 1
//By Wilh3lm, released as GPL3
#include <iostream>
#include <fstream>
using namespace std;

ifstream in;

int main(){
  string infile;
  cout << "Enter file name for data\n";
  cin >> infile;
  in.open(infile);
  string currentLine;
  int firstint, lastint;
  int total=0;
  while(!in.eof()){
    getline(in, currentLine);
    firstint=-1;
    lastint=-1;
    cout << currentLine << endl;
    for(int i=0; i<currentLine.length(); i++){
      if((currentLine[i] >= '0') && (currentLine[i] <= '9')) lastint=(currentLine[i]-48); // Ascii values: 0x30 through 0x39 = 48 through 57
      if((lastint != -1) && (firstint == -1)) firstint = lastint;
      // The first time we get an integer, the last integer seen is set, then since the first one has not been set it gets set, but doesn't get changed after that
    }
    cout << "First int: " << firstint << "\nlast int: " << lastint << "\n\n";
    if(firstint != -1) total += ((10*firstint)+lastint);
    //Skip lines without any integers
  }
  cout << total << endl;
  return 0;
}
