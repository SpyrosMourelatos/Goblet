#include "person.hpp"

#include <climits>
#include <bits/stdc++.h>

void person::set_location(coords xy){
    location=xy;
}
void person::set_goblet(coords xy){
    goblet_location=xy;
}
person::person(map_t& m,tile_t t)
    : map{m},self_symbol{t}
{}

void person::update_goblet(coords xy){
    goblet_location = xy;
}
void person::update_self(coords xy){
    location=xy;
}

int person::calculate_goblet_distance(){
    //The first for initializes the 2d array
    initial_distances_map={};
    visited={};
    for (auto& line :map){
        std::vector<int> temp_secret_line{};
        for(auto i:line){
            if( i==tile_t::wall)
                temp_secret_line.push_back(-1);
            else 
                temp_secret_line.push_back(std::numeric_limits<int>::max());
        }
        initial_distances_map.push_back(temp_secret_line);
    }
    initial_distances_map[goblet_location[0]][goblet_location[1]] = -2 ;   //initialize goblet
    initial_distances_map[location[0]][location[1]] = 0;
    visited.push_back(location);
    find_distances();
    return initial_distances_map[goblet_location[0]][goblet_location[1]];
}

void person::find_distances(){
    if(visited.empty()){
        debug("There is no way out!");
        return ;
    }
    auto test_path = visited.front();
    auto x  = test_path[0];
    auto y  = test_path[1];
    auto distance = initial_distances_map[x][y];
    visited.pop_front();
    if(test_coord(x+1,y,distance)) return ;
    if(test_coord(x-1,y,distance)) return ;
    if(test_coord(x,y+1,distance)) return ;
    if(test_coord(x,y-1,distance)) return ;
    find_distances();
}
bool person::test_coord(unsigned x,unsigned y,int distance){
    if( initial_distances_map[x][y] == -2)
    {
        initial_distances_map[x][y]=distance+1;
        visited.push_back(coords{x,y});
        return true;
    }
    else if(initial_distances_map[x][y] == std::numeric_limits<int>::max())
    {
        visited.push_back(coords{x,y});
        initial_distances_map[x][y] = distance + 1;
    }
    //there are two more cases if xy==something it means we already reached this point
    //if xy==-1 it means it's a wall
    //we don't do nothing on both cases
    return false;
}
action_t person::move_from_to(coords from,coords to){
    auto x = from[0];
    auto y = from[1];
    auto x_new = to[0];
    auto y_new = to[1];
    auto new_tile = map[x_new][y_new];
    if ( new_tile == tile_t::space){
        location = to;
        map[x][y] = tile_t::space;
        map[x_new][y_new] = self_symbol;
        return action_t::move;
    }
    else if (new_tile == tile_t::goblet){
        map[x][y] = tile_t::space;
        map[x_new][y_new] = self_symbol;
        return action_t::reached_goblet;
    }
    else 
        return action_t::invalid;

}
