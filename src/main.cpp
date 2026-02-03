#include <iostream>
#include "experiments/experimentRunner.h"

constexpr int WIDTH = 32;
constexpr int HEIGHT = 32;
constexpr int TOTAL_SENSOR = 100;
constexpr double NOISE_VARIABLE = 5.0;
constexpr int TOTAL_ITERATIONS = 1000;

int main() {
    ExperimentRunner::runSingleExperiment(
        WIDTH,
        HEIGHT,
        TOTAL_SENSOR,
        NOISE_VARIABLE,
        TOTAL_ITERATIONS
    );

    return 0;
}