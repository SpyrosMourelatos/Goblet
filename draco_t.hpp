#pragma once 

#include "common.hpp"
#include <bits/stdc++.h>
#include <vector>
#include <list>
#include <iostream>
#include "ncurses.h"

class draco_t{
    public:
    draco_t(const map_t& map){
        draco_position =  find(map,tile_t::draco);
        goblet_position =  find(map,tile_t::goblet);
        //calculate_path(map);
    };
    void update_path(coords goblet_new_coords){
        //TODO
    };
    coords next_move(){
        //TODO
        auto ret = path.back();
        path.pop_back();
        return ret;
    };
    void pause_to_avoid_harry(){
        //TODO
    };
    private:


    void calculate_path(const  map_t& map){
        //The first for initializes the 2d array
        for (auto& line :map){
            std::vector<int> temp_secret_line{};
            for(auto i:line){
                if( i==tile_t::wall)
                    temp_secret_line.push_back(-1);
                else 
                    temp_secret_line.push_back(INT_MAX);
            }
            secret_map.push_back(temp_secret_line);
        }
        secret_map[goblet_position[0]][goblet_position[1]] = -2 ;   //initialize goblet
        secret_map[draco_position[0]][draco_position[1]] = 0;
        visited.push_back(draco_position);
        colorize();
        backtrack(goblet_position);
        
    };
    void backtrack(coords last_point){
        path.push_back(last_point);
        auto x= last_point[0];
        auto y= last_point[1];
        debug("last point");
        debug(x);
        debug(y);
        auto distance =secret_map[x][y];
        if (distance == 0)
            return;
        if(test_backtrack(x-1,y,distance))
            backtrack(coords{x-1,y});
        else if(test_backtrack(x+1,y,distance))
            backtrack(coords{x+1,y});
        else if(test_backtrack(x,y+1,distance))
            backtrack(coords{x,y+1});
        else //if(test_backtrack(x,y-1,distance))
            backtrack(coords{x,y-1});
    }
    bool test_backtrack(unsigned x, unsigned y,int distance){
        if( secret_map[x][y] == distance-1)
            return true;
        return false;
    }
    void colorize(){
        if(visited.empty()){
            debug("There is no way out!");
            exit(1);
        }
        auto test_path = visited.front();
        auto x  = test_path[0];
        auto y  = test_path[1];
        visited.pop_front();
        if(test_coord(x+1,y)) return ;
        if(test_coord(x-1,y)) return ;
        if(test_coord(x,y+1)) return ;
        if(test_coord(x,y-1)) return ;
        colorize();
    }
    bool test_coord(unsigned x,unsigned y){
        auto distance = secret_map[x][y];
        if( secret_map[x][y] == -2)
        {
            visited.push_back(coords{x,y});
            secret_map[x][y] = distance + 1;
            return true;
        }
        else if(secret_map[x][y] == INT_MAX)
        {
            visited.push_back(coords{x,y});
            secret_map[x][y] = distance + 1;
        }
        //there are two more cases if xy==something it means we already reached this point
        //if xy==-1 it means it's a wall
        //we don't do nothing on both cases
        return false;
    
    }
    std::vector<std::vector<int>> secret_map;
    coords draco_position{};
    coords goblet_position{};
    std::list<coords> visited;
    std::list<coords> path;
};
