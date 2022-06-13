#include "common.hpp"
#include "file_parser.hpp"

#include <iostream>
#include <sstream> //string stream


map_t file_parser::read(const std::string &file_name){
    std::ifstream file; 
    file.open(file_name); //file.open("text.txt")
    if(!file) { 
        std::cerr << "Error: file could not be opened "<< file_name <<std::endl;
        exit(1);
    }
    map_t intermidiate_map{};
    unsigned line_number ={0};
    std::string line{};
    while ( std::getline(file, line) ) { 
        //initialize the line because intermidiate_map[line_number] would be undefined
        intermidiate_map.push_back(std::vector<tile_t>{});
        for(auto character:line){
            switch (character)
            {
                case '*':
                    intermidiate_map[line_number].push_back(tile_t::wall);
                    break;
                case '.':
                    intermidiate_map[line_number].push_back(tile_t::space);
                    break;
                default:
                    std::cerr << "Error cha contained invalid char :"<<character<<std::endl;
                    exit(1);
            }
        }
        line_number++;
    }
    file.close();
    return reverse_indexes(intermidiate_map);
}

map_t file_parser::reverse_indexes(const map_t& intermidiate_map){
    map_t actual_map(intermidiate_map[0].size(),std::vector<tile_t>(intermidiate_map.size(),tile_t::space));
    for(unsigned j=0;j<intermidiate_map.size(); j++){
        for(unsigned i=0;i<intermidiate_map[j].size();i++){
            actual_map[i][j]=intermidiate_map[j][i];
        }
    }
    return actual_map;
}
