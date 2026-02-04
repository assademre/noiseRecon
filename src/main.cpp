#include <iostream>
#include "experiments/experimentRunner.h"

constexpr int WIDTH = 32;
constexpr int HEIGHT = 32;
constexpr int TOTAL_ITERATIONS = 1000;

int main() {
    std::vector<int> sensors = {5, 25, 50, 100};
    std::vector<double> noises = {0.0, 1.0, 5.0, 10.0};
    ExperimentRunner::runMultipleExperiments(
        WIDTH,
        HEIGHT,
        sensors,
        noises,
        TOTAL_ITERATIONS
    );

    return 0;
}