#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "body/body.hpp"
#include "kosmos/kosmos.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_nbody_core, m) {
    m.doc() = "N-body gravitational simulator - C++ core module";
    
    // Body class bindings
    py::class_<Body>(m, "Body")
        .def(py::init<double, double, double, double, double>(),
             py::arg("mass"),
             py::arg("x"),
             py::arg("y"),
             py::arg("v_x") = 0.0,
             py::arg("v_y") = 0.0,
             "Create a body with mass, position (x, y), and velocity (v_x, v_y)")
        
        // Getters
        .def("get_mass", &Body::get_mass, "Get body mass in kg")
        .def("get_x", &Body::get_x, "Get x position in meters")
        .def("get_y", &Body::get_y, "Get y position in meters")
        .def("get_v_x", &Body::get_v_x, "Get x velocity in m/s")
        .def("get_v_y", &Body::get_v_y, "Get y velocity in m/s")
        .def("get_a_x", &Body::get_a_x, "Get x acceleration in m/s²")
        .def("get_a_y", &Body::get_a_y, "Get y acceleration in m/s²")
        .def("get_f_x", &Body::get_f_x, "Get x force in N")
        .def("get_f_y", &Body::get_f_y, "Get y force in N")
        
        // Setters
        .def("set_x", &Body::set_x, py::arg("x"), "Set x position in meters")
        .def("set_y", &Body::set_y, py::arg("y"), "Set y position in meters")
        .def("set_v_x", &Body::set_v_x, py::arg("v_x"), "Set x velocity in m/s")
        .def("set_v_y", &Body::set_v_y, py::arg("v_y"), "Set y velocity in m/s")
        
        // String representation
        .def("__repr__", [](const Body &b) {
            return "<Body mass=" + std::to_string(b.get_mass()) + 
                   " pos=(" + std::to_string(b.get_x()) + ", " + std::to_string(b.get_y()) + ")>";
        });
    
    // Kosmos class bindings
    py::class_<Kosmos>(m, "Kosmos")
        .def(py::init<const std::vector<Body>&>(),
             py::arg("bodies"),
             "Create a simulation with initial bodies")
        
        .def("step", &Kosmos::step, 
             py::arg("time_delta"),
             "Advance simulation by time_delta seconds")
        
        .def("get_bodies", &Kosmos::get_bodies,
             "Get list of all bodies in the simulation")
        
        .def("__repr__", [](const Kosmos &k) {
            return "<Kosmos with " + std::to_string(k.get_bodies().size()) + " bodies>";
        });
    
    // Constants
    m.attr("G_CONST") = 6.67430e-11;  // Gravitational constant
    m.attr("AU") = 1.496e11;           // Astronomical unit in meters
}
