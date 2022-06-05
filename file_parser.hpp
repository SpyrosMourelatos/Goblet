#pragma once

#include "common.hpp"
#include <fstream>

struct file_parser{
    map_t read(const std::string& f);
    private:
    //this functiontransforms x-> y and y->x because is needed by ncurses...
    map_t reverse_indexes(const map_t & map);
};
