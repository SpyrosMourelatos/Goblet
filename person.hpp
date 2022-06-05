#pragma once

#include "common.hpp"
#include <list>

class person{
    public:
    person(map_t& m,tile_t t);
    virtual action_t move()=0; //This means pure virtual important
    void update_goblet(coords);
    void update_self(coords);
    void set_location(coords);
    void set_goblet(coords);
    protected: 
    int calculate_goblet_distance();
    action_t move_from_to(coords from,coords to);
    tile_t self_symbol;
    void find_distances();
    bool test_coord(unsigned x,unsigned y,int distance);
    map_t& map;
    std::vector<std::vector<int>> initial_distances_map;
    coords goblet_location;
    coords location;
    std::list<coords> visited;
};
