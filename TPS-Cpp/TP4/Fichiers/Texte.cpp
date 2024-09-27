#include "Texte.hpp"

Texte::Texte(const std::string& name, const std::string& extension, unsigned int size, Encoding encoding) : File(name, extension, size) {
    this->encoding = encoding;
}

Texte::Texte(const Texte& other) : File(other) {
    encoding = other.encoding;
}

Texte::~Texte() {}

unsigned int Texte::getCompressedSize() const {
    if (encoding == Encoding::ASCII) {
        return size / 2;
    } else {
        return size * 0.6;
    }
}