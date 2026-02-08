#include <iostream>
#include "config.h"
#include "experiments/experimentRunner.h"
#include "forward/projection.h"


int main() {
    ExperimentRunner::runMultipleExperiments(
        WIDTH,
        HEIGHT,
        sensors,
        noises,
        lambdas,
        blockSizes,
        TOTAL_ITERATIONS,
        SensorType::LOCALIZED
    );

    return 0;
}