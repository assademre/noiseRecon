#include "experimentRunner.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include "config.h"

double ExperimentRunner::runSingleExperiment(int width, int height,
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
    double finalError = reconstructor.reconstruct(reconstructedField, proj, measurements);

    //Saving results
    std::string comparisonFile = outputPref + "_comparison.ppm";

    //Visualize
    Visualizer::saveComparison(field, reconstructedField, comparisonFile);

    //Error logging
    std::ofstream errorLog("experiment_errors.csv", std::ios::app);
    if (errorLog.is_open()) {
        errorLog << numSensors << ',' 
                 << noiseLevel << ','
                 << lambda << ','
                 << blockSize << ','
                 << iterations << ','
                 << finalError << '\n';
        errorLog.close();
    }

    std::cout << "Files saved \n"; 
    return finalError;
    
 }

 void ExperimentRunner::runMultipleExperiments(int width, int height,
                                            std::vector<int>& sensorRange,
                                            std::vector<double>& noiseRange,
                                            std::vector<double>& lambdas,
                                            std::vector<int>& blockSizes,
                                            int iterations, 
                                            SensorType sensorType) {

    struct Result { int sensor; double noise; int iterations; double lambda; int blockSize; double err; };
    std::vector<Result> results;
    for (int sensor : sensorRange) {
        for (double noise : noiseRange) {
            for (double lambda : lambdas) {
                for (int blockSize : blockSizes) {
                    std::string outputPref = outputPrefix + "_s" + std::to_string(sensor) +
                                             "_n" + std::to_string(static_cast<int>(noise*100)) +
                                             "_l" + std::to_string(static_cast<int>(lambda*100)) +
                                             "_b" + std::to_string(blockSize);                                        

                    double err = runSingleExperiment(width, height, sensor, noise, iterations, lambda, blockSize, outputPref, sensorType);
                    results.push_back({sensor, noise, iterations, lambda, blockSize, err});
                }
            }
        }
    }

    std::cout << "Experiment summary:\n";
    std::cout << std::setw(8) << "Sensors"
              << std::setw(8) << "Noises"
              << std::setw(8) << "Iteractions"
              << std::setw(8) << "Lambda"
              << std::setw(8) << "Block"
              << std::setw(16) << "Final Error\n";
    std::cout << std::string(46, '-') << '\n';

    for (const auto& r : results) {
        std::cout << std::setw(8) << r.sensor
                  << std::setw(8) << r.noise
                  << std::setw(8) << r.iterations
                  << std::setw(8) << r.lambda
                  << std::setw(8) << r.blockSize
                  << std::setw(14) << std::fixed << std::setprecision(2) << r.err << '\n';
    }
 }