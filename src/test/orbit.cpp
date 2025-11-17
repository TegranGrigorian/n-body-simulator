#include "orbit.h"
#include "../constants.h"
#include <cstdio>
#include <cmath>

void test_orbit_simulation() {
    // Earth-Sun system with real values
    // Sun: 1.989×10³⁰ kg at origin
    // Earth: 5.972×10²⁴ kg at 1 AU with orbital velocity
    Body sun(1.989e30, 0.0, 0.0, 0.0, 0.0);
    Body earth(5.972e24, AU_M, 0.0, 0.0, 29780.0); // 29780 ms orbit vel

    std::vector<Body> bodies = { sun, earth };
    Kosmos kosmos(bodies);
    

    printf("Earth-Sun Orbital Simulation\n");
    printf("Sun: mass=%.3e kg at oriigin\n", sun.get_mass());
    printf("Earth: mass=%.3e kg at %.3e m 1au\n", earth.get_mass(), earth.get_x());
    printf("Earth orbital velocity: %.0f m/s  ~29,780 m/s\n", earth.get_v_y());
    printf("Expected orbital period: 365.25 days\n\n");

    const double time_step = 3600.0; // 1 hour timestep
    const int num_steps = 8760; // 365 days
    const int output_interval = 730; // Output every ~30 days

    double initial_distance = earth.get_x();
    
    for (int step = 0; step < num_steps; ++step) {
        kosmos.step(time_step);
        
        if (step % output_interval == 0) {
            const auto & current_bodies = kosmos.get_bodies();
            const Body & e = current_bodies[1];
            
            // Calculate distance from sun
            double dist = sqrt(e.get_x() * e.get_x() + e.get_y() * e.get_y());
            double vel = sqrt(e.get_v_x() * e.get_v_x() + e.get_v_y() * e.get_v_y());
            
            printf("Day %3.0f: pos=(%.3e, %.3e) m, dist=%.3e m (%.2f AU), vel=%.0f m/s\n", 
                   (step * time_step) / DAY_TO_SECONDS,  // DAY_TO_SECONDS conversion
                   e.get_x(), e.get_y(), 
                   dist, dist / AU_M,
                   vel);
        }
    }
    
    // Final check
    const auto & final_bodies = kosmos.get_bodies();
    const Body & final_earth = final_bodies[1];
    double final_distance = sqrt(final_earth.get_x() * final_earth.get_x() + 
                                  final_earth.get_y() * final_earth.get_y());
    
    printf("\nResults\n");
    printf("Initial distance: %.3e m (%.3f AU)\n", initial_distance, initial_distance / AU_M);
    printf("Final distance:   %.3e m (%.3f AU)\n", final_distance, final_distance / AU_M);
    printf("Distance change:  %.2f%%\n", 
           (final_distance - initial_distance) / initial_distance * 100);
}