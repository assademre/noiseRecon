#pragma once
#include <vector>
#include "../field/field.h"
#include <random>

class Projection {
    public:
        Projection(int numSensors, int fieldSize);
        std::vector<double> measure(const Field2D& field) const;
        const std::vector<std::vector<double>>& matrix() const {return A_;}
    private:
        std::vector<std::vector<double>> A_;
};