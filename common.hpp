#pragma once

#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

enum class tile_t:char {
    harry='h',
    draco='d',
    wall='w',
    goblet='G',
    space='s'
};

enum class direction_t{
    left,right,up,down
};
enum class action_t {
    move_up,
    move_down,
    move_left,
    move_right,
    reached_goblet,
    invalid,
    exit
};
using coords= std::array<unsigned,2>;
using map_t = std::vector<std::vector<tile_t>>;

template <class T>
static inline void debug(T s){
    std::ofstream f;
    f.open("outputs.txt", std::ios_base::app);
    f<<s;
    //f<<"\n";
}

static inline coords find(const map_t& map,tile_t type){
    unsigned x{};
    for (auto& line :map){
        unsigned y={};
        for(auto i:line){
            if (i==type){
                debug("Location of");
                debug(char(type));
                debug(x);
                debug(y);
                return coords{x,y};
            }
            y++;
        }
        x++;
    }
    std::cerr<<"Draco not in map!"<<std::endl;
    return coords{unsigned(-1),unsigned(-1)};
}
