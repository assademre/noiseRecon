#pragma once
#include "reconstructor.h"
#include "../field/field.h"
#include "../forward/projection.h"
#include <vector>

class Reconstructor {
    public:
        Reconstructor(int itereations);

        void reconstruct(Field2D& field, const Projection& projection, const std::vector<double>& measurement);

    private:
        int iterations_;
        double computeError(const std::vector<double>& a, const std::vector<double>& b);
        double computeSmoothnessError(const Field2D& field);
};