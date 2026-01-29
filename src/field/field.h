#pragma once
#include <vector>
#include <cmath>
#include <iostream>

class Field2D {
    public:
        Field2D(int width, int height);

        void addBubble(int cx, int cy, int r);
        double at(int x, int y) const;
        void set(int x, int y, double value);

        int width() const {return width_;}
        int height() const {return height_;}

        void printVisualization() const;


private:
    int width_, height_;
    std::vector<double> data_;

};