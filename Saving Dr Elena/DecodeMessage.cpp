// DecodeMessage.cpp

#include "DecodeMessage.h"
#include <iostream>

// Default constructor
DecodeMessage::DecodeMessage() {
}

// Destructor
DecodeMessage::~DecodeMessage() {
}


std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {
    std::string binaryString;

    for (const auto& pixel : edgePixels) {
        int pixelValue = image.get_data(pixel.first, pixel.second);
        int lsb = pixelValue & 1;

        binaryString += std::to_string(lsb);
    }

    while (binaryString.length() % 7 != 0) {
        binaryString = '0' + binaryString;
    }

    std::string asciiMessage;
    for (size_t i = 0; i < binaryString.length(); i += 7) {
        std::string segment = binaryString.substr(i, 7);
        int decimalValue = std::stoi(segment, nullptr, 2);

        decimalValue = decimalValue <=32 ? decimalValue+33 : (decimalValue >= 127 ? 126 : decimalValue);

        asciiMessage += static_cast<char>(decimalValue);
    }

    return asciiMessage;
}
