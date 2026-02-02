#include <iostream>
#include "field/field.h"
#include "forward/projection.h"
#include "noise/noiseModel.h"
#include "reconstruction/reconstructor.h"
#include "visualize/visualizer.h"


constexpr int WIDTH = 32;
constexpr int HEIGHT = 32;
constexpr int TOTAL_SENSOR = 100;
constexpr double NOISE_VARIABLE = 5.0;
constexpr int TOTAL_ITERATIONS = 1000;

int main() {
    Field2D field(WIDTH, HEIGHT);
    // added two bubbles given x y coordinates with radius                                      
    field.addBubble(16, 16, 6);
    field.addBubble(8, 10, 4);

    Projection proj(TOTAL_SENSOR, WIDTH * HEIGHT);
    auto measurements = proj.measure(field);


    Visualizer::saveFieldPPM(field, "Buble_map.ppm");
    std::cout << "Sensor reading without noise started...\n";
    
    for (double v : measurements) std::cout << v << '\n';


    std::cout << "Sensor reading with noise started...\n";

    NoiseModel noise(NOISE_VARIABLE);
    noise.apply(measurements);


    for (double v : measurements) std::cout << v << '\n';


    // reconstrution test
    Field2D newField(WIDTH, HEIGHT);
    Reconstructor reconstruct(TOTAL_ITERATIONS, 0.5);

    reconstruct.reconstruct(newField, proj, measurements);

    std::cout << "\n Reconstrutered field with ghost blob: \n";
    
    Visualizer::saveFieldPPM(newField, "reconstructed_map.ppm");

    Visualizer::saveComparison(field, newField, "comparison.ppm");
    std::cout << "Comparison saved\n";
    
    return 0;
}