#pragma once

#include "common.hpp"
#include "draco_t.hpp" 
#include "harry_t.hpp"
#include "goblet_controller.hpp"

#include <curses.h>

class game_engine{
    public:
        game_engine(map_t & map);
        int loop();

    private:
        bool maybe_change_goblet();
        void display();
        void enum_to_char(unsigned j,unsigned i,tile_t t);

        const unsigned green = 1;
        const unsigned black = 2;
        const unsigned yellow = 3;
        const unsigned grey =4;
        map_t& map_;
        draco_t draco;
        harry_t harry;
        coords goblet_location;
        goblet_controller goblet_accessible;

};
