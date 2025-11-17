#ifndef KOSMOS_HPP
#define KOSMOS_HPP
#include "../body/body.hpp"
#include <vector>   
class Kosmos {
    std::vector<Body> bodies;
    float time_delta;
    public:
        Kosmos(const std::vector<Body> & InitalBodies) : bodies(InitalBodies), time_delta(0.0f) {
            this -> bodies = InitalBodies;

        }
        void calculate_forces(); // calculate forces between all bodies
        void step(double time_delta); // step the simulation forward by time_delta seconds
        const std::vector<Body> & get_bodies() const {
            return bodies;
        }
    private:
        void addBody(const Body & newBody) {
            bodies.push_back(newBody);
        }
    };

#endif