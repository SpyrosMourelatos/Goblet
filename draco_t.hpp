#pragma once 

#include "common.hpp"
#include <bits/stdc++.h>
#include <climits>
#include <vector>
#include <list>
#include <iostream>
#include "ncurses.h"
#include <limits>
#include "person.hpp"

class draco_t:public person{
    public:
    draco_t(map_t& map);
    action_t move() override;
    void calculate_path();
    int get_goblet_total_distance();

    private:
    void backtrack(coords last_point);
    bool test_backtrack(unsigned x, unsigned y,int distance);
    std::list<coords> path;
    int goblet_total_distance;
};
