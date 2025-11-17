#!/bin/bash

# simple build then run
make clean
make
chmod +x ./nbody_simulator
./nbody_simulator