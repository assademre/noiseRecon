#pragma once
#include <string>
#include <vector>
#include "field/field.h"
#include "forward/projection.h"
#include "noise/noiseModel.h"
#include "reconstruction/reconstructor.h"
#include "visualize/visualizer.h"

class ExperimentRunner {
    public:
        static void runSingleExperiment(int width, int height, int numSensors, double noiseLevel, int iterations, const std::string& outputPref=
        "results");
        static void runMultipleExperiments(int width, int height, std::vector<int>& sensorRange, std::vector<double>& noiseRange, int iterations);
};