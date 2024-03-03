#include "EncodeMessage.h"
#include <cmath>
#include <algorithm>


// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {
    
}

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions) {
    ImageMatrix encodedImage = img;

    for (size_t i = 0; i < 6; ++i) {
        int row = positions[i].first;
        int col = positions[i].second;

        if (i >= message.size()) {
            break;
        }

        int pixelValue = encodedImage.get_data(row, col);

        int bit = (message[i] - '0');
        pixelValue = (pixelValue & 0xFE) | bit;

        encodedImage.set_data(row, col, pixelValue);
    }

    return encodedImage;
}

