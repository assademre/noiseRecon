#pragma once
#include <vector>
#include <cmath>

class Field2D {
    public:
        Field2D(int width, int height);

        void addBubble(int cx, int cy, int r);
        double at(int x, int y) const;

        int width() const {return width_;}
        int height() const {return height_;}

private:
    int width_, height_;
    std::vector<double> data_;

};