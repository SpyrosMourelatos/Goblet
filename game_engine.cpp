#include "game_engine.hpp"


#include <cmath>
#include <random>

int game_engine::loop(){
    display();
    while(true){
        auto act=harry.move();
        if (act!= action_t::invalid){
            if (act == action_t::exit)
                return -1;
            else if(act == action_t::reached_goblet)
            {
                win();
                return 1;
            }
            auto draco_action=draco.move();
            if(draco_action == action_t::reached_goblet)
            {
                lose();
                return 0;
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
void game_engine::enum_to_char(unsigned j,unsigned i,tile_t t){
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


game_engine::game_engine(map_t & map)
    :map_{map},
    draco{map},
    harry{map},
    goblet_accessible{map}

{

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

void game_engine::display(){
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

bool game_engine::maybe_change_goblet(){
    static std::random_device rnd;
    static std::mt19937 mt{rnd()};
    static std::uniform_real_distribution<double> generator(0,1);
    static auto total_probability = 0.1;
    int max_rounds = draco.get_goblet_total_distance();
    //Bernuli Binominam Distribution:
    //Chance of getting even one
    //total_probability=1-(1/1-q)^max_rounds  =>  1-[1/root(0.5,max_rounds)]=q
    auto per_turn_threshold = std::pow(total_probability,1.0/max_rounds);
    double d100 = generator(mt);
    debug("Per turn threshold: ");
    debug(per_turn_threshold);
    debug(d100);
    debug("\n");
    if (d100 > per_turn_threshold){
        total_probability+=0.1;
        return true;
    }
    else return false;
    
};

void game_engine::win(){
    debug("WIN\n");
}

void game_engine::lose(){
    debug("LOSE\n");
}
