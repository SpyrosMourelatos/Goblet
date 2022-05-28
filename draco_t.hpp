#pragma once 

#include "common.hpp"
#include <vector>
#include <iostream>

class draco_t{
    public:
    using path_t = std::vector<coords>;
    draco_t(const map_t& map){
        draco_position =  find(map,tile_t::draco);
        goblet_position =  find(map,tile_t::goblet);
        calculate_path(map);
    };
    void update_path(coords goblet_new_coords){
        //TODO
    };
    coords next_move(){
        //TODO
        return coords{0,0};
    };
    void pause_to_avoid_harry(){
        //TODO
    };
    private:

    coords find(const map_t& map,tile_t type){
        unsigned x{};
        unsigned y={};
        for (auto& line :map){
            for(auto i:line){
                if (i==type)
                    return coords{x,y};
                x++;
            }
            y++;
        }
        std::cerr<<"Draco not in map!"<<std::endl;
        return coords{unsigned(-1),unsigned(-1)};
    }

    void calculate_path(const  map_t& map){
        //The first for initializes the 2d array
        unsigned x{};
        unsigned y={};
        for (auto& line :map){
            std::vector<int> temp_secret_line{};
            for(auto i:line){
                if( i==tile_t::wall)
                    temp_secret_line.push_back(-1);
                else 
                    temp_secret_line.push_back(0);
            }
            secret_map.push_back(temp_secret_line);
        }
        secret_map[goblet_position[0]][goblet_position[1]] = -2 ;   //initialize goblet
        paths_list.push_back(path_t{draco_position});
        colorize(paths_list);
        
    };
    void colorize(std::vector<path_t>& paths){

    }
    std::vector<std::vector<int>> secret_map;
    coords draco_position{};
    coords goblet_position{};

    std::vector<path_t> paths_list;


};
