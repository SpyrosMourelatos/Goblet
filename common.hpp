#pragma once

#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

enum class tile_t {
    harry,
    draco,
    wall,
    goblet,
    space
};

enum class action_t {
    move,
    reached_goblet,
    stay,
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
                return coords{x,y};
            }
            y++;
        }
        x++;
    }
    std::cerr<<"Someone not in map!"<<std::endl;
    return coords{unsigned(-1),unsigned(-1)};
}
