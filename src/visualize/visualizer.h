#pragma once
#include "../field/field.h" 
#include <string>
#include <fstream>


class Visualizer {
    public:
        static void saveFieldPPM(const Field2D& field, const std::string& filename);
        static void saveComparison(const Field2D& field, const Field2D& field2, const std::string& filename);

    private:
        static void valueToRGB(double value, unsigned char& r, unsigned char& g, unsigned char& b);
        static void writePPM(const std::string& fileName, int width, int height, const std::vector<unsigned char>& pixels);
};