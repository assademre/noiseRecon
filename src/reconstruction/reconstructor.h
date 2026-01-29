#pragma once
#include "../field/field.h"
#include "../forward/projection.h"
#include <vector>

class Reconstructor {
    public:
        Reconstructor(int itereations, double step);

        void reconstruct(Field2D& field, const Projection& projection, const std::vector<double>& measurement);

    private:
        int iterations_;
        double step_;
        double computeError(const std::vector<double>& a, const std::vector<double>& b);
};