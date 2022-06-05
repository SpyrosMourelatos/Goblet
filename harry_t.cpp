#include "harry_t.hpp"

harry_t::harry_t(map_t& map):
    person(map,tile_t::harry)
{
}

coords harry_t::get_location(){
    return location;
}
action_t harry_t::move(){
    unsigned char  c=getch();//ncurses specific to read keyboard input
    auto x=location[0];
    auto y=location[1];
    switch(c){
        case ' ':
            {
            return action_t::stay;
            }
        case 3://UP in ncurses
            {
                auto ret = move_from_to(location,coords{x,y-1});
                if(ret !=action_t::invalid)
                    location = coords{x,y-1};
                return ret;
            }
        case 2://DOWN in ncurses
            {
                auto ret = move_from_to(location,coords{x,y+1});
                if(ret !=action_t::invalid)
                    location = coords{x,y+1};
                return ret;
            }
        case 4: //left in ncurses
            {
                auto ret = move_from_to(location,coords{x-1,y});
                if(ret !=action_t::invalid)
                    location = coords{x-1,y};
                return ret;
            }
        case 5://right in ncurses
            {
                auto ret = move_from_to(location,coords{x+1,y});
                if(ret !=action_t::invalid)
                    location = coords{x+1,y};
                return ret;
            }
        case 27:
            return action_t::exit;
        default:
            return action_t::invalid;
    }
    return action_t::invalid;
}
