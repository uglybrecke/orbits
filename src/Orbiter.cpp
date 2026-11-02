#include "movement.h"
#include "center.h"
#include <bn_fixed_point.h>
#include <bn_sprite_items_fire.h>
#include "Orbiter.h"


/**
 * An object that orbits around a center. Orbits using Hooke's law, as if attached by a 2D spring.
 * The stiffness of the spring in each dimension is center.mass() / FORCE_SCALE. 
 */
Orbiter::Orbiter(bn::fixed_point starting_velocity, Center &center) :
        _sprite(bn::sprite_items::fire.create_sprite(center.position())),
        _velocity(starting_velocity),
        _center(center) {
                //run this after making an Orbiter
                //ask what direction the center is facing
                bool which_way = center.direction(); 
                //adjust the sprite to face the direction of the wizard
                _sprite.set_horizontal_flip(!which_way);
                
                //place the fire left or right
                if(which_way) {
                        _sprite.set_position(center.position() + bn::fixed_point(-32, 0));
                } else {
                        _sprite.set_position(center.position() + bn::fixed_point(32, 0));
                }
        }

void Orbiter::update() {
            // A vector from the Orbiter to the Center
            bn::fixed_point delta = _center.position() - _sprite.position();

            // Scale the vector by the mass and apply a FORCE_SCALE
            // This is done in two steps instead of having a pre-scaled mass to prevent loss of
            // fixed point precision
            bn::fixed_point force = delta * _center.mass();
            force /= FORCE_SCALE;

            // Update the current velocity with the force
            _velocity += force;

            // Update the position by taking a step by the velocity vector
            _sprite.set_position(_sprite.position() + _velocity);
}