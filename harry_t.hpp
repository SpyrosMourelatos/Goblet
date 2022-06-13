#pragma once

#include "common.hpp"
#include "curses.h"
#include "person.hpp"

class harry_t :public person{
    public:
    harry_t(map_t& map);
    action_t move() ;
    coords get_location();
};
