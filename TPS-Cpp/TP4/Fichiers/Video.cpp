#include "Video.hpp"

Video::Video(const std::string& name, const std::string& extension, unsigned int size, unsigned int duration, unsigned int frameRate) : File(name, extension, size) {
    this->duration = duration;
    this->frameRate = frameRate;
}

Video::Video(const Video& other) : File(other) {
    duration = other.duration;
    frameRate = other.frameRate;
}

Video::~Video() {}

unsigned int Video::getCompressedSize() const {
    if (extension == "mp4") {
        return size * 0.5;
    } else if (extension == "mov") {
        return size * 0.6;
    } else {
        return size;
    }
}