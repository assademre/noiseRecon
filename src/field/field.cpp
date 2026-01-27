#include "field.h"

Field2D::Field2D(int width, int height)
    : width_(width), height_(height), data_(width * height, 1.0) {}


void Field2D::addBubble(int cx, int cy, int r) {
    for (int y=0; y<height_; y++) {
        for (int x=0; x<width_; x++) {
            int dx{x-cx};
            int dy{y-cy};
            if (dx*dx + dy*dy < r*r) {
                data_[y * width_ + x] = 0.1; // for gas
            }
        }
    }
}

double Field2D::at(int x, int y) const {
    return data_[y*width_ + x];
}

void Field2D::printVisualization() const {
    for (int y = 0; y < height_; ++y) {
        for (int x=0; x < width_; ++x) {
            double v = at(x, y);
            if (v > 0.5) std::cout << "1";
            else std::cout << "0";
        }
        std::cout << '\n';
    }
}