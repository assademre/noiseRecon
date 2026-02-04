#include <iostream>
#include "experiments/experimentRunner.h"
#include "config.h"


int main() {
    ExperimentRunner::runMultipleExperiments(
        WIDTH,
        HEIGHT,
        sensors,
        noises,
        TOTAL_ITERATIONS
    );

    return 0;
}