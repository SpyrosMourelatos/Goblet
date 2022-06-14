#include <curses.h>
#include <iostream>

#include "file_parser.hpp"
#include "game_engine.hpp"
     
int main(int argc ,char** argv){
    if (argc != 2) {
        std::cerr<<"Not correct ammount of arguments "<<argc <<std::endl;
        exit(1);
    }

    file_parser parser{};
    auto map = parser.read(argv[1]); //read the file
    keypad(initscr(),true);// activate the keypad 
    start_color();  //activate colors
    curs_set(false);//don't show cursor
    game_engine game{map}; //initialize game
    int game_result = game.loop();           //run the loop
    endwin();              //close curses elegantly
    if (game_result==-1)
        std::cout<<"Exited"<<std::endl;
    else if(game_result==0)
        std::cout<<"Lost :("<<std::endl;
    else if(game_result==1)
        std::cout<<"WON!!"<<std::endl;
}
