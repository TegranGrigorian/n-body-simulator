#include "body.hpp"

Body::Body(double mass, double x, double y, double v_x, double v_y) 
    : mass(mass), x(x), y(y), v_x(v_x), v_y(v_y), a_x(0), a_y(0), f_x(0), f_y(0) {
        // construct the intristic properties, no force or a yet because no "universe" exists
}

double Body::get_mass() const {
    return mass;
}

double Body::get_x() const {
    return this->x;
}

double Body::get_y() const {
    return y;
}

double Body::get_v_x() const {
    return v_x;
}

double Body::get_v_y() const {
    return v_y;
}

double Body::get_a_x() const {
    return a_x;
}

double Body::get_a_y() const {
    return a_y;
}

double Body::get_f_x() const {
    return f_x;
}

double Body::get_f_y() const {
    return f_y;
}

void Body::add_force(double f_x, double f_y) {
    this->f_x += f_x;
    this->f_y += f_y;
}

void Body::set_x(double x) {
    this->x = x;
}

void Body::set_y(double y) {
    this->y = y;
}

void Body::set_v_x(double v_x) {
    this->v_x = v_x;
}

void Body::set_v_y(double v_y) {
    this->v_y = v_y;
}

void Body::set_f_x(double f_x) {
    this->f_x = f_x;
}

void Body::set_f_y(double f_y) {
    this->f_y = f_y;
}

void Body::set_a_x(double a_x) {
    this->a_x = a_x;
}

void Body::set_a_y(double a_y) {
    this->a_y = a_y;
}

void Body::compute_acceleration() { // heart of physics: f = ma -> a = f/m
    a_x = f_x / mass;
    a_y = f_y / mass;
}

void Body::reset_force() {
    f_x = 0;
    f_y = 0;
}

void Body::update(double time_delta) {
    // euler integration, 2nd smartest dude after newton
    v_x += 0.5 * a_x * time_delta;
    v_y += 0.5 * a_y * time_delta;

    // Update position
    x += v_x * time_delta;
    y += v_y * time_delta;
}

void Body::update_velocity(double time_delta) {
    v_x += 0.5 * a_x * time_delta;
    v_y += 0.5 * a_y * time_delta;
}

void Body::step(double time_delta) {
    update(time_delta);
}