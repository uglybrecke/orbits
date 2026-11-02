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
        for(Orbiter& orbiter : orbiters) {
            orbiter.update();
        }

        bn::core::update();
    }
}