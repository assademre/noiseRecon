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
        static void runSingleExperiment(int width, int height,
                                        int numSensors,
                                        double noiseLevel,
                                        int iterations,
                                        double lambda,
                                        int blockSize, 
                                        const std::string& outputPref= "results",
                                        SensorType sensorType = SensorType::RANDOM);
        static void runMultipleExperiments(int width, int height,
                                            std::vector<int>& sensorRange,
                                            std::vector<double>& noiseRange,
                                            std::vector<double>& lambdas,
                                            std::vector<int>& blockSizes,
                                            int iterations, 
                                            SensorType sensorType = SensorType::RANDOM);
};