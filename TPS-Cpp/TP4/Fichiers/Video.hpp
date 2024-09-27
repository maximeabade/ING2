#ifndef VIDEO_HPP
#define VIDEO_HPP

#include "File.hpp"

class Video : public File {
private:
    unsigned int duration;
    unsigned int frameRate;

public:
    Video(const std::string& name, const std::string& extension, unsigned int size, unsigned int duration, unsigned int frameRate);
    Video(const Video& other);
    ~Video();
    unsigned int getCompressedSize() const;
};

#endif // VIDEO_HPP