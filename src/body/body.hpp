#ifndef BODY_HPP
#define BODY_HPP

// a body in 2d space time
class Body {
    public:
        double mass, x, y; // simple intristic
        double v_x, v_y; // velocity in x and y vectors
        double a_x, a_y; // acceleration in x and y vectors
        double f_x, f_y; // force in x and y vectors

        Body(double mass, double x, double y, double v_x=0, double v_y = 0);
        // getters
        double get_mass() const;
        double get_x() const;
        double get_y() const;
        double get_v_x() const;
        double get_v_y() const;
        double get_a_x() const;
        double get_a_y() const;
        double get_f_x() const;
        double get_f_y() const;

        // setters
        void set_x(double x);
        void set_y(double y);
        void set_v_x(double v_x);
        void set_v_y(double v_y);
        void set_f_x(double f_x);
        void set_f_y(double f_y);
        void set_a_x(double a_x);
        void set_a_y(double a_y);

        // more complex setters
        void add_force(double f_x, double f_y);
        void compute_acceleration(); // requires forces to be set
        void reset_force(); // zero out forces
        void step(double time_delta); // update position based on velocity and acceleration
        void update(double time_delta); // first half of velocity verlet
        void update_velocity(double time_delta); // second half of velocity verlet
        private:
};

#endif