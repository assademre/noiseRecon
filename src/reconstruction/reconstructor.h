#pragma once
#include "field/field.h"
#include "forward/projection.h"
#include <vector>

class Reconstructor {
    public:
        Reconstructor(int iterations, double lambda, int blockSize);

        void reconstruct(Field2D& field, const Projection& projection, const std::vector<double>& measurement);

    private:
        int iterations_;
        double lambda_;
        int blockSize_;
        double computeError(const std::vector<double>& a, const std::vector<double>& b);
        double computeSmoothnessError(const Field2D& field);
        void flipBlock(Field2D& field, int cx, int cy, int blockSize, std::mt19937& rng);
};