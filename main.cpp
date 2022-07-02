#include <iostream>
#include<queue>
using namespace std;

bool isGameOver = false;
#define row 6
#define coloum 7

class Player {
   private:
      string name;
      string mark;

   public:
     Player(string name, string mark) {
       this->name = name;
       this->mark = mark;
     }

     string getName() {
       return name;
     }

     string getMark(){
       return mark;
     }
};

class GameRule {
  public:
    GameRule() {
      printGameTitle();
      gameRule();
      howToPlay();
    }

    void printGameTitle() {
      for(int i = 0; i < 40; i++) {
        cout<<"*";
      }
      cout<<endl;
      cout<<"*                                      *"<<endl;
      cout<<"*         WELCOME TO CONNECT-4         *"<<endl;
      cout<<"*                                      *"<<endl;
      for(int i = 0; i < 40; i++) {
        cout<<"*";
      }
      cout<<endl;
    }

    void gameRule() {
      cout<<endl<<endl<<endl<<endl;
      cout<<"Rules : "<<endl;
      cout<<"1. Board size is 6-Rows and 7-Coloum. "<<endl;
      cout<<"2. It's two player game (Red and Yellow)." <<endl;
      cout<<"3. A player is win if He/She able to connect 4 dots Horizontally or Vertically or Diagonally."<<endl;
      cout<<"4. Game will draw When the board is Full."<<endl;
      
    }

    void howToPlay() {
      cout<<endl<<endl<<endl<<endl;
      cout<<"How to Play : "<<endl;
      cout<<"1. Game always start with Player-1 Red."<<endl;
      cout<<"2. In each step choose the coloum number in which you want the ball."<<endl;
      cout<<"3. Rows will be filled from bottom to top."<<endl;
    }
};


class Connect4 {
  private:
    int count = 0;
    int winPoint = 4;
    string emptySpace = "|_|";
    string board[row][coloum];

  public:
    Connect4() {
      initializeEmptyBoard();
    }

    void initializeEmptyBoard() {
      for(int i = 0; i < row; i++) {
        for(int j = 0; j < coloum; j++) {
          board[i][j] = emptySpace;
        }
      }
    }

    void insertData (int i, int j, string playerMark) {
      board[i][j] = playerMark;
    }

    int getEmptyRowPos(int j) {
      if(j >= coloum || j < 0) {
        return -1;
      } 
      int i = row-1;
      while( i != -1) {
        if(board[i][j] == emptySpace) {
          return i;
        }
        i--;
      }
      return -1;
    }

    bool isVerticallyConnect(int I, int J, string playerMark) {
      int i = I;
      int j = J;
      
      while(board[i][j] == playerMark && i <= row-1) {
        count++;
        i++;
      }
      if(count == winPoint) {
        count = 0;
        return true;
      }
      count = 0;
      return false;
    }

    bool isHorizontallyConnect(int I, int J, string playerMark) {
      int i = I;
      int j = J;
      while(board[i][j] == playerMark && j >= 0) {
        count++;
        j--;
      }
      j = J+1;
      while(board[i][j] == playerMark && j <= coloum-1) {
        count++;
        j++;
      }
      if(count == winPoint) {
        count = 0;
        return true;
      }
      count = 0;
      return false;
    }

    bool isRightDiagonallyConnect(int I, int J, string player) {
      int i = I;
      int j = J;
      while(board[i][j] == player && i >= 0 && j <= coloum-1) {
        count++;
        i--;
        j++;
      }
      i = I+1;
      j = J-1;
      while(board[i][j] == player && i <= row-1 && j >= 0) {
        count++;
        i++;
        j--;
      }
      if(count == winPoint) {
        count = 0;
        return true;
      }
      count = 0;
      return false;
    }

    bool isLeftDiagonallyConect(int I, int J, string player) {
      int i = I;
      int j = J;
      while(board[i][j] == player && i >= 0 && j >= 0) {
        count++;
        i--;
        j--;
      }
      i = I+1;
      j = J+1;
      while(board[i][j] == player && i <= row-1 && j <= coloum-1) {
        count++;
        i++;
        j++;
      }
      if(count == winPoint) {
        count = 0;
        return true;
      }
      count = 0;
      return false;
    }

    bool isEmpty() {
      for(int i = 0; i < row; i++) {
        for(int j = 0; j < coloum; j++) {
          if(board[i][j] == emptySpace) {
            return true;
          }
        }
      }
      return false;
    }
      
    void print() {
       cout<<endl;
       for(int i = 0; i < row; i++) {
        for(int j = 0; j < coloum; j++) {
          cout<< board[i][j] ;
        }
        cout<<endl;
      }
      cout<<endl;
    }
};

 void gameStatusLogo(string status) {
    for(int i = 0; i < 30; i++) {
      cout<<"_";
    }
    cout<<endl;
    cout<<"|                            |"<<endl;
    cout<<"|        "<<status<<"          |"<<endl;
    cout<<"|                            |"<<endl;
    for(int i = 0; i < 30; i++) {
      cout<<"-";
    }
    cout<<endl;
}


  void gamePlay(string playerName, string playerMark, Connect4 &play) {
      int j;
      cout<<"Enter colum Number (1 to 7) : ";
      cin>> j;
  
      int i = play.getEmptyRowPos(--j);
    
      if( i < 0) {
        cout<<"\nCan't insert. Coloum FULL / Out of range "<< endl;
      } else {
          play.insertData(i,j,playerMark);
          play.print();
          if(play.isVerticallyConnect(i,j,playerMark) || 
             play.isHorizontallyConnect(i,j,playerMark) ||
             play.isRightDiagonallyConnect(i, j,playerMark) ||
             play.isLeftDiagonallyConect(i, j,playerMark)) {
                gameStatusLogo(playerName + "    WON");
                isGameOver = true;
          }
      }
  }

void play() {
  Player red("Red","|R|");
  Player yellow("Yellow","|Y|");
  Connect4 play;
  
  bool flag = true;
 
  while(!isGameOver) {
    if(!play.isEmpty()) {
      cout<<"Board is Full. Game Draw "<<endl;
      return ;
    }
    
    if(flag) {
      cout<<"\nPlayer-1 : "<< red.getName() <<" playing" <<endl;
      gamePlay(red.getName(), red.getMark(),play);
    } else {
      cout<<"\nPlayer-2 : "<< yellow.getName() <<" playing"<<endl;
      gamePlay(yellow.getName(), yellow.getMark(),play);
    }
     flag = !flag;
  }
}


int main () { 
  GameRule rule;
  char input;
  cout<<endl<<endl;
  
  cout<<"Press 'Y/y' to play OR any Key to close : ";
  cin>> input;

  if(input == 'Y' || input == 'y') {
    gameStatusLogo("GAME START");
    play();
  }

  gameStatusLogo(" GAME END ");
  return 0;
}