// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>


// Default constructor
EdgeDetector::EdgeDetector() {

}

// Destructor
EdgeDetector::~EdgeDetector() {

}

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {
    double* Gx[3] = {
            new double[3]{-1.0, 0.0, 1.0},
            new double[3]{-2.0, 0.0, 2.0},
            new double[3]{-1.0, 0.0, 1.0}
    };
    double* Gy[3] = {
            new double[3]{-1.0, -2.0, -1.0},
            new double[3]{0.0, 0.0, 0.0},
            new double[3]{1.0, 2.0, 1.0}
    };
    double height = input_image.get_height();
    double width = input_image.get_width();

    Convolution gxConv(Gx, 3, 3, 1, true);
    ImageMatrix Ix = gxConv.convolve(input_image);

    Convolution gyConv(Gy, 3, 3, 1, true);
    ImageMatrix Iy = gyConv.convolve(input_image);

    ImageMatrix magnitude(height, width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double gx = Ix.get_data(i, j);
            double gy = Iy.get_data(i, j);
            magnitude.set_data(i, j, std::sqrt((gx * gx) + (gy * gy)));
        }
    }

    double threshold = 0.0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            threshold += magnitude.get_data(i, j);
        }
    }
    threshold = threshold / (height * width);

    std::vector<std::pair<int, int>> edgePixels;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (magnitude.get_data(i, j) > threshold) {
                edgePixels.emplace_back(i, j);
            }
        }
    }
    return edgePixels;
}

