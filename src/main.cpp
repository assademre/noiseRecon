#include <iostream>
#include "experiments/experimentRunner.h"
#include "forward/projection.h"
#include "config.h"


int main() {
    ExperimentRunner::runMultipleExperiments(
        WIDTH,
        HEIGHT,
        sensors,
        noises,
        TOTAL_ITERATIONS,
        SensorType::LOCALIZED
    );

    return 0;
}