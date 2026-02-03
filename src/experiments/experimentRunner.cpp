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
