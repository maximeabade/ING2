#include "Image.hpp"

Image::Image(const std::string& name, const std::string& extension, unsigned int size, unsigned int width, unsigned int height) : File(name, extension, size) {
    this->width = width;
    this->height = height;
}

Image::Image(const Image& other) : File(other) {
    width = other.width;
    height = other.height;
}

Image::~Image() {}

unsigned int Image::getCompressedSize() const {
    if (extension == "jpg") {
        return size * 0.8;
    } else if (extension == "png") {
        return size * 0.7;
    } else {
        return size;
    }
}