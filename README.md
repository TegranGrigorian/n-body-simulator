# Nbody Simulator

This is a C++ based n body simulator with python bindings to be used as a python package. The simulator uses newtonian graviation laws and euler integration to simulate the motion of celestial bodies. This package is intended to be used for educational purposes and simple simulations while being performantive and easy to extend and modify.

## Installation
1. clone the repository
```shell
git clone https://github.com/TegranGrigorian/n-body-simulator
```

1. navigate to the project directory
```shell
cd n-body-simulator
```

1. Compile/Run the program
    * Compile with makefile
    ```shell
    make
    ```
    * Run with main script
    ```shell
    chmod +x ./main.sh
    ./main.sh
    ```
    * Install as python package
    ```shell
    pip install -e .
    ```

## Usage
After installing the package, you can use it in your python scripts as follows:
```python
import nbody

# Create Sun and Earth
sun = nbody.Body(1.989e30, 0.0, 0.0, 0.0, 0.0)
earth = nbody.Body(5.972e24, nbody.AU, 0.0, 0.0, 29780.0)

# Create simulation
sim = nbody.Kosmos([sun, earth]) # bodies are passed through a list

# Run for 1 day
for _ in range(24):
    sim.step(3600.0)  # 1 hour steps

# Check positions
bodies = sim.get_bodies()
print(f"Earth: x={bodies[1].get_x():.3e}, y={bodies[1].get_y():.3e}")
```

## Project Strucuture
* body: contains the body class code
* kosmos: contains the kosmos (simulation) class code
    * mathmatical computations are done here
* test: contains test code for the package
* main.cpp: contains the main function to run the program
```shell
└── src
    ├── bindings.cpp
    ├── body
    │   ├── body.cpp
    │   └── body.hpp
    ├── constants.h
    ├── kosmos
    │   ├── kosmos.cpp
    │   └── kosmos.hpp
    ├── main.cpp
    └── test
        ├── orbit.cpp
        ├── orbit.h
        └── sun_earth.py
```
## Final Notes
This repository aims to be a nbody engine, it is currnetly imployed in one of my projects, `https://github.com/TegranGrigorian/nbody-gui/tree/main`. I built this project to learn more C++ and how to incorporate C++ into Python. For more information or documentation, please refer to the code comments, documents, nbody-gui repository, reach out directly to me or the website I will hopefully soon make. Thank you for checking out my project!