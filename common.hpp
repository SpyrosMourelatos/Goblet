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
}

