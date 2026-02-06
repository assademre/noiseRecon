#pragma once
#include <vector>
#include "../field/field.h"
#include "../config.h"
#include <random>

enum class SensorType {
    RANDOM,
    LOCALIZED   
};

class Projection {
    public:
        Projection(int numSensors, int fieldSize, SensorType sensorType = SensorType::RANDOM);
        std::vector<double> measure(const Field2D& field) const;
        const std::vector<std::vector<double>>& matrix() const {return A_;}
    private:
        std::vector<std::vector<double>> A_;
        void createRandomSensors(int numSensors, int fieldSize);
        void createLocalizedSensors(int numSensors, int fieldSize);
};