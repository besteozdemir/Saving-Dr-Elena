#include "ImageSharpening.h"

// Default constructor
ImageSharpening::ImageSharpening() {

}

ImageSharpening::~ImageSharpening(){

}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    double* blur[3] = {
            new double[3]{1.0/9, 1.0/9, 1.0/9},
            new double[3]{1.0/9, 1.0/9, 1.0/9},
            new double[3]{1.0/9, 1.0/9, 1.0/9},
    };

    Convolution blurConv(blur, 3, 3, 1, true);
    ImageMatrix blurred_image = blurConv.convolve(input_image);
    ImageMatrix sharp_image = input_image + (input_image - blurred_image) * k;
    for (int i = 0; i < sharp_image.get_height(); ++i) {
        for (int j = 0; j < sharp_image.get_width(); ++j) {
            double pixel_value = sharp_image.get_data(i, j);
            if (pixel_value < 0) {
                sharp_image.set_data(i, j, 0);
            } else if (pixel_value > 255) {
                sharp_image.set_data(i, j, 255);
            }
        }
    }

    return sharp_image;
}
