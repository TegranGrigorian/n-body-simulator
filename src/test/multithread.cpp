#include "multithread.h"
#include "../body/body.hpp"
#include "../kosmos/kosmos.hpp"
#include "../constants.h"
#include <chrono>
#include <cstdio>
#include <cmath>
#include <omp.h>
#include <vector>

// Run simulation with multithreading enabled
double run_simulation_with_threads(int num_bodies, int num_steps, bool use_threads, int num_threads) {
    if (!use_threads) {
        omp_set_num_threads(1);  // Force single thread
    } else {
        omp_set_num_threads(num_threads);  // Use specified number of threads`
    }
    
    // Create a more intensive n-body system
    std::vector<Body> bodies;
    
    // Central mass (Sun)
    bodies.push_back(Body(1.989e30, 0.0, 0.0, 0.0, 0.0));
    
    // Create orbital bodies in a spiral/multi-orbital configuration
    double orbital_radius = AU_M;
    for (int i = 1; i < num_bodies; ++i) {
        // Create multiple orbital shells for more interactions
        double radius = orbital_radius * (1.0 + 0.3 * (i % 4));
        double angle = (2.0 * M_PI * i) / (num_bodies - 1);
        
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        
        // Orbital velocity for roughly circular orbit
        double orbital_vel = sqrt(G_CONST * 1.989e30 / radius);
        double v_x = -orbital_vel * sin(angle);
        double v_y = orbital_vel * cos(angle);
        
        // Vary masses slightly
        double mass = 5.972e24 * (0.5 + (i % 3) * 0.3);
        bodies.push_back(Body(mass, x, y, v_x, v_y));
    }
    
    Kosmos kosmos(bodies);
    
    // Time the simulation
    auto start = std::chrono::high_resolution_clock::now();
    
    const double time_step = 3600.0;  // 1 hour timestep
    for (int step = 0; step < num_steps; ++step) {
        kosmos.step(time_step);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    return duration.count();
}

void test_multithread_performance() {
    // Get system info
    int max_threads = omp_get_max_threads();
    printf("System Information:\n");
    printf("  Available CPU threads: %d\n", max_threads);
    printf("  Physics constant G: %.5e m^3 kg^-1 s^-2\n", G_CONST);
    printf("\n");
    
    // Optimal thread count (usually physical cores, not logical)
    int opt_threads = (max_threads > 8) ? max_threads / 2 : max_threads;
    
    // Test different body counts with MUCH larger workload
    std::vector<int> body_counts = {50, 100, 200};
    int num_steps = 5000;  // Extremely intensive simulation
    
    for (int num_bodies : body_counts) {
        printf("Benchmark: %d bodies, %d simulation steps\n", num_bodies, num_steps);
        printf("%-30s %12s %12s %12s\n", "Configuration", "Time (ms)", "Speedup", "Efficiency");
        printf("%-30s %12s %12s %12s\n", "---", "---", "---", "---");
        
        // Single-threaded baseline
        double single_time = run_simulation_with_threads(num_bodies, num_steps, false, 1);
        printf("%-30s %12.2f %12s %12s\n", "Single-threaded (1 thread)", single_time, "-", "-");
        
        // Multi-threaded with optimized thread count
        double multi_time = run_simulation_with_threads(num_bodies, num_steps, true, opt_threads);
        double speedup = single_time / multi_time;
        double efficiency = (speedup / opt_threads) * 100.0;
        
        char thread_config[50];
        sprintf(thread_config, "Multi-threaded (%d threads)", opt_threads);
        printf("%-30s %12.2f %12.2fx %12.1f%%\n", 
               thread_config, multi_time, speedup, efficiency);
        
        printf("\n");
        
        // Analysis
        if (speedup > 2.0) {
            printf("ts Speedup: %.2fx\n", speedup);
        } else if (speedup > 1.0) {
            printf("not as bad(%.2fx)\n", speedup);
        } else {
            printf("YOur bad\n");
        }
        printf("\n");
    }
}