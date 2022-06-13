#include "draco_t.hpp"

draco_t::draco_t(map_t& map)
    :person(map,tile_t::draco)
{};

action_t draco_t::move(){
    auto next_coords = path.back();
    auto ret = move_from_to(location, next_coords);
    if (ret != action_t::invalid){
        path.pop_back();
        location =  next_coords;
    }
    return ret;
}

void draco_t::calculate_path(){
    goblet_total_distance = calculate_goblet_distance();
    backtrack(goblet_location);
}

int draco_t::get_goblet_total_distance(){
    return goblet_total_distance;
}

void draco_t::backtrack(coords last_point){
    auto x= last_point[0];
    auto y= last_point[1];
    auto distance =initial_distances_map[x][y];
    if (distance == 0)
        return;
    path.push_back(last_point);
    if(test_backtrack(x-1,y,distance))
        backtrack(coords{x-1,y});
    else if(test_backtrack(x+1,y,distance))
        backtrack(coords{x+1,y});
    else if(test_backtrack(x,y+1,distance))
        backtrack(coords{x,y+1});
    else //if(test_backtrack(x,y-1,distance))
        backtrack(coords{x,y-1});
}
bool draco_t::test_backtrack(unsigned x, unsigned y,int distance){
    if( initial_distances_map[x][y] == distance-1)
        return true;
    return false;
}
