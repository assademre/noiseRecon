#include <iostream>
#include "field/field.h"
#include "forward/projection.h"

constexpr int WIDTH = 32;
constexpr int HEIGHT = 32;

int main() {
    Field2D field(WIDTH, HEIGHT);
    field.addBubble(16, 16, 6);
    field.addBubble(8, 10, 4);

    Projection proj(10, WIDTH * HEIGHT);
    auto measurements = proj.measure(field);

    std::cout << "Sensor reading started...\n";
    for (double v : measurements) std::cout << v << '\n';

    field.printVisualization();
    
    return 1;
}