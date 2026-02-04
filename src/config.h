#pragma once
#include <vector>

constexpr int WIDTH = 64;
constexpr int HEIGHT = 64;
constexpr int TOTAL_ITERATIONS = 5000;


inline std::vector<int> sensors = {100, 300, 500}; 
inline std::vector<double> noises = {1.0, 3.0, 5.0};