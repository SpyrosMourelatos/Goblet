#pragma once

#include <vector>
#include <array>

enum class tile_t {
    harry,draco,wall,goblet,space
};

enum class direction_t{
 left,right,up,down
};
enum class action_t {
    move_up,
    move_down,
    move_left,
    move_right,
    invalid,
    exit
};
using coords= std::array<unsigned,2>;
using map_t = std::vector<std::vector<tile_t>>;
