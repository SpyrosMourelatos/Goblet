#include <curses.h>
#include <iostream>

#include "file_parser.hpp"
#include "game_engine.hpp"
     
int main(int argc ,char** argv){
    if (argc != 2) {
        std::cerr<<"Not correct ammount of arguments"<<argc <<std::endl;
        exit(1);
    }
    file_parser parser{};
    keypad(initscr(),true);// activate the keypad 
    curs_set(false);//don't show cursor
    auto map = parser.read(argv[1]); //read the file
    game_engine game{map}; //initialize game
    game.loop();           //run the loop
    endwin();
}
