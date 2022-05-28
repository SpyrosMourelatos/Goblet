#pragma once

#include "common.hpp"
#include "draco_t.hpp" 
#include "harry_t.hpp"

class game_engine{
    public:
    game_engine(map_t & map)
    :draco{map},
     map_{map}
    { }
    void loop(){
        while(true){
        if (auto act=harry.move(map_); act!= action_t::invalid){
            //current_harry_location 
            if (draco.next_move() == current_harry_location)
               draco.pause_to_avoid_harry();
            if(maybe_change_goblet()){
               draco.update_path(current_goblet_location) ;
            }
            display();

        }
        }

    }
    private:
    bool maybe_change_goblet(){
        //TODO 
        return false;
    };
    void display(){
        //TODO
    };
    map_t map_;
    draco_t draco;
    harry_t harry;
    coords current_goblet_location;
    coords current_harry_location={};

};
