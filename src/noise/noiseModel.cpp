#include "noiseModel.h"

NoiseModel::NoiseModel(double sigma) 
    : rng_(42), dist_(0.0, sigma) {
        if (sigma <= 0.0) {
            throw std::invalid_argument("Noise level must be positive\n");
        }
    } 

void NoiseModel::apply(std::vector<double>& values) {
    for (double& x : values) {
        x+=dist_(rng_);
    }
}