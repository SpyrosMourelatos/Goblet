#pragma once 

#include "common.hpp"
#include <vector>
#include <list>
#include <limits>

// This class knows all the accesible element from the initial gobletlocation
// It is usefull to add new elements (like harry draco or update the goblet)
// on accessible spaces
class goblet_controller {
    public:
        goblet_controller(map_t& map)
            :map_(map){
                auto cols= map_.size();
                auto rows= map_[0].size();
                unsigned x=rand()%cols;
                unsigned y=rand()%rows;
                while( map_[x][y] != tile_t::space)
                {
                    x=rand()%cols;
                    y=rand()%rows;
                }
                location=coords{x,y};
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
                initial_distances_map[location[0]][location[1]] = 0;
                visited.push_back(location);
                all_possible_locations.push_back(location);
                find_accessible_elements();
            }

        coords add_entity_on_map(tile_t t){
            unsigned index=rand()%all_possible_locations.size();
            auto x= all_possible_locations[index][0];
            auto y= all_possible_locations[index][1];
            while( map_[x][y] != tile_t::space)
            {
                unsigned index=rand()%all_possible_locations.size();
                auto x= all_possible_locations[index][0];
                auto y= all_possible_locations[index][1];
            }
            if(t==tile_t::goblet)
                location=coords{x,y};
            return coords{x,y};
        }
        coords get_location(){
            return location;
        };
    private:
        void find_accessible_elements(){
            if(visited.empty()){
                return ;
            }
            auto test_path = visited.front();
            all_possible_locations.push_back(test_path);
            visited.pop_front();
            auto x  = test_path[0];
            auto y  = test_path[1];
            test_coord(x+1,y);
            test_coord(x-1,y);
            test_coord(x,y+1);
            test_coord(x,y-1);
            find_accessible_elements();
        }
        void test_coord(unsigned x, unsigned y){
            if(initial_distances_map[x][y] == std::numeric_limits<int>::max())
            {
                visited.push_back(coords{x,y});
                initial_distances_map[x][y] = +1;
            }
        }
        map_t& map_;
        coords location;
        std::list<coords> visited;
        std::vector<coords> all_possible_locations;
        std::vector<std::vector<int>> initial_distances_map;
};
