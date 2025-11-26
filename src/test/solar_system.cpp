#include "solar_system.h"
#include "../body/body.hpp"
#include "../kosmos/kosmos.hpp"
#include "../constants.h"
#include <chrono>
#include <cstdio>
#include <cmath>
#include <vector>

// Physical constants (SI units)
#define SOLAR_MASS 1.989e30
#define MERCURY_MASS 3.285e23
#define VENUS_MASS 4.867e24
#define EARTH_MASS 5.972e24
#define MOON_MASS 7.342e22
#define MARS_MASS 6.417e23
#define JUPITER_MASS 1.898e27
#define SATURN_MASS 5.683e26
#define URANUS_MASS 8.681e25
#define NEPTUNE_MASS 1.024e26

void test_solar_system_simulation() {
    printf("========================================\n");
    printf("  Solar System Simulation Test\n");
    printf("========================================\n\n");
    
    // Create solar system bodies
    std::vector<Body> bodies;
    
    // Sun at origin
    bodies.push_back(Body(SOLAR_MASS, 0.0, 0.0, 0.0, 0.0));
    
    // Mercury
    bodies.push_back(Body(MERCURY_MASS, 0.387*AU_M, 0.0, 0.0, 47870.0));
    
    // Venus
    bodies.push_back(Body(VENUS_MASS, 0.723*AU_M, 0.0, 0.0, 35020.0));
    
    // Earth
    bodies.push_back(Body(EARTH_MASS, 1.0*AU_M, 0.0, 0.0, 29780.0));
    
    // Moon (relative to Earth)
    double moon_orbital_radius = 3.844e8;  // 384,400 km
    bodies.push_back(Body(MOON_MASS, 1.0*AU_M + moon_orbital_radius, 0.0, 0.0, 29780.0 + 1022.0));
    
    // Mars
    bodies.push_back(Body(MARS_MASS, 1.524*AU_M, 0.0, 0.0, 24070.0));
    
    // Jupiter
    bodies.push_back(Body(JUPITER_MASS, 5.203*AU_M, 0.0, 0.0, 13070.0));
    
    // Saturn
    bodies.push_back(Body(SATURN_MASS, 9.537*AU_M, 0.0, 0.0, 9690.0));
    
    // Uranus
    bodies.push_back(Body(URANUS_MASS, 19.191*AU_M, 0.0, 0.0, 6800.0));
    
    // Neptune
    bodies.push_back(Body(NEPTUNE_MASS, 30.069*AU_M, 0.0, 0.0, 5430.0));
    
    Kosmos kosmos(bodies);
    
    printf("Initial Configuration:\n");
    printf("  Bodies: %zu\n", bodies.size());
    printf("  Sun mass: %.3e kg\n", SOLAR_MASS);
    printf("\n");
    
    // Simulation parameters
    const double time_step = 86400.0;  // 1 day in seconds
    const double time_warp = 100.0;    // 100x speed
    const int fps = 60;                // GUI rendering at 60 FPS
    const double sim_years = 7.0;
    const int steps_per_second = fps;  // Simulate 60 steps per second (GUI loop)
    const int total_steps = (int)(sim_years * 365.25 * steps_per_second);  // Much more intensive
    const int output_interval = steps_per_second * 60;  // Output every minute of real-time
    
    printf("Simulation Parameters:\n");
    printf("  Time step: %.0f seconds (1 day)\n", time_step);
    printf("  Time warp: %.0fx\n", time_warp);
    printf("  Effective step: %.0f seconds\n", time_step * time_warp);
    printf("  GUI simulation: %d FPS\n", fps);
    printf("  Total steps: %d (simulates GUI running for %.1f years)\n", total_steps, sim_years);
    printf("  Output interval: Every 60 seconds real-time\n\n");
    
    printf("%-50s %16s %16s\n", "Simulation Phase", "Time (ms)", "Avg Step (ms)");
    printf("%-50s %16s %16s\n", "---", "---", "---");
    
    // Storage for trajectories (like GUI does)
    std::vector<std::vector<std::pair<double, double>>> trajectories;
    for (size_t i = 0; i < bodies.size(); ++i) {
        trajectories.push_back(std::vector<std::pair<double, double>>());
    }
    
    auto total_start = std::chrono::high_resolution_clock::now();
    auto interval_start = std::chrono::high_resolution_clock::now();
    
    for (int step = 0; step < total_steps; ++step) {
        kosmos.step(time_step * time_warp);  // Apply time warp
        
        // Store trajectory positions (like GUI does every step)
        const auto& current_bodies = kosmos.get_bodies();
        for (size_t i = 0; i < current_bodies.size(); ++i) {
            trajectories[i].push_back({
                current_bodies[i].get_x() / AU_M,
                current_bodies[i].get_y() / AU_M
            });
        }
        
        if ((step + 1) % output_interval == 0) {
            auto interval_end = std::chrono::high_resolution_clock::now();
            auto interval_duration = std::chrono::duration_cast<std::chrono::milliseconds>(interval_end - interval_start);
            double avg_step_ms = interval_duration.count() / (double)output_interval;
            int real_seconds = (step + 1) / fps;
            
            printf("Real-time %3d min: %12.0f ms, Avg step: %.4f ms, Total steps: %d\n", 
                   real_seconds / 60, (double)interval_duration.count(), avg_step_ms, step + 1);
            
            interval_start = std::chrono::high_resolution_clock::now();
        }
    }
    
    auto total_end = std::chrono::high_resolution_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(total_end - total_start);
    
    printf("\n");
    printf("========================================\n");
    printf("Simulation Complete\n");
    printf("========================================\n");
    printf("Total simulation time: %.3f seconds\n", total_duration.count() / 1000.0);
    printf("Total duration: %.0f ms\n", (double)total_duration.count());
    printf("Average time per step: %.4f ms\n", total_duration.count() / (double)total_steps);
    printf("Simulated time: %.1f years\n", sim_years);
    printf("\n");
    
    // Report trajectory memory usage
    long long total_trajectory_points = 0;
    for (const auto& traj : trajectories) {
        total_trajectory_points += traj.size();
    }
    double trajectory_memory_mb = (total_trajectory_points * 2 * sizeof(double)) / (1024.0 * 1024.0);
    printf("Trajectory Statistics:\n");
    printf("  Total stored positions: %lld points\n", total_trajectory_points);
    printf("  Approximate memory: %.2f MB\n", trajectory_memory_mb);
    printf("  Points per body: ~%lld\n", total_trajectory_points / (long long)bodies.size());
    printf("\n");
    
    // Check final positions
    const auto& final_bodies = kosmos.get_bodies();
    printf("Final Body Positions:\n");
    printf("%-10s %16s %16s %16s\n", "Body", "X (AU)", "Y (AU)", "Distance (AU)");
    printf("%-10s %16s %16s %16s\n", "---", "---", "---", "---");
    
    for (size_t i = 0; i < final_bodies.size(); ++i) {
        double x_au = final_bodies[i].get_x() / AU_M;
        double y_au = final_bodies[i].get_y() / AU_M;
        double dist = sqrt(x_au*x_au + y_au*y_au);
        
        const char* names[] = {"Sun", "Mercury", "Venus", "Earth", "Moon", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
        printf("%-10s %16.6f %16.6f %16.6f\n", names[i], x_au, y_au, dist);
    }
}
