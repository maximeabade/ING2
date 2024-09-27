#ifndef FILE_HPP
#define FILE_HPP

#include <iostream>
#include <string>

class File {
protected:
    std::string name;
    std::string extension;
    unsigned int size;

public:
    // Constructeurs
    File(const std::string& name, const std::string& extension, unsigned int size);
    File(const File& other);
    virtual ~File();

    // Accesseurs
    const std::string& getName() const { return name; }
    void setName(const std::string& name) { this->name = name; }
    friend std::ostream& operator<<(std::ostream& os, const File& file) {
        os << "Nom : " << file.name << std::endl;
        os << "Extension : " << file.extension << std::endl;
        os << "Taille : " << file.size << " octets" << std::endl;
        return os;
    }
};

#endif // FILE_HPP