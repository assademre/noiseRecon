#include "experimentRunner.h"
#include <iostream>

void ExperimentRunner::runSingleExperiment(int width, int height, int numSensors, double noiseLevel, int iterations, const std::string& outputPref)
 {
    std::cout << "Sensors: " << numSensors << " | Noise: " << noiseLevel << " | Iterations: " << iterations << '\n';

    Field2D field(width, height);
    field.addBubble(16, 16, 6);
    field.addBubble(8, 10, 4);

    //Projection
    Projection proj(numSensors, width * height);
    auto measurements = proj.measure(field);

    //Noise Model
    NoiseModel noise(noiseLevel);
    noise.apply(measurements);

    //Reconstruct
    Field2D reconstructedField(width, height);
    Reconstructor reconstructor(iterations);
    reconstructor.reconstruct(reconstructedField, proj, measurements);

    //Saving results
    std::string groundTruthFile = outputPref + "_ground_truth.ppm";
    std::string reconstructedFile = outputPref + "_reconstructed.ppm";
    std::string comparisonFile = outputPref + "_comparison.ppm";

    //Visualize
    Visualizer::saveFieldPPM(field, groundTruthFile);
    Visualizer::saveFieldPPM(reconstructedField, reconstructedFile);
    Visualizer::saveComparison(field, reconstructedField, comparisonFile);

    std::cout << "Files saved \n"; 
 }

 void ExperimentRunner::runMultipleExperiments(int width, int height, std::vector<int>& sensorRange, std::vector<double>& noiseRange, int iterations) {
    int experimentNumber = 1;

    for (int sensor : sensorRange) {
        for(double noise : noiseRange) {
            std::string outputPref = "experiment_" + std::to_string(experimentNumber) + "_sensors_" + std::to_string(sensor) + "_noise_" +
            std::to_string(static_cast<int>(noise));

            runSingleExperiment(width, height, sensor, noise, iterations, outputPref);

            experimentNumber++;
        }
    }

    std::cout << "Experiments completed\n";
 }