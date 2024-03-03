#include <iostream>

#include "Convolution.h"

// Default constructor 
Convolution::Convolution() {
    this->kernel = nullptr;
    this->kernelHeight = 0;
    this->kernelWidth = 0;
    this->stride = 1;
    this->padding = true;
}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad){
    this->kernelHeight = kh;
    this->kernelWidth = kw;
    this->stride = stride_val;
    this->padding = pad;

    kernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        kernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; ++j) {
            kernel[i][j] = customKernel[i][j];
        }
    }
}

// Destructor
Convolution::~Convolution() {
    if (kernel != nullptr) {
        for (int i = 0; i < kernelHeight; i++) {
            delete[] kernel[i];
        }
        delete[] kernel;
    }
}

// Copy constructor
Convolution::Convolution(const Convolution &other)
    : kernel(nullptr), kernelHeight(0), kernelWidth(0), stride(0), padding(false) {
    if (other.kernel != nullptr) {
        kernel = new double*[other.kernelHeight];
        for (int i = 0; i < other.kernelHeight; i++) {
            kernel[i] = new double[other.kernelWidth];
            for (int j = 0; j < other.kernelWidth; j++) {
                kernel[i][j] = other.kernel[i][j];
            }
        }
        kernelHeight = other.kernelHeight;
        kernelWidth = other.kernelWidth;
    }
    stride = other.stride;
    padding = other.padding;
}


// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this != &other) {
        if (kernel != nullptr) {
            for (int i = 0; i < kernelHeight; i++) {
                delete[] kernel[i];
            }
            delete[] kernel;
        }
        kernel = other.kernel;
        kernelHeight = other.kernelHeight;
        kernelWidth = other.kernelWidth;
        stride = other.stride;
        padding = other.padding;
    }
    return *this;
}

// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    int inputHeight = input_image.get_height();
    int inputWidth = input_image.get_width();
    int outputHeight = ((inputHeight - kernelHeight + 2 * padding) / stride) + 1;
    int outputWidth = ((inputWidth - kernelWidth + 2 * padding) / stride) + 1;

    ImageMatrix convolvedImage(outputHeight, outputWidth);
    if(padding) {
        int paddedHeight = inputHeight + 2;
        int paddedWidth = inputWidth + 2;
        ImageMatrix paddedImage(paddedHeight, paddedWidth);

        for (int i = 1; i < paddedHeight - 1; i++) {
            for (int j = 1; j < paddedWidth - 1; j++) {
                paddedImage.set_data(i, j, input_image.get_data(i - 1, j - 1));
            }
        }

        for (int i = 0; i < outputHeight; i++) {
            for (int j = 0; j < outputWidth; j++) {
                double sum = 0.0;
                for (int ki = 0; ki < kernelHeight; ki++) {
                    for (int kj = 0; kj < kernelWidth; kj++) {
                        sum += paddedImage.get_data(i * stride + ki, j * stride + kj) * kernel[ki][kj];
                    }
                }
                convolvedImage.set_data(i, j, sum);
            }
        }
    } else {
        for (int i = 0; i < outputHeight; i++) {
            for (int j = 0; j < outputWidth; j++) {
                double sum = 0.0;
                for (int ki = 0; ki < kernelHeight; ki++) {
                    for (int kj = 0; kj < kernelWidth; kj++) {
                        sum += input_image.get_data(i *stride + ki, j *stride + kj) * kernel[ki][kj];
                    }
                }
                convolvedImage.set_data(i, j, sum);
            }
        }
    }
    return convolvedImage;
}