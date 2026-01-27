#include "noiseModel.h"

NoiseModel::NoiseModel(double sigma) 
    : rng_(42), dist_(0.0, sigma) {} 

void NoiseModel::apply(std::vector<double>& vector) {
    for (double& x : vector) {
        x+=dist_(rng_);
    }
}