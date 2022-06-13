#pragma once

#include "common.hpp"
#include <list>

class person{
    public:
    person(map_t& m,tile_t t);
    void set_location(coords);
    void set_goblet(coords);
    protected: 

    int calculate_goblet_distance(); 
    action_t move_from_to(coords from,coords to);
    void find_distances();
    bool test_coord(unsigned x,unsigned y,int distance);
    tile_t self_symbol;
    map_t& map;
    coords goblet_location;
    coords location;
    std::vector<std::vector<int>> initial_distances_map;
    std::list<coords> visited;
};
