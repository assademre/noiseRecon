#include "projection.h"

Projection::Projection(int numSensors, int fieldSize, SensorType sensorType) {
    if (sensorType == SensorType::RANDOM) {
        createRandomSensors(numSensors, fieldSize);
    } else if (sensorType == SensorType::LOCALIZED) {
        createLocalizedSensors(numSensors, fieldSize);
    }
}

void Projection::createRandomSensors(int numSensors, int fieldSize) {
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    A_.resize(numSensors, std::vector<double>(fieldSize));
    for (auto& row : A_) {
        for(auto& v : row) {
            v = dist(rng);
        }
    }
}

void Projection::createLocalizedSensors(int numSensors, int fieldSize) {
    // TODO: Implement a solution for non square field sizes
    int width = static_cast<int>(std::sqrt(fieldSize));
    int height = width;

    A_.resize(numSensors, std::vector<double>(fieldSize, 0.0));

    for (int s=0; s<numSensors; ++s) {
        double angle = 2.0 * PI * s / numSensors;

        double sx = width/2.0 + (width/2.0 - 1.5) * std::cos(angle);
        double sy = height/2.0 + (height/2.0 - 1.5) * std::sin(angle);
        
        //sensitivity
        double sigma = width/3.0;

        //creating Gaussian sensitivity
        for (int y=0; y<height; ++y) {
            for (int x=0; x<width; ++x) {
                double dx = x - sx;
                double dy = y - sy;
                double distanceSquare = (dx*dx) + (dy*dy);

                //falloff position
                A_[s][y * width + x] = std::exp(-distanceSquare / (2.0 * sigma * sigma));
            }
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