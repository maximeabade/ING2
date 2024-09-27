#include "File.hpp"

File::File(const std::string& name, const std::string& extension, unsigned int size) {
    this->name = name;
    this->extension = extension;
    this->size = size;
}

File::File(const File& other) {
    name = other.name;
    extension = other.extension;
    size = other.size;
}

File::~File() {}
