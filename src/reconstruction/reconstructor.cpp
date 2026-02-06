#include "reconstructor.h"
#include <algorithm>
#include <cmath>
#include <random>
#include <iostream>

Reconstructor::Reconstructor(int iterations) : iterations_(iterations){}

void Reconstructor::flipBlock(Field2D& field, int cx, int cy, int blockSize, std::mt19937& rng) {
    for (int dy = -blockSize/2; dy<=blockSize/2; ++dy) {
        for (int dx = -blockSize/2; dx<=blockSize/2; ++dx) {
            int x = cx + dx;
            int y = cy + dy;
            
            if (x >= 0 && x < field.width() && y >= 0 && y < field.height()) {
                double val = field.at(x, y);
                field.set(x, y, 1-val);
            }
        }
    }
}

double Reconstructor::computeError(const std::vector<double>& a, const std::vector<double>& b) {
    double error{0.0};
    for (size_t i=0; i<a.size(); ++i) error += std::pow(a[i] - b[i], 2);
    return error;
}

double Reconstructor::computeSmoothnessError(const Field2D& field) {
    double smoothness{0.0};
    int width = field.width();
    int height = field.height();

    for (int y=1; y<height - 1; ++y) {
        for (int x=1; x<width-1; ++x) {
            double center = field.at(x, y);

            //neighbour comparison
            double up = field.at(x, y-1);
            double down = field.at(x, y+1);
            double left = field.at(x-1, y);
            double right = field.at(x+1, y);

            //smoothness calculation
            smoothness += std::pow(center-up, 2);
            smoothness += std::pow(center-down, 2);
            smoothness += std::pow(center-left, 2);
            smoothness += std::pow(center-right, 2);
        }
    }

    return smoothness;
}


void Reconstructor::reconstruct(Field2D &field, const Projection &projection, const std::vector<double> &measurement) {
    std::mt19937 rng(111);
    std::uniform_int_distribution<int> xDist(0, field.width() - 1);
    std::uniform_int_distribution<int> yDist(0, field.height() - 1);
    
    double measurementError = computeError(projection.measure(field), measurement);
    double smoothnessError = computeSmoothnessError(field);
    double bestError = measurementError + (LAMBDA * smoothnessError);

    for (int iter=0; iter<iterations_; ++iter) {
        int cx = xDist(rng);
        int cy = yDist(rng);

        flipBlock(field, cx, cy, BLOCK_SIZE, rng);

        double newMeasurementError = computeError(projection.measure(field), measurement);
        double newSmoothnessError = computeSmoothnessError(field);
        double newError = newMeasurementError + (LAMBDA * newSmoothnessError);

        if (newError < bestError) {
            bestError = newError;
        } else {
            flipBlock(field, cx, cy, BLOCK_SIZE, rng);
        }

        if (iter % ERROR_DISPLAY_FREQUENCY == 0) std::cout << "Iteration: " << iter << " error: " << bestError << '\n';
    }
}