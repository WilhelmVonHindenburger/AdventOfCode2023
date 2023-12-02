#Advent of Code 2023, Problem 2, Part 1, Attempt 2 (UNSUCCESSFUL)
#By Wilh3lm, released as GPL3
from dataclasses import dataclass

types=["EMPTY", "number", "color", "comma", "semicolon", "game", "colon", "INVALID"]
# Empty: 0
# Number: 1
# Color: 2
# Comma: 3
# Semicolon: 4
# Game: 5
# Colon: 6
# Invalid: 7

@dataclass
class Token:
  tokenType: str = types[0]
  text: str = ""

@dataclass
class TokenizedText:
  tokens: list[Token] # NO DEFAULT CONSTRUCTOR

numbers="0123456789"
colors="rgb"

def getType(letter):
  if letter in numbers: return types[1]
  elif letter in colors: return types[2]
  elif letter == ",": return types[3]
  elif letter == ";": return types[4]
  elif letter == "A": return types[5]
  elif letter == ":": return types[6]
  else : return types[6]

def tokenize(text):
  output=TokenizedText([])
  currentToken=Token()
  for i in range(0, len(text)):
    letter=text[i]
    if(letter != " "): # SKIP SPACES
      currentLetterType=getType(letter)
    if(i==0): # Special case for text-initial
      currentToken.tokenType=currentLetterType
      currentToken.text += letter
    elif(currentLetterType==getType(text[i-1])): # Same letter type as previous
      currentToken.text += letter
    else:
      output.tokens.append(Token(currentToken.tokenType, currentToken.text))
      currentToken.tokenType=currentLetterType
      currentToken.text=letter
  output.tokens.append(currentToken)
  return output

filename=input("File name?\n")
openedFile=open(filename)
fileText=openedFile.read()
fileText=fileText.replace("Game","A")
fileText=fileText.replace("red","r")
fileText=fileText.replace("green","g")
fileText=fileText.replace("blue","b")
tokenizedText=tokenize(fileText)
for token in tokenizedText.tokens:
  if(token.tokenType==types[7]):
    tokenizedText.tokens.remove(token)
  token.text=token.text.strip()

@dataclass
class Draw:
  red: int = 0
  green: int = 0
  blue: int = 0

@dataclass
class Game:
  draws: list = Draw([])
  gameId: int=-1

data=[]

mode=0
# 0=none
# 1=Searching for game ID
# 2=Start new draw
# 3=Searching for draw number
# 4=Searching for draw color

# 0+"A"->1
# 1+number->
currentDrawNumber=0
currentGame = Game()
currentGame.draws=[] # It won't let me initialize as an empty list?
currentDraw = Draw()

for token in tokenizedText.tokens:
  print("Token: `" + token.text + "`")
  if(token.tokenType==types[5]): #start of game
    mode=1
    data.append(currentGame)
    currentDrawNumber=0
    currentGame=Game()
  elif(mode==1) and (token.tokenType==types[1]):
    # Game ID
    currentGame.gameId=int(token.text)
    print("Game number: " + str(currentGame.gameId))
    mode=3
  elif(mode==3) and (token.tokenType==types[4]):
    # Semicolon separates draws
    currentGame.draws.append(currentDraw)
    mode=3
  elif(mode==3) and (token.tokenType==types[1]):
    # Number in a draw
    currentDrawNumber=int(token.text)
    print("Draw number: " + str(currentDrawNumber))
    mode=4
  elif(mode==4) and (token.tokenType==types[2]):
    # Draw color
    if(token.text=="r"):
      currentDraw.red=currentDrawNumber
    elif token.text=="g":
      currentDraw.green=currentDrawNumber
    elif token.text=="b":
      currentDraw.blue=currentDrawNumber
    print("Draw color: " + token.text)
    mode=3
