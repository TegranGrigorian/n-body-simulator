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

    private:
        void addBody(const Body & newBody) {
            bodies.push_back(newBody);
        }
    };

#endif