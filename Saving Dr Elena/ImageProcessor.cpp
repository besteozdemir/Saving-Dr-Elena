#include "ImageProcessor.h"

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {

}


std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    ImageSharpening imageSharpening;
    ImageMatrix sharpenedImage = imageSharpening.sharpen(img , 2);
    EdgeDetector edgeDetector;
    const std::vector<std::pair<int, int>> edgePixels = edgeDetector.detectEdges(sharpenedImage);

    DecodeMessage decodeMessage;
    std::string decodedMessage = decodeMessage.decodeFromImage(sharpenedImage , edgePixels);
    return decodedMessage;
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {
    EdgeDetector edgeDetector;
    std::vector<std::pair<int, int>> edgePixels = edgeDetector.detectEdges(img);

    EncodeMessage encodeMessage;
    ImageMatrix encodedMessage = encodeMessage.encodeMessageToImage(img, message, edgePixels);
    return encodedMessage;
}
