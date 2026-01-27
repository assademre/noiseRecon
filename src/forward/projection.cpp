#include "projection.h"

Projection::Projection(int numSensors, int fieldSize) {
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    A_.resize(numSensors, std::vector<double>(fieldSize));
    for (auto& row : A_) {
        for(auto& v : row) {
            v = dist(rng);
        }
    }
}

std::vector<double> Projection::measure(const Field2D& field) const {
    int width = field.width();
    int height = field.height();
    int N = width*height;

    std::vector<double> x(N);
    for (int y = 0; y<height; ++y) {
        for (int x0 = 0; x0<width; ++x0) {
            x[y * width + x0] = field.at(x0, y);            
        }
    }

    std::vector<double> b(A_.size(), 0.0);
    for (size_t i = 0; i<A_.size(); ++i) {
        for (int j = 0; j<N; ++j) {
            b[i] += A_[i][j] * x[j];            
        }
    }

    return b;
}