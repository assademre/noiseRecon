# noiseRecon

This is a small experimental C++ project about reconstructing a 2D field from noisy sensor data.

The idea is pretty simple. You generate a field, take measurements with virtual sensors, add noise, and then try to reconstruct the original field again.

This is mainly a learning / research project. Structure and APIs will probably change as I go.

## what it does right now
- creates a 2D field
- adds simple shapes (bubbles)
- projects sensor measurements
- applies noise to the measurements
- tries to reconstruct the field iteratively
- saves the result as an image

## build
you’ll need:
- C++17
- CMake

roughly:

```bash
cmake -S . -B build
cmake --build build
