#pragma once

#include "common.hpp"
#include "curses.h"

class harry_t {
    public:
    harry_t(const map_t& map){
        current_harry_location =  find(map,tile_t::harry);
    }
    action_t move(map_t& map){
        unsigned char  c=getch();
        auto x=current_harry_location[0];
        auto y=current_harry_location[1];
        debug((int)c);
        switch(c){
        case 4://UP
          if (auto f=map[x][y-1]; f== tile_t::space){
                current_harry_location = {x,y-1};
                map[x][y] = tile_t::space;
                map[x][y-1] = tile_t::harry;
                return action_t::move_up;
          }
          else if (f == tile_t::goblet){
            map[x][y] = tile_t::space;
            map[x][y-1] = tile_t::harry;
            return action_t::reached_goblet;
          }
          break;
        case 5://DOWN
          if (auto f=map[x][y+1]; f== tile_t::space){
                current_harry_location = {x,y+1};
                map[x][y] = tile_t::space;
                map[x][y+1] = tile_t::harry;
                return action_t::move_down;
          }
          else if (f == tile_t::goblet){
            map[x][y] = tile_t::space;
            map[x][y+1] = tile_t::harry;
            return action_t::reached_goblet;
          }
          break;
        case 3: //left
          if (auto f=map[x-1][y]; f== tile_t::space){
                current_harry_location = {x-1,y};
                map[x][y] = tile_t::space;
                map[x-1][y] = tile_t::harry;
                return action_t::move_left;
          }
          else if (f == tile_t::goblet){
            map[x][y] = tile_t::space;
            map[x-1][y] = tile_t::harry;
            return action_t::reached_goblet;
          }
          break;
        case 2://right
          if (auto f=map[x+1][y]; f== tile_t::space){
                map[x][y] = tile_t::space;
                map[x+1][y] = tile_t::harry;
                current_harry_location = {x+1,y};
                return action_t::move_right;
          }
          else if (f == tile_t::goblet){
            map[x][y] = tile_t::space;
            map[x+1][y] = tile_t::harry;
            return action_t::reached_goblet;
          }
          break;
        case 27:
          return action_t::exit;
          break;
        default:
          return action_t::invalid;
        }
            return action_t::invalid;
    };

    coords get_current_location(){
        return current_harry_location;
    }
    private:
    coords current_harry_location={};


};
