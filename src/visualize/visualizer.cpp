#include "visualizer.h"

void Visualizer::valueToRGB(double value, unsigned char& r, unsigned char& g, unsigned char& b) {
    value = std::max(0.0, std::min(1.0, value)); // so the value is always betwenn 0 and 1

    unsigned char gray_tone = static_cast<unsigned char>(value * 255); // cast it to 255 for gray tone rgb

    r = g = b = gray_tone;
}

void Visualizer::writePPM(const std::string& fileName, int width, int height, const std::vector<unsigned char>& pixels) {
    std::ofstream file(fileName, std::ios::binary);

    if(!file) {
        std::cerr << "Error. File cannot be opened. Filename: " << fileName << '\n';
        return;
    }

    file << "P6\n" << width << " " << height << "\n255\n";

    file.write(reinterpret_cast<const char*>(pixels.data()), pixels.size());
    file.close();

    std::cout << "File saved under: " << fileName << " sucessfully\n";
}

void Visualizer::saveFieldPPM(const Field2D &field, const std::string &filename)
{
    int width = field.width();
    int height = field.height();

    std::vector<unsigned char> pixels(width * height * 3);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double value = field.at(x, y);
            unsigned char r, g, b;
            
            valueToRGB(value, r, g, b);

            int id = (y*width + x) * 3;

            pixels[id] = r;
            pixels[id+1] = g;
            pixels[id+2] = b;
        }
    }   
    
    writePPM(filename, width, height, pixels);
}

void Visualizer::saveComparison(const Field2D& field, const Field2D& field2, const std::string& filename) {
    int width = field.width();
    int height = field.height();

    // gap between the two images
    int gap = 1;
    int totalWidth = width * 2 + gap;

    std::vector<unsigned char> pixels(totalWidth*height*3);

    std::fill(pixels.begin(), pixels.end(), 150); 

    //TODO: Create a helper function to avoid repeating pixel copy.

    for (int y=0; y<height; ++y) {
        for (int x=0; x<width; ++x) {
            double value = field.at(x, y);
            unsigned char r, g, b;

            valueToRGB(value, r, g, b);

            int id = (y*totalWidth+x) * 3;

            pixels[id] = r;
            pixels[id+1] = g;
            pixels[id+2] = b;
        }
    }

    for (int y=0; y<height; ++y) {
        for (int x=0; x<width; ++x) {
            double value = field2.at(x, y);
            unsigned char r, g, b;

            valueToRGB(value, r, g, b);

            int id = (y*totalWidth+ (width + gap + x)) * 3;

            pixels[id] = r;
            pixels[id+1] = g;
            pixels[id+2] = b;
        }
    }

    writePPM(filename, totalWidth, height, pixels);
}