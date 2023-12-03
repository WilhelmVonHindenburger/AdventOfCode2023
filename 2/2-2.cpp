//Advent of Code 2023, Problem 2, Part 2
//By Wilh3lm, released as GPL3
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
ifstream in;

class Token{
  public:
  int tokenType=0;
  /* List of token types:
  0. Empty
  1. Number
  2. Color
  3. Comma
  4. Semicolon
  5. Game
  6. Colon
  7. End of Line
  -1. Invalid */
  string text="";
};

class Draw{
public:
  int red=0;
  int green=0;
  int blue=0;
};

class Game{
public:
  vector<Draw> draws;
  int id=0;
};

int getType(char letter){
  switch(letter){
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
      return 1;
    case 'r':
    case 'g':
    case 'b':
      return 2;
    case ',':
      return 3;
    case ';':
      return 4;
    case 'G':
      return 5;
    case ':':
      return 6;
    case 'E':
      return 7;
    default:
      return -1;
  }
}

vector<Token> tokenize(string text){
  vector<Token> output;
  Token currentToken;
  currentToken.text=text[0];
  currentToken.tokenType=getType(text[0]);
  int currentLetterType=-2; //0 and -1 are taken
  for(int i=1; i<=text.length(); i++){ // Why the fuck does this off by one work
    currentLetterType=-2;
    if(text[i] != ' '){ // Ignore spaces
      currentLetterType=getType(text[i]);
      
      if(currentLetterType == getType(text[i-1])){
        //Same type as previous letter
        currentToken.text += text[i];
      }
      else{
        output.push_back(currentToken);
        currentToken.text=text[i];
        currentToken.tokenType=currentLetterType;
      }
    }
  }
  return output;
}

string replaceAll(string data, string toSearch, string toReplace){
  string output=data;
  int pos=output.find(toSearch);
  while(pos != string::npos){
    output.replace(pos, toSearch.size(), toReplace);
    pos=output.find(toSearch, pos + toReplace.size());
  }
  return output;
}

int main(){
  cout << "Enter file name.\n";
  string filename;
  cin >> filename;
  in.open(filename);
  vector<string> rawText;
  string currentLine="";
  while(getline(in, currentLine)){
    //cout << "Reading line: |" << currentLine << "|\n";
    rawText.push_back(currentLine);
    currentLine="";
  }
  vector<string> modifiedText;
  currentLine="";
  for(int i=0; i<rawText.size(); i++){
    currentLine=rawText[i] + "E";
    currentLine=replaceAll(currentLine, "red", "r");
    currentLine=replaceAll(currentLine, "green", "g");
    currentLine=replaceAll(currentLine, "blue", "b");
    currentLine=replaceAll(currentLine, "Game", "G");
    modifiedText.push_back(currentLine);
    cout << "Reading line: |" << currentLine << "|\n";
  }
  vector<Token> tokenizedLine;
  vector<vector<Token>> tokenizedText;
  for(int i=0; i<modifiedText.size(); i++){
    tokenizedLine=tokenize(modifiedText[i]);
    tokenizedText.push_back(tokenizedLine);
  }
  
  vector<Game> allGames;
  
  int parserState=0;
  /* Parser states:
  0: Looking for game number
  1: Looking for draw number (semicolon -> start new set of draws, stay on state 1)
  2: Looking for draw color
  5: End of line
  
  */
  Game emptyGame;
  Draw emptyDraw; // Use for resetting
  for(int i=0; i<tokenizedText.size(); i++){
  
    //Each line
    parserState=0;
    Game currentGame;
    Draw currentDraw;
    int currentDrawNumber=0;
    for(int j=0; j<tokenizedText[i].size(); j++){
      //cout << "Current token: |" << tokenizedText[i][j].text << "|\n";
      //tokenizedText[i][j] is the j'th token of the i'th line
      if((parserState==0) && (tokenizedText[i][j].tokenType==1)){
        //Game number
        currentGame.id=stoi(tokenizedText[i][j].text);
        cout << "GAME NUMBER " << tokenizedText[i][j].text << endl;
        parserState=1;
      }
      else if((parserState==1) && ((tokenizedText[i][j].tokenType==4) || (tokenizedText[i][j].tokenType==7))){
        //Semicolon or end of line found
        currentGame.draws.push_back(currentDraw);
        cout << "Draw: " << currentDraw.red << " red, " << currentDraw.green << " green, and " << currentDraw.blue << " blue.\n";
        currentDraw=emptyDraw;
        if(tokenizedText[i][j].tokenType==7){
          //Special end of line stuff
          allGames.push_back(currentGame);
          cout << "End of game!\n\n";
          currentGame=emptyGame;
        }
      }
      else if((parserState==1) && (tokenizedText[i][j].tokenType==1)){
        // Draw number found
        currentDrawNumber=stoi(tokenizedText[i][j].text);
        parserState=2;
      }
      else if((parserState==2) && (tokenizedText[i][j].tokenType==2)){
        //Draw color found
        switch(tokenizedText[i][j].text[0]){
          case 'r':
            cout << currentDrawNumber << " red balls\n";
            currentDraw.red=currentDrawNumber;
            break;
          case 'g':
            cout << currentDrawNumber << " green balls\n";
            currentDraw.green=currentDrawNumber;
            break;
          case 'b':
            cout << currentDrawNumber << " blue balls\n";
            currentDraw.blue=currentDrawNumber;
            break;
          default:
            cout << "Congratulations. The program is in an unreachable state. How did you do this?\n";
            return 1;
        }
        parserState=1;
      }
    }
  }
  
  int total=0;
  
  for(int i=0; i<allGames.size(); i++){
    // Loop over each game
    int maxRed=0;
    int maxGreen=0;
    int maxBlue=0;
    for(int j=0; j<allGames[i].draws.size(); j++){
      //Loop over draws in each game
      if(allGames[i].draws[j].red > maxRed) maxRed=allGames[i].draws[j].red;
      if(allGames[i].draws[j].green > maxGreen) maxGreen=allGames[i].draws[j].green;
      if(allGames[i].draws[j].blue > maxBlue) maxBlue=allGames[i].draws[j].blue;
    }
    cout << "Game " << allGames[i].id << " requires " << maxRed << " red, " << maxGreen << " green, and " << maxBlue << " blue.\n";
    total += (maxRed*maxGreen*maxBlue);
  }
  
  cout << "Total: " << total << endl;
  return 0;
}
