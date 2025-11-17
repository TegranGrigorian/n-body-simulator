#include "kosmos.hpp"
#include "../constants.h"
#include <cmath>

void Kosmos::calculate_forces() {
    // Reset all forces
    for (auto & body : bodies) {
        body.reset_force();  // sigma maethod
    }

    // Calculate gravitational forces between all pairs of bodies
    for (size_t i = 0; i < bodies.size(); ++i) {
        for (size_t j = i + 1; j < bodies.size(); ++j) {
            Body & bodyA = bodies[i];
            Body & bodyB = bodies[j];

            double dx = bodyB.get_x() - bodyA.get_x();
            double dy = bodyB.get_y() - bodyA.get_y();
            double distance_sq = dx * dx + dy * dy;
            
            // add softening to avoid interstellar collisions
            distance_sq += SOFTENING_LENGTH_SQ;

            double distance = sqrt(distance_sq);

            if (distance > 0) {
                double force_magnitude = (G_CONST * bodyA.get_mass() * bodyB.get_mass()) / distance_sq;
                double force_x = force_magnitude * (dx / distance);
                double force_y = force_magnitude * (dy / distance);

                // Update forces using setters
                bodyA.add_force(force_x, force_y);

                // every force has an equal and opposite reaction, except when we both start rapping (ERB reference)
                bodyB.add_force(-force_x, -force_y);
            }
        }
    }
}



void Kosmos::step(double time_delta) {
    // Calculate current forces and accelerations
    calculate_forces();
    for (auto & body : bodies) {
        body.compute_acceleration();
    }
    
    // update
    for (auto & body : bodies) {
        body.update(time_delta);
    }
    
    // Recalculate forces at new positions
    calculate_forces();
    for (auto & body : bodies) {
        body.compute_acceleration();
    }
    
    // update again
    for (auto & body : bodies) {
        body.update_velocity(time_delta);
    }
}