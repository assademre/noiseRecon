#pragma once
#include <vector>

//main
constexpr int WIDTH = 64;
constexpr int HEIGHT = 64;
constexpr int TOTAL_ITERATIONS = 15000;

inline std::vector<int> sensors = {1}; 
inline std::vector<double> noises = {0.1};

//reconstructor
constexpr int ERROR_DISPLAY_FREQUENCY = 20;
constexpr double LAMBDA = 0.2;
constexpr int BLOCK_SIZE = 13;
