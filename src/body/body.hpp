#ifndef BODY_HPP
#define BODY_HPP

// a body in 2d space time
class Body {
    public:
        float mass, x, y; // simple intristic
        float v_x, v_y; // velocity in x and y vectors
        float a_x, a_y; // acceleration in x and y vectors
        float f_x, f_y; // force in x and y vectors

        Body(float mass, float x, float y, float v_x=0, float v_y = 0) {
            // construct the intristic properties, no force or a yet because no "universe" exists
            this -> mass = mass;
            this -> x = x;
            this -> y = y;
            this -> v_x = v_x;
            this -> v_y = v_y;
        }
    private:
    void update(float time_delta) {
        // update the position of the body based on its current acceleration and velocity
        v_x += a_x * time_delta;
        v_y += a_y * time_delta;
        x += v_x * time_delta;
        y += v_y * time_delta;
    }
};

#endif