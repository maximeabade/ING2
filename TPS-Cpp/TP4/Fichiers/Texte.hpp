#ifndef TEXTE_HPP
#define TEXTE_HPP

#include "File.hpp"

enum class Encoding { ASCII, UTF8 }; // Assuming Encoding enum is declared in File.hpp

class Texte : public File {
private:
    Encoding encoding;

public:
    Texte(const std::string& name, const std::string& extension, unsigned int size, Encoding encoding);
    Texte(const Texte& other);
    ~Texte();
    unsigned int getCompressedSize() const;
};

#endif // TEXTE_HPP