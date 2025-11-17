#ifndef CONSTANTS_H
#define CONSTANTS_H

// physics constants, pretty much just big G
#define G_CONST 6.67430e-11 // BIG G!! m^3 kg^-1 s^-2
#define SOFTENING_LENGTH 1e6 // 1 km softening length to avoid singularities
#define SOFTENING_LENGTH_SQ (SOFTENING_LENGTH * SOFTENING_LENGTH) // ill make clean code
#endif // CONSTANTS_H