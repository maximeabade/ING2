#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "File.hpp"

class Image : public File {
private:
    unsigned int width;
    unsigned int height;

public:
    Image(const std::string& name, const std::string& extension, unsigned int size, unsigned int width, unsigned int height);
    Image(const Image& other);
    ~Image();
    unsigned int getCompressedSize() const;
};

#endif // IMAGE_HPP