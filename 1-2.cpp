//Advent of Code 2023, Problem 1, Part 2
//By Wilh3lm, released as GPL3
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream in;

string replace(string input, string toSearch, string toReplace){
  string data=input;
  int pos=data.find(toSearch);
  while(pos != string::npos){
    data.replace(pos, toSearch.size(), toReplace);
    pos=data.find(toSearch, pos + toReplace.size());
  }
  return data;
}

int main(){
  string infile;
  cout << "Enter file name for data\n";
  cin >> infile;
  in.open(infile);
  string currentLine;
  string modifiedLine;
  int firstint, lastint;
  int total=0;
  while(!in.eof()){
    getline(in, currentLine);
    firstint=-1;
    lastint=-1;
    cout << currentLine << endl;
    currentLine += "=";
    for(int i=0; i<currentLine.length(); i++){
      //Loop over each character in current line
      if((currentLine.find("one",i)==i)||(currentLine[i]=='1')){
        //One found at this location
        lastint=1;
      }
      if((currentLine.find("two",i)==i)||(currentLine[i]=='2')){
        //Two found at this location
        lastint=2;
      }
      if((currentLine.find("three",i)==i)||(currentLine[i]=='3')){
        //Three found at this location
        lastint=3;
      }
      if((currentLine.find("four",i)==i)||(currentLine[i]=='4')){
        //Four found at this location
        lastint=4;
      }
      if((currentLine.find("five",i)==i)||(currentLine[i]=='5')){
        //Zero found at this location
        lastint=5;
      }
      if((currentLine.find("six",i)==i)||(currentLine[i]=='6')){
        //Zero found at this location
        lastint=6;
      }
      if((currentLine.find("seven",i)==i)||(currentLine[i]=='7')){
        //Zero found at this location
        lastint=7;
      }
      if((currentLine.find("eight",i)==i)||(currentLine[i]=='8')){
        //Eight found at this location
        lastint=8;
      }
      if((currentLine.find("nine",i)==i)||(currentLine[i]=='9')){
        //Nine found at this location
        lastint=9;
      }
      if(firstint==-1)firstint=lastint;
    }
    cout << "First int: " << firstint << " last int: " << lastint << endl;
    if(firstint!=-1)total += ((10*firstint)+lastint);
    cout << "Total: " << total << "\n\n";
  }
  cout << total << endl;
  return 0;
}
