#pragma once

#include "common.hpp"
#include "draco_t.hpp" 
#include "harry_t.hpp"

#include <curses.h>

//#define KEY_UP 72
//#define KEY_DOWN 80
//#define KEY_LEFT 75
//#define KEY_RIGHT 77
class game_engine{
    public:
        game_engine(map_t & map)
            :draco{map},
            harry{map},
            map_{map}
        {}
        void loop(){
            display();
            while(true){
                if (auto act=harry.move(map_); act!= action_t::invalid){
                    if (act == action_t::exit)
                        return;
                    else if(act == action_t::reached_goblet)
                    {
                        win();
                        return;
                    }
                    //current_harry_location 
//                    if (auto next_draco_location = draco.next_move();
//                            next_draco_location== harry.get_current_location())
//                    {
//                        prev_draco_location=next_draco_location;
//                        draco.pause_to_avoid_harry();
//                    }
//                    else{
//                        map_[prev_draco_location[0]][prev_draco_location[1]]=tile_t::space;
//                        map_[next_draco_location[0]][next_draco_location[1]]=tile_t::draco;
//                    }
//                    if(maybe_change_goblet()){
//                        draco.update_path(current_goblet_location) ;
//                    }
                    display();
                }
            }

        }
    private:
        void win(){
            //TODO
            debug("WIN");
        }
        bool maybe_change_goblet(){
            //TODO 
            return false;
        };
        void display(){
            unsigned i=0;
            for (auto& line: map_){
                unsigned j=0;
                for(auto symbol:line){
                    mvaddch(i,j,static_cast<char>(symbol));
                    j++;
                }
                i++;
            }
        };
        map_t map_;
        draco_t draco;
        harry_t harry;
        coords current_goblet_location;
        coords prev_draco_location;

};
