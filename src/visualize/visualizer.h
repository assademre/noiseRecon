#pragma once
#include "../field/field.h" 
#include <string>


class Visualizer {
    public:
        static void saveFieldPPM(const Field2D& field, const std::string& filename);
}