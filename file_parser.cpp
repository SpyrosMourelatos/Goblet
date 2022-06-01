#include "common.hpp"
#include "file_parser.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>


map_t file_parser::read(const std::string &file_name){
    std::ifstream indata; 
    indata.open(file_name); 
    if(!indata) { 
        std::cerr << "Error: file could not be opened"<< file_name <<std::endl;
        exit(1);
    }
    map_t ret{};
    unsigned line_number ={0};
    std::string line;
    while ( std::getline(indata, line) ) { 
        for(auto i:line){
            ret.push_back(std::vector<tile_t>{});
            switch (i)
            {
                case 'H':
                    ret[line_number].push_back(tile_t::harry);
                    break;
                case 'D':
                    ret[line_number].push_back(tile_t::draco);
                    break;
                case 'G':
                    ret[line_number].push_back(tile_t::goblet);
                    break;
                case '|':
                case '-':
                    ret[line_number].push_back(tile_t::wall);
                    break;
                case ' ':
                    ret[line_number].push_back(tile_t::space);
                    break;
                default:
                    std::cerr << "Error file contained invalid char :"<<i<<std::endl;
                    exit(1);
            }
        }
        line_number++;
    }
    indata.close();
    return ret;
}
