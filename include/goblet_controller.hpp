#pragma once 

#include "common.hpp"
#include <vector>
#include <list>
#include <limits> //for intmax
#include <ctime>//for true random seed

// This class knows all the accesible elements from the initial gobletlocation
// It is usefull to add new elements (like harry draco or update the goblet)
// on accessible spaces
class goblet_controller {
    public:
        goblet_controller(map_t& map);
        coords add_entity_on_map(tile_t t);
        coords get_location();
    private:
        void find_accessible_elements();
        void test_coord(unsigned x, unsigned y);
        map_t& map_;
        coords location;
        std::list<coords> visited;
        std::vector<coords> all_possible_locations;
        std::vector<std::vector<int>> initial_distances_map;
};
