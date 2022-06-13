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

// the keyword class makes the enumerator scoped
//  you can not use the words freely eg:"move" 
//  but you have to use the scoped alternative "action_t::move"
enum class action_t {
    move,
    reached_goblet,
    stay,
    invalid,
    exit
};
using coords= std::array<unsigned,2>;
using map_t = std::vector<std::vector<tile_t>>;


