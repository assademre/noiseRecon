#pragma once
#include <vector>
#include <random>

class NoiseModel {
    public:
        explicit NoiseModel(double sigma);
        void apply(std::vector<double>& values);

    private:
        std::mt19937 rng_;
        std::normal_distribution<double> dist_;
};