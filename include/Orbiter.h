#pragma once
#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include "center.h"

/**
 * An object that orbits around a center. Orbits using Hooke's law, as if attached by a 2D spring.
 * The stiffness of the spring in each dimension is center.mass() / FORCE_SCALE. 
 */
class Orbiter {
    public:
        /**
         * Creates an orbiter.
         * 
         * @param starting_velocity the initial velocity of the Orbiter, {dx, dy}
         * @param center the center to orbit around
         */
        Orbiter(bn::fixed_point starting_velocity, 
                Center &center);

        /**
         * Take a step orbiting around the center.
         */
        void update();

        private:
            bn::sprite_ptr _sprite;
            bn::fixed_point _velocity;
            Center& _center;
            // adding force scale inside each orbiter
            // A scaling factor by which to reduce the force applied when orbiting
            // Important for numerical stability
            static constexpr bn::fixed FORCE_SCALE = 10;
};