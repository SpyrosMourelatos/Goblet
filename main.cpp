//
//    initscr(); 
//    cbreak(); //disable buffering
//    noecho(); //dont retype
//    keypad(stdscr, TRUE); //allow special chars like arrows
//    WINDOW * win = newwin(5, 5, 5, 5); 
#include <curses.h>
#include <iostream>
#define LEN 18
#define TRUE 1
#define FALSE 0
#define UP 3
#define DOWN 2
#define RIGHT 5
#define LEFT 4

#include "file_parser.hpp"
#include "game_engine.hpp"

// A simple program that allows a cursor to be moved around the screen.
void dispMap(int x, 
             int y, 
             char map[][LEN]){
  int row,col;
  // draw basic map
  for(row=0;row<LEN;row++){
    for(col=0;col<LEN;col++){
      mvaddch(row+1,col+1,map[row][col]);
    }
  }
  // cursor symbol
  mvaddch(y+1,x+1,'#');
}
     
int main(int argc ,char** argv){
    if (argc != 2) {
        std::cerr<<"Not correct ammount of arguments"<<argc <<std::endl;
        exit(1);
    }
    file_parser parser{};
    auto map = parser.read(argv[1]);
    game_engine game(map);
    game.loop();
        
//
//     char map[][LEN]={" --------------- ", // empty space to fill array to length of LEN
//                      "|               |",
//                      "|               |",
//                      "|               |",
//                      "|               |",
//                      "|               |",
//                      "|               |",
//                      "|               |",
//                      "|               |",
//                      "|               |",
//                      "|               |",
//                      "|               |",
//                      "|               |",
//                      "|               |",
//                      "|               |",
//                      "|               |",
//                      " --------------- ",    
//  };
//  
//  // activate the keypad to read from this terminal
//  keypad(initscr(),TRUE);
//  //don't show cursor
//  curs_set(0);
//
//
//  // initialise the x and y positions of the cursor
//  int xPos=1;
//  int yPos=1;
//  int p = 1;
//  char c='\0';       // input character initialise to null
//  
//  while( c!='q'){
//    dispMap(xPos,yPos,map);
//    // read a single character
//    c=getch();
//    mvaddch(yPos,xPos,'#');        // erase old position
//    // move according to cursor
// 
//    switch(c){
//    case UP:
//      if (map[yPos-1][xPos]== ' '){
//        yPos--;
//      }
//      break;
//    case DOWN:
//      if (map[yPos+1][xPos]== ' '){
//        yPos++;
//      }
//      break;
//    case LEFT:
//      if (map[yPos][xPos-1]== ' '){
//        xPos--;
//      }
//      break;
//    case RIGHT:
//      if (map[yPos][xPos+1]== ' '){
//        xPos++;
//      }
//    }
//  }
//  endwin();
}
