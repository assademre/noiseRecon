#include "experimentRunner.h"
#include <iostream>
#include "config.h"

void ExperimentRunner::runSingleExperiment(int width, int height,
                                        int numSensors,
                                        double noiseLevel,
                                        int iterations,
                                        double lambda,
                                        int blockSize,
                                        const std::string& outputPref,
                                        SensorType sensorType) {
    Field2D field(width, height);

    for (const auto& bubble : bubbles) {
        field.addBubble(bubble.cx, bubble.cy, bubble.radius);
    }

    //Projection
    Projection proj(numSensors, width * height, sensorType);
    auto measurements = proj.measure(field);

    //Noise Model
    NoiseModel noise(noiseLevel);
    noise.apply(measurements);

    //Reconstruct
    Field2D reconstructedField(width, height);
    Reconstructor reconstructor(iterations, lambda, blockSize);
    reconstructor.reconstruct(reconstructedField, proj, measurements);

    //Saving results
    std::string comparisonFile = outputPref + "_comparison.ppm";

    //Visualize
    Visualizer::saveComparison(field, reconstructedField, comparisonFile);

    std::cout << "Files saved \n"; 
 }

 void ExperimentRunner::runMultipleExperiments(int width, int height,
                                            std::vector<int>& sensorRange,
                                            std::vector<double>& noiseRange,
                                            std::vector<double>& lambdas,
                                            std::vector<int>& blockSizes,
                                            int iterations, 
                                            SensorType sensorType) {

    for (int sensor : sensorRange) {
        for (double noise : noiseRange) {
            for (double lambda : lambdas) {
                for (int blockSize : blockSizes) {
                    std::string outputPref = "_s" + std::to_string(sensor) +
                                             "_n" + std::to_string(static_cast<int>(noise*100)) +
                                             "_l" + std::to_string(static_cast<int>(lambda*100)) +
                                             "_b" + std::to_string(blockSize);                                        

                    runSingleExperiment(width, height, sensor, noise, iterations, lambda, blockSize, outputPref, sensorType);
                }
            }
        }
    }

    std::cout << "Experiments completed\n";
 }