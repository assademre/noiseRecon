#include "reconstructor.h"
#include <algorithm>
#include <cmath>
#include <random>
#include <iostream>

constexpr int ERROR_DISPLAY_FREQUENCY{100};

Reconstructor::Reconstructor(int iterations, double step) : iterations_(iterations), step_(step) {}

double Reconstructor::computeError(const std::vector<double>& a, const std::vector<double>& b) {
    double error;
    for (size_t i=0; i<a.size(); ++i) error += std::pow(a[i] - b[i], 2);
    return error;
}

void Reconstructor::reconstruct(Field2D &field, const Projection &projection, const std::vector<double> &measurement) {
    std::mt19937 rng(111);
    std::uniform_int_distribution<int> xDist(0, field.width() - 1);
    std::uniform_int_distribution<int> yDist(0, field.height() - 1);

    double bestError{computeError(projection.measure(field), measurement)};

    for (int iter=0; iter<iterations_; ++iter) {
        int x{xDist(rng)};
        int y{yDist(rng)};

        double real{field.at(x, y)};
        field.set(x, y, 1.0 - real);

        double newError{computeError(projection.measure(field), measurement)};

        if (newError < bestError) {
            bestError = newError;
        } else {
            field.set(x, y, real);
        }

        if (iter % ERROR_DISPLAY_FREQUENCY == 0) std::cout << "Iteration: " << iter << " error: " << bestError << '\n';
    }
}

