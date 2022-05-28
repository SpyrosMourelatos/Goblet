#pragma once

#include "common.hpp"
#include <fstream>
#include <vector>

class file_parser{
    public:
    map_t read(const std::string& f);
    private:
    map_t  map{};
};
