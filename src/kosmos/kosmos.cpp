#include "kosmos.hpp"
#include <omp.h> // include multithreadig
#include "../constants.h"
#include <cmath>

void Kosmos::calculate_forces() {
    // Reset all forces
    #pragma omp parallel for
    for (size_t i = 0; i < bodies.size(); ++i) {
        bodies[i].reset_force();
    }

    // Calculate gravitational forces between all pairs of bodies
    // Note: Using critical section to safely update forces from multiple threads
    #pragma omp parallel for schedule(dynamic)
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

                // Update forces using critical section to prevent race conditions
                #pragma omp critical
                {
                    bodyA.add_force(force_x, force_y);
                    bodyB.add_force(-force_x, -force_y);
                }
            }
        }
    }
}



void Kosmos::step(double time_delta) {
    // Calculate current forces and accelerations
    calculate_forces();
    #pragma omp parallel for
    for (size_t i = 0; i < bodies.size(); ++i) {
        bodies[i].compute_acceleration();
    }
    
    // update
    #pragma omp parallel for
    for (size_t i = 0; i < bodies.size(); ++i) {
        bodies[i].update(time_delta);
    }
    
    // Recalculate forces at new positions
    calculate_forces();

    #pragma omp parallel for
    for (size_t i = 0; i < bodies.size(); ++i) {
        bodies[i].compute_acceleration();
    }
    
    // update again
    #pragma omp parallel for
    for (size_t i = 0; i < bodies.size(); ++i) {
        bodies[i].update_velocity(time_delta);
    }
}