#include "visualizer.h"

void Visualizer::saveFieldPPM(const Field2D &field, const std::string &filename)
{
    int width = field.width();
    int height = field.height();

    std::vector<char> pixl(width * height * 3);

}