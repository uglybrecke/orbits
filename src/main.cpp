#include <bn_core.h>
#include <bn_backdrop.h>
#include <bn_color.h>
#include <bn_keypad.h>

#include <bn_fixed_point.h>
#include <bn_vector.h>
#include <bn_sprite_items_water.h>

#include "movement.h"
#include "center.h"
#include "Orbiter.h"

#include <bn_log.h>

// Maximum number of orbiters allowed on the screen
static constexpr int MAX_ORBITERS = 30;

// Default velocity for Orbiter
static constexpr bn::fixed_point ORBITER_START_VELOCITY = {0, 2};

int main() {
    bn::core::init();

    Center center = Center({0, 0}, .05, 1);
    bn::vector<Orbiter, MAX_ORBITERS> orbiters = {};

    //water drop starting conditions
    int water_1_start = 80;
    int water_2_start = 80;

    bn::sprite_ptr water_1 = bn::sprite_items::water.create_sprite(-60, water_1_start);
    bn::sprite_ptr water_2 = bn::sprite_items::water.create_sprite(60, water_2_start);
    
    while(true) {
        // Add an orbiter when A is pressed if there's room
        if(bn::keypad::a_pressed()) {
            if(orbiters.size() < MAX_ORBITERS) {
                orbiters.push_back(Orbiter(ORBITER_START_VELOCITY, center));
            }
        }

        // Remove an orbiter when B is pressed if there's at least one
        if (bn::keypad::b_pressed()) {
            if(orbiters.size() > 0) {
                orbiters.pop_back();
            }
        }

        //second attempt to make water move up!
        if (water_1_start > -90) {
            water_1_start--;
        }else {
            water_1_start = 90;
        }

        if (water_2_start > -90) {
            water_2_start--;
        }else {
            water_2_start = 90;
        }

        water_1.set_position(-60, water_1_start);
        water_2.set_position(60, water_2_start);

        center.update();

        int i = 0;
        for(Orbiter& orbiter : orbiters) {
            orbiter.update();

            //check distance for each orbiter from a water
            bn::fixed_point w1_dist = orbiter.position() - water_1.position();
            bn::fixed_point w2_dist = orbiter.position() - water_2.position();

            //did we hit? check x and y coordinates against distance (sprite is 16x16)
            bool hit_water_1 = 
                   w1_dist.x() > -16
                && w1_dist.x() < 16 
                && w1_dist.y() > -16 
                && w1_dist.y() < 16;

            bool hit_water_2 = 
                   w2_dist.x() > -16
                && w2_dist.x() < 16 
                && w2_dist.y() > -16 
                && w2_dist.y() < 16;

            if(hit_water_1 || hit_water_2) {
                //if hit use the index to delete the orbiter
                orbiters.erase(orbiters.begin() + i);
                //leave the loop immediatly
                break;
            }
            //step the iterator if you didn't erase
            i++;         
        }

        bn::core::update();
    }
}