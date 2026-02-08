#pragma once
#include <vector>
#include <string>

//main
constexpr int WIDTH = 64;
constexpr int HEIGHT = 64;
constexpr int TOTAL_ITERATIONS = 5000;

inline std::vector<int> sensors = {1, 10, 20}; 
inline std::vector<double> noises = {0.1, 0.3, 0.5};

//reconstructor
constexpr int ERROR_DISPLAY_FREQUENCY = 20;
inline std::vector<double> lambdas = {0.2, 0.3, 0.5};
inline std::vector<int> blockSizes = {1, 5, 7, 10};

//projection
constexpr double PI = 3.1415;

//experiment runner
struct BubbleConfig {
    int cx, cy, radius;
};

inline std::vector<BubbleConfig> bubbles = {
    {16, 6, 4},
    {25, 55, 7}
};

//output prefix
inline std::string outputPrefix = "output";
