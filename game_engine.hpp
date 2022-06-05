#pragma once

#include "common.hpp"
#include "draco_t.hpp" 
#include "harry_t.hpp"
#include "goblet_controller.hpp"

#include <curses.h>
#include <ctime>//for true random seed
#include <stdlib.h>//for rand

class game_engine{
    public:
        game_engine(map_t & map)
            :map_{map},
            draco{map},
            harry{map},
            goblet_accessible{map}

        {
            srand(unsigned(time(0)));

            init_pair(green,COLOR_GREEN,COLOR_GREEN);
            init_pair(yellow,COLOR_YELLOW,COLOR_WHITE);
            init_pair(black,COLOR_BLACK,COLOR_WHITE);

            goblet_location = goblet_accessible.get_location();
            auto draco_location = goblet_accessible.add_entity_on_map(tile_t::draco);
            auto harry_location = goblet_accessible.add_entity_on_map(tile_t::harry);
            harry.set_location(harry_location);
            harry.set_goblet(goblet_location);
            draco.set_location(draco_location);
            draco.set_goblet(goblet_location);
            draco.calculate_path();
            map_[goblet_location[0]][goblet_location[1]]=tile_t::goblet;
            map_[harry_location[0]][harry_location[1]]=tile_t::harry;
            map_[draco_location[0]][draco_location[1]]=tile_t::draco;

        }
        coords add_entity_on_map(tile_t t){
            auto cols= map_.size();
            auto rows= map_[0].size();
            unsigned x=rand()%cols;
            unsigned y=rand()%rows;
            while( map_[x][y] != tile_t::space)
            {
                x=rand()%cols;
                y=rand()%rows;
            }
            return coords{x,y};
        }

        void loop(){
            display();
            while(true){
                auto act=harry.move();
                if (act!= action_t::invalid){
                    if (act == action_t::exit)
                        return;
                    else if(act == action_t::reached_goblet)
                    {
                        win();
                        return;
                    }
                    auto draco_action=draco.move();
                    if(draco_action == action_t::reached_goblet)
                    {
                        lose();
                        return;
                    }

                    if(maybe_change_goblet()){
                        map_[goblet_location[0]][goblet_location[1]]=tile_t::space;
                        goblet_location= goblet_accessible.add_entity_on_map(tile_t::goblet);
                        map_[goblet_location[0]][goblet_location[1]]=tile_t::goblet;
                        harry.set_goblet(goblet_location);
                        draco.set_goblet(goblet_location);
                        draco.calculate_path();
                    }
                    display();
                }
            }

        }
    private:
        enum colors:unsigned{
            green = 1,
            black = 2,
            yellow = 3,
            grey =4
        };
        void win(){
            debug("WIN\n");
        }

        void lose(){
            debug("LOSE\n");
        }
        bool maybe_change_goblet(){
            static int x=1;
            x++;
            return !bool(x%5);
        };
        void display(){
            unsigned i=0;
            for (auto& line: map_){
                unsigned j=0;
                for(auto symbol:line){
                    enum_to_char(j,i,symbol);
                    j++;
                }
                i++;
            }
        };
        void enum_to_char(unsigned j,unsigned i,tile_t t){
            attron(A_NORMAL);
            switch (t)
            {
                case tile_t::harry :
                    attron(COLOR_PAIR(black));
                    mvaddch(j,i,'h');
                    attroff(COLOR_PAIR(black));
                    break;
                case tile_t::wall :
                    attron(COLOR_PAIR(black));
                    mvaddch(j,i,'*');
                    attroff(COLOR_PAIR(black));
                    break;
                case tile_t::draco:
                    attron(COLOR_PAIR(black));
                    mvaddch(j,i,'d');
                    attroff(COLOR_PAIR(black));
                    break;
                case tile_t::goblet:
                    attron(COLOR_PAIR(yellow));
                    mvaddch(j,i,'G');
                    attroff(COLOR_PAIR(yellow));
                    break;
                case tile_t::space :
                    attron(COLOR_PAIR(green));
                    mvaddch(j,i,' ');
                    attroff(COLOR_PAIR(green));
                    break;
                default:
                    attron(COLOR_PAIR(green));
                    mvaddch(j,i,' ');
                    attroff(COLOR_PAIR(green));
            }
        }
        map_t& map_;
        draco_t draco;
        harry_t harry;
        coords goblet_location;
        goblet_controller goblet_accessible;

};
